#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <concepts>
#include <cmath>
#include <span>
#include <cassert>

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

constexpr auto cmpMax = [](int a, int b) -> int { return std::max(a, b); };
constexpr auto cmpMin = [](int a, int b) -> int { return std::min(a, b); };

auto main() -> int//NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, s, minLen;
    std::cin >> n >> s >> minLen;

    std::vector<int> arr(n);
    for (auto& a : arr) std::cin >> a;

    auto stMin = buildTable<cmpMin>(arr);
    auto stMax = buildTable<cmpMax>(arr);

    auto getDiff = [&](int l, int r) -> int
    {
        return query<cmpMax>(l, r, stMax) - query<cmpMin>(l, r, stMin);
    };

    constexpr int INF = 1'000'000'000;
    const int size = n + 1;

    std::vector<int> tmp(size, INF);
    tmp[n] = 0;
    auto dp = buildTable<cmpMin>(tmp);
    const int pmax = static_cast<int>(dp.size());
    for (int i = n - minLen; i >= 0; --i)
    {
        int low = i + minLen - 2;
        int high = n;
        while (high - low > 1)
        {
            int const mid = (low + high) / 2;
            if (getDiff(i, mid) <= s)
                low = mid;
            else
                high = mid;
        }
        assert(low < n);

        if (i + minLen <= low + 1)
            dp[0][i] = cmpMin(dp[0][i], 1 + query<cmpMin>(i + minLen, low + 1, dp));

        // Подтягиваем верхние уровни для позиции i

        for (int p = 1; p < pmax; ++p)
            if (i + (1 << p) - 1 < size)
                dp[p][i] = cmpMin(dp[p - 1][i], dp[p - 1][i + (1 << (p - 1))]);
    }

    std::cout << (dp[0][0] >= INF ? -1 : dp[0][0]) << '\n';
    return 0;
}
