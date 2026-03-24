#include <iostream>
#include <limits>
#include <span>
#include <vector>
#include <format>

struct People
{
    double x{};
    double v{};
};

auto check(std::span<People> peoples, double t) -> bool
{
    constexpr double eps = 1e-6;
    double left = std::numeric_limits<int>::min();
    double right = std::numeric_limits<int>::max();
    for (auto [x,v] : peoples)
    {
        double l = x - v * t;
        double r = x + v * t;
        left = std::max(left, l);
        right = std::min(right, r);
        if (left > right + eps)return false;
    }
    return true;
}

auto search(std::span<People> peoples) -> double
{
    constexpr double eps = 1e-6;
    double l = 0, r = std::numeric_limits<int>::max();
    while (l + eps < r)
    {
        // [l,r)
        auto m = (l + r) / 2;
        if (check(peoples, m))
        {
            r = m;
        }
        else
        {
            l = m + eps;
        }
    }
    return r;
}


auto main() -> int
{
    int n;
    std::cin >> n;
    std::vector<People> peoples(n);
    for (auto& [x,v] : peoples)std::cin >> x >> v;
    std::cout << std::format("{:.8}", search(peoples));
}
