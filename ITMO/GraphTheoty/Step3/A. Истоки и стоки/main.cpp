#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int { // NOLINT
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> indegree(n), outdegree(n);

        for (int j = 0; j < m; ++j) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--; // переход к 0-индексации
            outdegree[u] = 1; // из u исходит ребро
            indegree[v] = 1; // в v входит ребро
        }

        auto sources = std::ranges::count(indegree, 0); // истоки: нет входящих
        auto sinks = std::ranges::count(outdegree, 0); // стоки: нет исходящих
        std::cout << sources << " " << sinks << "\n";
    }
}
