#include <iostream>
#include <vector>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<long long>> p(n + 1, std::vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int val;
            std::cin >> val;
            p[i][j] = val + p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
        }
    }
    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << p[x2][y2] - p[x1 - 1][y2] - p[x2][y1 - 1] + p[x1 - 1][y1 - 1] << '\n';
    }
}
