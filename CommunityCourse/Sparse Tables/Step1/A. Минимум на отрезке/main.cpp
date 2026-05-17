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
            lookup[i][j] = lookup[i][j - 1] <
                           lookup[i + (1 << (j - 1))][j - 1]
                               ? lookup[i][j] = lookup[i][j - 1]
                               : lookup[i + (1 << (j - 1))][j - 1];
        }
    }

    return lookup;
}


auto query(int L, int R, std::vector<std::vector<int>> const& lookup) -> int
{
    if (int j = static_cast<int>(log2(R - L + 1)); lookup[L][j] <= lookup[R - (1 << j) + 1][j])
        return lookup[L][j];
    else
        return lookup[R - (1 << j) + 1][j];
}

auto solveQueries(std::span<const int> arr,
                  std::span<const std::pair<int, int>> queries) -> std::vector<int>
{
    std::vector<int> result;
    result.reserve(arr.size());

    auto const lookup = buildSparseTable(arr);

    for (auto const& [L,R] : queries)
    {
        result.push_back(query(L, R, lookup));
    }

    return result;
}

void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) std::cin >> a;
    int m;
    std::cin >> m;
    std::vector<std::pair<int, int>> queries(m);
    for (auto& q : queries)
    {
        int l, r;
        std::cin >> l >> r;
        q = {l, r};
    }
    for (const auto result = solveQueries(arr, queries); const int& r : result) std::cout << r << "\n";
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
