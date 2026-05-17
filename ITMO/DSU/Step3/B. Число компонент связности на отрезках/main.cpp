#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class RollbackDSU
{
private:
    vector<int> parent;
    vector<int> sz;
    vector<pair<int*, int>> history;
    int components{};

public:
    explicit RollbackDSU(int n) : parent(n + 1), sz(n + 1, 1), components(n)
    {
        for (int i = 0; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    [[nodiscard]] auto find(int x) const -> int
    {
        while (parent[x] != x)
        {
            x = parent[x];
        }
        return x;
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x == y) return;

        // Эвристика: меньшее к большему
        if (sz[x] > sz[y]) swap(x, y);

        // Сохраняем изменения в стек
        history.emplace_back(&parent[x], parent[x]);
        history.emplace_back(&sz[y], sz[y]);
        history.emplace_back(&components, components);

        parent[x] = y;
        sz[y] += sz[x];
        components--;
    }

    [[nodiscard]] auto getComponents() const -> int
    {
        return components;
    }

    [[nodiscard]] auto saveState() const -> int
    {
        return history.size();
    }

    void restoreState(int state)
    {
        while ((int)history.size() > state)
        {
            auto [ptr, val] = history.back();
            history.pop_back();
            *ptr = val;
        }
    }
};

auto main() -> int
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
    }

    int k;
    cin >> k;

    struct Query
    {
        int l, r, idx;
    };

    vector<Query> queries(k);
    for (int i = 0; i < k; i++)
    {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; // Переводим в 0-индексацию
        queries[i].r--;
        queries[i].idx = i;
    }

    int block_size = max(1, (int)sqrt(m));

    // Группируем запросы по блокам левой границы
    sort(queries.begin(), queries.end(), [&](const Query& a, const Query& b)
    -> bool {
        int ba = a.l / block_size;
        int bb = b.l / block_size;
        if (ba != bb) return ba < bb;
        return a.r < b.r;
    });

    vector<int> answer(k);

    // Обрабатываем запросы блок за блоком
    for (int block_idx = 0; block_idx * block_size < m; block_idx++)
    {

        int block_end = min(m, (block_idx + 1) * block_size);

        RollbackDSU dsu(n);
        int cur_r = block_end - 1;

        // Обрабатываем запросы текущего блока
        for (auto& q : queries)
        {
            if (q.l / block_size != block_idx) continue;

            // Если запрос целиком внутри блока - обрабатываем отдельно
            if (q.r < block_end)
            {
                int state = dsu.saveState();
                for (int i = q.l; i <= q.r; i++)
                {
                    dsu.unite(edges[i].first, edges[i].second);
                }
                answer[q.idx] = dsu.getComponents();
                dsu.restoreState(state);
                continue;
            }

            // Двигаем правую границу от cur_r до q.r
            while (cur_r < q.r)
            {
                cur_r++;
                dsu.unite(edges[cur_r].first, edges[cur_r].second);
            }

            // Сохраняем состояние
            int state = dsu.saveState();

            // Добавляем левую часть [q.l, block_end)
            for (int i = q.l; i < block_end; i++)
            {
                dsu.unite(edges[i].first, edges[i].second);
            }

            answer[q.idx] = dsu.getComponents();

            // Откатываемся
            dsu.restoreState(state);
        }
    }

    for (int i = 0; i < k; i++)
    {
        cout << answer[i] << "\n";
    }

    return 0;
}
