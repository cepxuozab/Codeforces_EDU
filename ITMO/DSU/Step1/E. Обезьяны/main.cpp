#include <iostream>
#include <vector>
using namespace std;

constexpr int INF = 1e9;

struct DSU {
    vector<int> parent;
    vector<int> size;
    vector<int> fall_time;
    vector<vector<int>> nodes;

    explicit DSU(int n) : parent(n), size(n, 1), fall_time(n, INF), nodes(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            nodes[i].push_back(i);
        }
        fall_time[0] = -1; // Вожак не падает
    }

    auto find(int x) -> int {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int x, int y, int time) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        // y присоединяем к x
        if (fall_time[x] == INF && fall_time[y] != INF) {
            // x становится связанным с вожаком
            for (int node : nodes[x]) fall_time[node] = time;
        } else if (fall_time[y] == INF && fall_time[x] != INF) {
            // y становится связанным с вожаком
            for (int node : nodes[y]) fall_time[node] = time;
        }
        parent[y] = x;
        size[x] += size[y];
        nodes[x].insert(nodes[x].end(), nodes[y].begin(), nodes[y].end());
        nodes[y].clear();
    }
};

auto main() -> int {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> hands(n);
    for (int i = 0; i < n; i++) {
        cin >> hands[i].first >> hands[i].second;
        if (hands[i].first > 0) hands[i].first--;
        if (hands[i].second > 0) hands[i].second--;
    }

    vector<pair<int, int>> events(m);
    vector<vector<bool>> active(n, vector<bool>(2, true));

    for (int i = 0; i < m; i++) {
        cin >> events[i].first >> events[i].second;
        events[i].first--;
        events[i].second--;
        int monkey = events[i].first;
        int hand = events[i].second;
        active[monkey][hand] = false;
    }

    DSU dsu(n);

    // Добавляем начальные связи (которые не были разжаты)
    for (int i = 0; i < n; i++) {
        for (int h = 0; h < 2; h++) {
            int target = (h == 0 ? hands[i].first : hands[i].second);
            if (target != -1 && active[i][h]) {
                dsu.unite(i, target, -1);
            }
        }
    }

    // Обрабатываем события в обратном порядке
    for (int i = m - 1; i >= 0; i--) {
        int monkey = events[i].first;
        int hand = events[i].second;
        int target = (hand == 0 ? hands[monkey].first : hands[monkey].second);
        dsu.unite(monkey, target, i);
    }

    // Выводим результат
    for (int i = 0; i < n; i++) {
        if (dsu.fall_time[i] == INF) cout << -1 << "\n";
        else cout << dsu.fall_time[i] << "\n";
    }

    return 0;
}