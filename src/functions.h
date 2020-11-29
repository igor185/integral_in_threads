// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef INTEGRAL_FUNCTIONS_H
#define INTEGRAL_FUNCTIONS_H

#include <cmath>

double func1(double x1, double x2) {
    double res = 0.002;

    for (int i = -2; i <= 2; i++)
        for (int j = -2; j <= 2; j++)
            res += 1.0 / (5 * (i + 2) + j + 3 + std::pow(x1 - 16 * j, 6) + std::pow(x2 - 16 * i, 6));

    return 1 / res;
}


double func2(double x1, double x2) {
    return -20 * std::exp(-0.2 * std::sqrt((x1 * x1 + x2 * x2) / 2)) -
           std::exp((std::cos(2 * M_PI * x1) + std::cos(2 * M_PI * x2)) / 2) + 20 + std::exp(1);
}

double func3_sum(double x) {
    double res = 0;
    for (int i = 1; i <= 5; i++)
        res += (i * std::cos((i + 1) * x + 1));


    return res;
}

double func3(double x1, double x2) {
    return -func3_sum(x1) * func3_sum(x2);
}


double func4(double x1, double x2) {
    int a1[] = {1, 2, 1, 1, 5};
    int a2[] = {4, 5, 1, 2, 4};
    int c[] = {2, 1, 4, 7, 2};
    double res = 0;
    for (int i = 0; i < 5; i++)
        res -= c[i] * std::exp((std::pow(x1 - a1[i], 2) + std::pow(x2 - a2[i], 2)) / -M_PI) *
               std::cos(M_PI * (std::pow(x1 - a1[i], 2) + std::pow(x2 - a2[i], 2)));
//                (c[i] *
//                std::exp(
//                        (std::pow(x1 - a1[i], 2) + std::pow(x2 + a2[i], 2))
//                                                                                    / -M_PI))*
//               std::cos(M_PI *
//               (std::pow(x1 - a1[i], 2) + std::pow(x2 - a2[i], 2)
//                                                                                )
//               );


    return res;
}

#endif //INTEGRAL_FUNCTIONS_H
