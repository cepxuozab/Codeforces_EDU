#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <vector>

auto main() -> int
{
    double c;
    std::cin >> c;
    double eps = 1e-7;
    auto Check = [c, eps](long double x) {
        long double num = x * x + sqrt(x);
        return num >= c || std::abs(num - c) <= eps;
    };
    long double l = 0, r = sqrt(c);
    while (l + eps < r) { // [l,r)
        long double m = (l + r) / 2;
        if (Check(m)) {
            r = m;
        } else {
            l = m + eps;
        }
    }
    std::cout << std::format("{:.8}", r);
}
