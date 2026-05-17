#include <algorithm>
#include <iostream>
#include <vector>

struct Fenwick
{
    std::vector<int> bit;
    int n;

    explicit Fenwick(int n) : n(n)
    {
        bit.assign(n + 1, 0);
    }

    void update(int idx, int delta)
    {
        for (++idx; idx <= n; idx += idx & -idx)
        {
            bit[idx] += delta;
        }
    }

    [[nodiscard]] auto query(int idx) const -> int
    {
        if (idx < 0) return 0;
        if (idx >= n) idx = n - 1;
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
        {
            res += bit[idx];
        }
        return res;
    }

    [[nodiscard]] auto range_query(int l, int r) const -> int
    {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(2LL * n);
    for (int i = 0; i < 2 * n; ++i)
    {
        std::cin >> a[i];
    }

    std::vector<int> L(n + 1, -1), R(n + 1, -1);
    for (int i = 0; i < 2 * n; ++i)
    {
        int x = a[i];
        if (L[x] == -1)
        {
            L[x] = i;
        }
        else
        {
            R[x] = i;
        }
    }

    // Шаг 1: посчитать inside[i] — вложенные отрезки (как в задаче C)
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i + 1;

    std::ranges::sort(indices, [&](int i, int j) -> bool
    {
        return L[i] > L[j];
    });

    Fenwick fenwick(2 * n);
    std::vector<int> inside(n + 1, 0);

    for (int x : indices)
    {
        inside[x] = fenwick.query(R[x] - 1);
        fenwick.update(R[x], 1);
    }

    // Шаг 2: собрать все L и R
    std::vector<int> all_L, all_R;
    for (int i = 1; i <= n; ++i)
    {
        all_L.push_back(L[i]);
        all_R.push_back(R[i]);
    }
    std::ranges::sort(all_L);
    std::ranges::sort(all_R);

    // Шаг 3: для каждого i посчитать A и B
    for (int i = 1; i <= n; ++i)
    {
        int l = L[i], r = R[i];

        // A = count of L[j] in (l, r)
        const auto it1 = std::ranges::upper_bound(all_L, l);
        const auto it2 = std::ranges::lower_bound(all_L, r);
        const int A = static_cast<int>(std::distance(it1, it2));

        // B = count of R[j] in (l, r)
        auto it3 = std::ranges::upper_bound(all_R, l);
        const auto it4 = std::ranges::lower_bound(all_R, r);
        const int B = static_cast<int>(std::distance(it3, it4));

        const int intersect = A + B - 2 * inside[i];
        std::cout << intersect << ' ';
    }

    return 0;
}
