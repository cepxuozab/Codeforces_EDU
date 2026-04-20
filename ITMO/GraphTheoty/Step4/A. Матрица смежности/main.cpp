#include <iostream>
#include <vector>

auto main() -> int { // NOLINT
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        for (int j = 0; j < m; ++j) {
            int u, v;
            std::cin >> u >> v;
            u--, v--;
            matrix[u][v] = 1;
            matrix[v][u] = 1;
        }
        for (auto const& arr : matrix) {
            for (int x : arr)
                std::cout << x << ' ';
            std::cout << '\n';
        }
    }

    return 0;
}
