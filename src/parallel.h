// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef INTEGRAL_PARALLEL_H
#define INTEGRAL_PARALLEL_H

#include <cmath>
#include <mutex>
#include <vector>
#include <thread>


#include "help.h"

std::mutex m;


void calculate_func(Func &f, double &result, double fromX, double fromY, double stepX, double stepY, int amountX,
                    double toY) {
    double res = 0;
    for (size_t i = 0; i < amountX; i++) {
        for (double j = fromY; j <= toY; j += stepY) {
            res += (stepX * stepY * f(fromX, j));
        }
        fromX += stepX;
    }

    m.lock();

    result += res;

    m.unlock();
}

double calculate_threads(Func &f, range &range, int amount, int threads) {
    std::vector<std::thread> t(threads);

    double stepX = (range.x2 - range.x1) / amount,
            stepY = (range.y2 - range.y1) / amount,
            fromX = range.x1,
            result = 0;

    for (size_t i = 0; i < threads; i++) {
        t[i] = std::thread{calculate_func, std::ref(f), std::ref(result), fromX, range.y1, stepX, stepY,
                           (int) amount / threads, range.y2};

        fromX += stepX * amount / threads;
    }


    for (size_t i = 0; i < threads; i++) {
        t[i].join();
    }

    return result;
}

void calculate_parallel(config &config, bool csv) {
    auto start = get_current_time_fenced();

    int amount = 100, threads = config.threads;

    double res2 = calculate_threads(config.f, config.r, amount, threads),
            res1;

    amount *= 2;

    double err_abs, err_rel;

    do {
        res1 = res2;

        amount *= 2;

        res2 = calculate_threads(config.f, config.r, amount, threads);

        err_abs = std::abs(res1 - res2);
        err_rel = std::abs(res1 - res2) / res2;

    } while (err_abs > config.err_abs || err_rel > config.err_rel);

    auto end = get_current_time_fenced();

    if (!csv) {
        std::cout << "Total time: " << to_us(end - start) << std::endl;
        std::cout << "Err abs: " << err_abs << std::endl;
        std::cout << "Err rel: " << err_rel << std::endl;
        std::cout << "Current: " << res2 << std::endl;
    } else {
        std::cout << to_us(end - start) << ", " << threads << ", " << config.f << ", " << res2 << std::endl;
    }
}

#endif //INTEGRAL_PARALLEL_H
