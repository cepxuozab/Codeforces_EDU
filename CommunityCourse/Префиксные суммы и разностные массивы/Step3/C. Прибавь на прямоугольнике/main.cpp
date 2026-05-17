#include <iostream>
#include <vector>
#include <cstdint>

void prefix_sum2D_inplace(std::vector<std::vector<int64_t>>& a)
{
    const int n = static_cast<int>(a.size());
    const int m = static_cast<int>(a[0].size());
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
}

void addOnRectangle(int lx, int ly, int rx, int ry, int64_t d,
                    std::vector<std::vector<int64_t>>& diffs)
{
    diffs[lx][ly]         += d;
    diffs[lx][ry + 1]     -= d;
    diffs[rx + 1][ly]     -= d;
    diffs[rx + 1][ry + 1] += d;
}

auto main() -> int//NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int64_t>> arr(n, std::vector<int64_t>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            std::cin >> arr[i][j];

    std::vector<std::vector<int64_t>> diffs(n + 2, std::vector<int64_t>(m + 2, 0));

    int q;
    std::cin >> q;
    while (q--)
    {
        int x1, y1, x2, y2;
        int64_t val;
        std::cin >> x1 >> y1 >> x2 >> y2 >> val;
        addOnRectangle(x1, y1, x2, y2, val, diffs);
    }

    prefix_sum2D_inplace(diffs);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            arr[i][j] += diffs[i + 1][j + 1];
        for (int j = 0; j < m; ++j)
            std::cout << arr[i][j] << " \n"[j == m - 1];
    }
}