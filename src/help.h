// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef INTEGRAL_HELP_H
#define INTEGRAL_HELP_H

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include <chrono>
#include <atomic>

#include "functions.h"

struct range {
    double x1, x2, y1, y2;
};

typedef double (*Func)(double, double);

struct config {
    int times = 1;
    double err_abs = -1;
    double err_rel = -1;
    int threads = -1;
    range r = {0, 0, 0, 0};
    Func f = func1;
};

struct args {
    std::vector<config> configs = {};
    bool to_csv = false;
};

void print_help() {
    std::cout << "Usage: name --file <name> [--csv] \n\n"
              << "[--csv] print statistics in csv format"
              << "Config file is key=value on each line \n"
              << "Amount of threads should be divisor of 100 (1, 2, 5, 10...)\n"
              << "config=2 # time to execute this\n"
              << "err_abs=0.01\n"
              << "err_rel=0.00001\n"
              << "threads=1\n"
              << "x1=-50\n"
              << "x2=50\n"
              << "y1=-50\n"
              << "y2=50\n"
              << "func=1 # which function(1-4)\n"
              << "Empty line and new config after it\n"
              << std::endl;

    exit(EXIT_SUCCESS);
}

int parse_int(std::string &str) {
    int number;
    if (sscanf(str.c_str(), "%d", &number) != 1) {
        print_help();
    }
    return number;
}

double parse_double(std::string &str) {
    double number;
    if (sscanf(str.c_str(), "%lf", &number) != 1) {
        print_help();
    }
    return number;
}

bool is_valid(config conf) {
    return conf.err_abs > 0 &&
           conf.err_rel > 0 &&
           conf.threads > 0 &&
           conf.r.x1 != conf.r.x2 &&
           conf.r.y1 != conf.r.y2 && 100 %
                                     conf.threads == 0 && conf.times > 0;
}


args parse_args(int argc, char **argv) {
    args args;
    std::string filename;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
        } else if (strcmp(argv[i], "--csv") == 0) {
            args.to_csv = true;
        } else if (strcmp(argv[i], "--file") == 0) {
            if (i + 1 == argc) {
                std::cout << "No file name: " << std::endl;
                print_help();
            }
            filename = argv[++i];

        } else {
            std::cout << "No such argument: " << argv[i] << std::endl;
            print_help();
        }
    }

    std::ifstream file{filename};

    if (!file.is_open()) {
        std::cout << "No such file: " << filename << std::endl;
        print_help();
    }

    config config;

    std::string str;
    while (std::getline(file, str)) {
        auto index = str.find('=');
        auto key = str.substr(0, index), value = str.substr(index + 1);
        if (key == "err_abs") {
            config.err_abs = parse_double(value);
        } else if (key == "config") {
            config.times = parse_int(value);
        } else if (key == "err_rel") {
            config.err_rel = parse_double(value);
        } else if (key == "threads") {
            config.threads = parse_int(value);
        } else if (key == "x1") {
            config.r.x1 = parse_double(value);
        } else if (key == "x2") {
            config.r.x2 = parse_double(value);
        } else if (key == "y1") {
            config.r.y1 = parse_double(value);
        } else if (key == "y2") {
            config.r.y2 = parse_double(value);
        } else if (key.empty()) {
            args.configs.push_back(config);
            config = {};
        } else if (key == "func") {
            switch (parse_int(value)) {
                case 1:
                    config.f = func1;
                    continue;
                case 2:
                    config.f = func2;
                    continue;
                case 3:
                    config.f = func3;
                    continue;
                case 4:
                    config.f = func4;
                    continue;
                default:
                    print_help();
            }
        } else {
            std::cout << "No such argument: " << key << std::endl;
            print_help();
        }
    }

    args.configs.push_back(config);

    for (auto &&i: args.configs) {
        if (!is_valid(i)) {
            std::cout << "Invalid config" << std::endl;
            print_help();
        }
    }

    file.close();

    return args;
}


inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

#endif //INTEGRAL_HELP_H
