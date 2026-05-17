#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

auto canFormTree(std::span<const long long> degrees) -> bool
{
    const auto n = static_cast<int>(degrees.size());

    if (n == 1)
    {
        return degrees[0] == 0;
    }

    const auto degree_sum = std::ranges::fold_left(degrees, 0LL, std::plus<>{});
    if (degree_sum != 2LL * (n - 1))
    {
        return false;
    }

    return std::ranges::all_of(degrees, [n](long long d) -> bool
    {
        return d >= 1 && d <= n - 1;
    });
}

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--)
    {
        int n;
        std::cin >> n;

        std::vector<long long> degrees(n);
        for (auto& d : degrees)
        {
            std::cin >> d;
        }

        std::cout << (canFormTree(degrees) ? "YES\n" : "NO\n");
    }

    return 0;
}
