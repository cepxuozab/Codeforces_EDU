#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <concepts>
#include <cmath>
#include <span>

template <std::invocable<int, int> auto Combine>
auto buildTable(std::span<const int> arr) -> std::vector<std::vector<int>>
{
    const int n = static_cast<int>(arr.size());
    const int LOG = std::ilogb(n) + 1;
    std::vector<std::vector<int>> table(LOG, std::vector<int>(n));
    table[0] = {arr.begin(), arr.end()};

    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            table[j][i] = Combine(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);

    return table;
}

template <std::invocable<int, int> auto Combine>
auto query(int l, int r,
           std::vector<std::vector<int>> const& table) -> int
{
    int j = std::ilogb(r - l + 1);
    return Combine(table[j][l], table[j][r - (1 << j) + 1]);
}


constexpr auto cmpGcd = [](int a, int b) -> int { return std::gcd(a, b); };
constexpr auto cmpMin = [](int a, int b) -> int { return std::min(a, b); };

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--)
    {
        int n;
        std::cin >> n;
        std::vector<int> arr(n);
        for (auto& a : arr)std::cin >> a;
        auto sparse_table = buildTable<cmpMin>(arr);

        int q;
        std::cin >> q;
        while (q--)
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << query<cmpMin>(l, r, sparse_table) << '\n';
        }
    }
    return 0;
}
