#include <cmath>
#include <iostream>

auto main() -> int {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x;
        std::cin >> x;
        long long d = sqrtl(1LL + 8LL * x) + 1;
        long long res = d / 2;
        if (res * (res - 1) / 2 < x)
            res++;
        std::cout << res << '\n';
    }
}