#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

auto main() -> int {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> seq(k);
        for (int i = 0; i < k; i++) {
            cin >> seq[i];
        }

        // Создаем множество ребер для быстрого поиска
        set<pair<int, int>> edges;

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            // Храним ребра в упорядоченном виде
            if (u > v) swap(u, v);
            edges.insert({u, v});
        }

        // Проверка на путь
        bool is_path = true;
        for (int i = 0; i < k - 1; i++) {
            int u = seq[i], v = seq[i + 1];
            if (u > v) swap(u, v);
            if (edges.find({u, v}) == edges.end()) {
                is_path = false;
                break;
            }
        }

        if (!is_path) {
            cout << "none\n";
            continue;
        }

        // Проверка на цикл
        bool is_cycle = (k >= 3 && seq[0] == seq[k - 1]);

        // Проверка на простоту (все вершины различны, кроме возможного совпадения первой и последней)
        bool is_simple = true;
        unordered_set<int> seen;

        for (int i = 0; i < k; i++) {
            // Для цикла первая и последняя вершины могут совпадать
            if (is_cycle && i == k - 1 && seq[i] == seq[0]) {
                continue; // Пропускаем проверку для последней вершины в цикле
            }

            if (seen.contains(seq[i])) {
                is_simple = false;
                break;
            }
            seen.insert(seq[i]);
        }

        // Определяем результат в порядке приоритета
        if (is_cycle && is_simple) {
            cout << "simple cycle\n";
        } else if (is_cycle) {
            cout << "cycle\n";
        } else if (is_simple) {
            cout << "simple path\n";
        } else {
            cout << "path\n";
        }
    }

    return 0;
}