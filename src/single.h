// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef INTEGRAL_SINGLE_H
#define INTEGRAL_SINGLE_H

#include <cmath>
#include <iostream>

#include "parallel.h"

double calculate_single(range &range, Func &f, int n);

double calc_func(range &range, Func &f, double err_abs) {
    int n = 100;
    double res1 = calculate_single(range, f, n);
    n *= 2;
    double res2 = calculate_single(range, f, n);
    while (std::abs(res1 - res2) > err_abs) {
        res1 = res2;
        n *= 2;
        res2 = calculate_single(range, f, n);
    }


    return res2;
}

double calculate_single(range &range, Func &f, int n) {
    double stepX = (range.x2 - range.x1) / n;
    double stepY = (range.y2 - range.y1) / n;
    double res = 0;
    for (double i = range.x1; i <= range.x2; i += stepX) {
        for (double j = range.y1; j <= range.y2; j += stepY) {
            res += stepX * stepY * f(i, j);
        }
    }
    return res;
}

#endif //INTEGRAL_SINGLE_H
