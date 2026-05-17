#include <iostream>
#include <vector>

auto main() -> int { // NOLINT
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> outdegree(n + 1, 0);

        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            outdegree[u]++;
        }

        int moves = 0;
        int zeros = 0; // вершины с outdegree = 0

        for (int i = 1; i <= n; i++) {
            if (outdegree[i] == 0) {
                zeros++;
            } else if (outdegree[i] > 1) {
                moves += outdegree[i] - 1; // удаляем лишние ребра
            }
        }

        // Каждой вершине с outdegree = 0 нужно добавить ребро
        // Но мы можем использовать ребра, которые удалили
        moves += zeros;

        std::cout << moves << "\n";
    }

    return 0;
}
