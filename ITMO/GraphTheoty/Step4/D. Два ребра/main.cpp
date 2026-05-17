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
        vector<int> deg(n + 1, 0);

        // Чтение графа
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }

        long long ans = 0;

        // Считаем C(deg(u), 2) для каждой вершины
        // Это количество пар рёбер с общим концом u
        for (int u = 1; u <= n; u++) {
            long long d = deg[u];
            ans += d * (d - 1) / 2;
        }

        // Ориентированный граф для эффективного подсчёта треугольников
        // Ребро (u, v) направлено от u к v, если deg(u) < deg(v) или (deg(u) == deg(v) &&
        // u < v)
        vector<vector<int>> adj_dir(n + 1);
        for (int u = 1; u <= n; u++) {
            for (int v : adj[u]) {
                if (deg[u] < deg[v] || (deg[u] == deg[v] && u < v)) {
                    adj_dir[u].push_back(v);
                }
            }
            sort(adj_dir[u].begin(), adj_dir[u].end());
        }

        // Подсчёт треугольников
        // Каждый треугольник (u, v, w) будет найден ровно один раз
        long long triangles = 0;
        for (int u = 1; u <= n; u++) {
            for (int v : adj_dir[u]) {
                // Ищем общих соседей u и v в ориентированном графе
                int i = 0, j = 0;
                while (i < (int)adj_dir[u].size() && j < (int)adj_dir[v].size()) {
                    if (adj_dir[u][i] == adj_dir[v][j]) {
                        triangles++;
                        i++;
                        j++;
                    } else if (adj_dir[u][i] < adj_dir[v][j]) {
                        i++;
                    } else {
                        j++;
                    }
                }
            }
        }

        ans -= 3 * triangles;

        cout << ans << '\n';
    }

    return 0;
}
