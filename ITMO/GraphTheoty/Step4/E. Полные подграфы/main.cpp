#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        vector<vector<bool>> has_edge(n + 1, vector<bool>(n + 1, false));

        // Чтение графа
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            has_edge[u][v] = has_edge[v][u] = true;
        }

        // Сортируем списки смежности для оптимизации поиска общих соседей
        for (int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end());
        }

        long long k4_count = 0;

        // Перебираем все рёбра (u, v)
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (u >= v)
                    continue; // Чтобы не считать ребро дважды

                // Находим общих соседей u и v
                vector<int> common;
                for (int w : adj[u]) {
                    if (w == u || w == v)
                        continue;
                    if (has_edge[v][w]) {
                        common.push_back(w);
                    }
                }

                for (int i = 0; i < (int)common.size(); i++) {
                    for (int j = i + 1; j < (int)common.size(); j++) {
                        if (has_edge[common[i]][common[j]]) {
                            k4_count++;
                        }
                    }
                }
            }
        }

        // Каждый K4 посчитан 6 раз (по одному для каждого из 6 рёбер в K4)
        cout << k4_count / 6 << '\n';
    }

    return 0;
}