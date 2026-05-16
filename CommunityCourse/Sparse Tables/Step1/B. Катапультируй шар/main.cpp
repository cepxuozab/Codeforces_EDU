#include <iostream>
#include <vector>
#include <cmath>
#include <span>

auto buildSparseTable(std::span<const int> arr) -> std::vector<std::vector<int>>
{
    const int n = static_cast<int>(arr.size());
    std::vector<std::vector<int>> lookup(n + 1,
                                         std::vector<int>(static_cast<int>(std::log2(n)) + 1));

    for (int i = 0; i < n; i++)
        lookup[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 0; (i + (1 << j) - 1) < n; i++)
        {
            lookup[i][j] = lookup[i][j - 1] >
                           lookup[i + (1 << (j - 1))][j - 1]
                               ? lookup[i][j - 1]
                               : lookup[i + (1 << (j - 1))][j - 1];
        }
    }
    return lookup;
}

auto query(int L, int R, std::vector<std::vector<int>> const& lookup) -> int
{
    if (int j = static_cast<int>(log2(R - L + 1)); lookup[L][j] > lookup[R - (1 << j) + 1][j])
        return lookup[L][j];
    else
        return lookup[R - (1 << j) + 1][j];
}

void solve()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> arr(n);
    for (int& a : arr) std::cin >> a;

    auto const lookup = buildSparseTable(arr);

    int cnt = 0;
    for (int q = 0; q < m; q++)
    {
        int a, b;
        std::cin >> a >> b;
        a--; b--; // переводим в 0-индексацию

        // между a и b нет городов — доставка всегда возможна
        if (b - a <= 1)
        {
            cnt++;
            continue;
        }

        // максимум на [a+1, b-1] должен быть <= h[a]
        int maxBetween = query(a + 1, b - 1, lookup);
        if (maxBetween <= arr[a])
            cnt++;
    }

    std::cout << cnt << "\n";
}

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) solve();
    return 0;
}