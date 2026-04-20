#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<set<int>> adj(n + 1);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].insert(v);
            adj[v].insert(u);
        }

        // Находим вершину с максимальной степенью
        int maxDegreeVertex = 1;
        for (int i = 2; i <= n; i++) {
            if (adj[i].size() > adj[maxDegreeVertex].size()) {
                maxDegreeVertex = i;
            }
        }

        int k = adj[maxDegreeVertex].size();

        // Проверяем два случая:
        // 1. Все вершины со степенью k образуют полный граф
        // 2. Остальные вершины изолированы

        bool valid = true;

        // Множество вершин, которые должны быть в полном графе
        vector<bool> inComplete(n + 1, false);
        inComplete[maxDegreeVertex] = true;
        for (int v : adj[maxDegreeVertex]) {
            inComplete[v] = true;
        }

        // Проверяем вершины из полного графа
        for (int i = 1; i <= n; i++) {
            if (inComplete[i]) {
                // Должна иметь степень k
                if ((int)adj[i].size() != k) {
                    valid = false;
                    break;
                }

                // Должна быть соединена со всеми другими вершинами из полного графа
                for (int j = 1; j <= n; j++) {
                    if (inComplete[j] && i != j) {
                        if (!adj[i].count(j)) {
                            valid = false;
                            break;
                        }
                    }
                }
                if (!valid)
                    break;
            } else {
                // Изолированная вершина
                if (adj[i].size() != 0) {
                    valid = false;
                    break;
                }
            }
        }

        cout << (valid ? "YES" : "NO") << "\n";
    }

    return 0;
}
