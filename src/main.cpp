#include <iostream>

#include "help.h"
#include "functions.h"
#include "single.h"
#include "parallel.h"


int main(int argc, char** argv) {
    auto args = parse_args(argc, argv);

//    std::cout << args.to_csv << std::endl;
//    for(auto i: args.configs){
//        std::cout << "Time: " << i.times << std::endl;
//        std::cout << "abs: " << i.err_abs << std::endl;
//        std::cout << "rel: " << i.err_rel << std::endl;
//        std::cout << "threads: " << i.threads << std::endl;
//        std::cout << "x1: " << i.r.x1 << std::endl;
//        std::cout << "x2: " << i.r.x2 << std::endl;
//        std::cout << "y1: " << i.r.y1 << std::endl;
//        std::cout << "y2: " << i.r.y2 << std::endl;
//        std::cout << "func: " << i.f << std::endl;
//    }
    if(args.to_csv){
        std::cout << "time, threads, func, result" << std::endl;
    }

    for(auto& config: args.configs) {
        calculate_parallel(config, args.to_csv);
//        std::cout << calc_func(config.r, config.f, config.err_abs) << std::endl;
    }


    return 0;
}


