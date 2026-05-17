#include <algorithm>
#include <cstdint>
#include <iostream>

auto main() -> int
{
    int64_t w, h, n;
    std::cin >> w >> h >> n;
    auto check = [&](int64_t m) {
        int64_t a = m / w;
        int64_t b = m / h;
        return (n + a - 1) / a <= b;
    };
    auto left = std::max(w, h), right = std::max(w, h) * n + 1;
    while (left < right) { // [l,r)
        auto m = (left + right) / 2;
        if (check(m)) {
            right = m;
        } else {
            left = m + 1;
        }
    }
    std::cout << right;
}
