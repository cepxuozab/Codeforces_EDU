#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <cmath>
#include <span>
#include <functional>

auto buildTable(std::span<const int> arr,
                std::function<int(int, int)> const& combine) -> std::vector<std::vector<int>>
{
    const int n = static_cast<int>(arr.size());
    const int LOG = std::ilogb(n) + 1;
    std::vector<std::vector<int>> table(LOG, std::vector<int>(n));
    table[0] = {arr.begin(), arr.end()};

    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            table[j][i] = combine(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);

    return table;
}

auto query(int l, int r,
           std::vector<std::vector<int>> const& table,
           std::function<int(int, int)> const& combine,
           int sentinel) -> int
{
    if (l > r) return sentinel;
    int j = std::ilogb(r - l + 1);
    return combine(table[j][l], table[j][r - (1 << j) + 1]);
}

auto main() -> int//NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> D(N), H(N);
    for (auto& d : D) std::cin >> d;
    for (auto& h : H) std::cin >> h;

    const int K = 2 * N;

    // Префиксные суммы по удвоенному циклическому массиву
    std::vector<int64_t> preSum(K);
    for (int i = 0; i < K; ++i)
    {
        preSum[i] = D[(i + N - 1) % N];
        if (i) preSum[i] += preSum[i - 1];
    }

    // s0[i] = -preSum[i] + 2*H[i%N] (для поиска минимума preSum — максимума s0)
    // s1[i] = +preSum[i] + 2*H[i%N] (для поиска максимума preSum — максимума s1)
    // Sentinel на позиции K — недостижимое значение
    constexpr int64_t INF = 1e18;
    std::vector<int64_t> s0(K + 1), s1(K + 1);
    for (int i = 0; i < K; ++i)
    {
        s0[i] = -preSum[i] + 2LL * H[i % N];
        s1[i] = +preSum[i] + 2LL * H[i % N];
    }
    s0[K] = s1[K] = -INF; // sentinel-индекс

    // Индексный массив [0, 1, ..., K] — таблицы хранят индексы
    std::vector<int> idx(K + 1);
    std::ranges::iota(idx, 0);

    auto byS0 = [&](int a, int b) -> int { return s0[a] > s0[b] ? a : b; }; // argmax s0
    auto byS1 = [&](int a, int b) -> int { return s1[a] > s1[b] ? a : b; }; // argmax s1

    auto stS0 = buildTable(std::span<const int>(idx), byS0);
    auto stS1 = buildTable(std::span<const int>(idx), byS1);

    const int sentinel = K; // индекс с -INF значением

    auto getArgMaxS0 = [&](int l, int r) -> int
    {
        return query(l, r, stS0, byS0, sentinel);
    };
    auto getArgMaxS1 = [&](int l, int r) -> int
    {
        return query(l, r, stS1, byS1, sentinel);
    };

    auto solve = [&](int l, int r) -> int64_t
    {
        int mip = getArgMaxS0(l, r); // argmin preSum
        int mxp = getArgMaxS1(l, r); // argmax preSum
        if (mip != mxp)
            return s1[mxp] + s0[mip];
        // Совпали — нужно рассмотреть второй оптимум для каждого
        int mxpp = byS1(getArgMaxS1(l, mxp - 1), getArgMaxS1(mxp + 1, r));
        int mipp = byS0(getArgMaxS0(l, mxp - 1), getArgMaxS0(mxp + 1, r));
        return std::max(s1[mxp] + s0[mipp], s1[mxpp] + s0[mip]);
    };

    while (M--)
    {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        if (l <= r)
            std::cout << solve(r + 1, l - 1 + N) << '\n';
        else
            std::cout << solve(r + 1, l - 1) << '\n';
    }

    return 0;
}
