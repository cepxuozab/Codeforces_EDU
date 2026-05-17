#include <iostream>
#include <vector>
#include <algorithm>
#include <concepts>
#include <cmath>
#include <span>

template <std::invocable<int, int> auto Combine>
auto buildTable(std::span<const int> arr) -> std::vector<std::vector<int>>
{
    const int n = static_cast<int>(arr.size());
    const int LOG = static_cast<int>(std::log2(n)) + 1;
    std::vector<std::vector<int>> table(LOG, std::vector<int>(n));

    for (int i = 0; i < n; i++)
        table[0][i] = arr[i];

    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            table[j][i] = Combine(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);

    return table;
}

template <std::invocable<int, int> auto Combine>
auto query(int l, int r,
           std::vector<std::vector<int>> const& table,
           std::vector<int> const& log2floor) -> int
{
    int j = log2floor[r - l + 1];
    return Combine(table[j][l], table[j][r - (1 << j) + 1]);
}

auto buildLog2Floor(int n) -> std::vector<int>
{
    std::vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    return lg;
}

constexpr auto cmpMax = [](int a, int b) -> int { return std::max(a, b); };
constexpr auto cmpMin = [](int a, int b) -> int { return std::min(a, b); };

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int& x : a) std::cin >> x;
    for (int& x : b) std::cin >> x;

    auto const lg = buildLog2Floor(n);
    auto const maxTable = buildTable<cmpMax>(a);
    auto const minTable = buildTable<cmpMin>(b);

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (query<cmpMax>(i, i, maxTable, lg) > query<cmpMin>(i, i, minTable, lg))
            continue;

        int l = i - 1;
        int r = i;

        for (int p = 1 << lg[n - i]; p > 0; p >>= 1)
        {
            if (l + p < n && query<cmpMax>(i, l + p, maxTable, lg) < query<cmpMin>(i, l + p, minTable, lg))
                l += p;
            if (r + p < n && query<cmpMax>(i, r + p, maxTable, lg) <= query<cmpMin>(i, r + p, minTable, lg))
                r += p;
        }

        ans += r - l;
    }

    std::cout << ans << '\n';
    return 0;
}
