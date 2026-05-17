#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> parent, sz;
    vector<pair<int, int>> history; // (vertex, old_parent)
    vector<pair<int, int>> size_history; // (vertex, old_size)
    vector<int> component_history;
    int components;

    DSU(int n) : parent(n), sz(n, 1), components(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (sz[x] < sz[y]) swap(x, y);

        history.emplace_back(y, parent[y]);
        size_history.emplace_back(x, sz[x]);
        component_history.push_back(components);

        parent[y] = x;
        sz[x] += sz[y];
        components--;
    }

    int get_checkpoint()
    {
        return history.size();
    }

    void rollback_to(int checkpoint)
    {
        while ((int)history.size() > checkpoint)
        {
            // Откатываем в обратном порядке
            parent[history.back().first] = history.back().second;
            history.pop_back();

            sz[size_history.back().first] = size_history.back().second;
            size_history.pop_back();

            components = component_history.back();
            component_history.pop_back();
        }
    }
};

struct SegmentTree
{
    int n;
    vector<vector<pair<int, int>>> tree;

    SegmentTree(int size)
    {
        n = size;
        if (n > 0) tree.resize(4 * n);
    }

    void add_edge(int v, int tl, int tr, int l, int r, const pair<int, int>& edge)
    {
        if (l > r || tl > tr) return;
        if (l <= tl && tr <= r)
        {
            tree[v].push_back(edge);
            return;
        }
        int tm = (tl + tr) / 2;
        if (r <= tm)
        {
            add_edge(v * 2, tl, tm, l, r, edge);
        }
        else if (l > tm)
        {
            add_edge(v * 2 + 1, tm + 1, tr, l, r, edge);
        }
        else
        {
            add_edge(v * 2, tl, tm, l, tm, edge);
            add_edge(v * 2 + 1, tm + 1, tr, tm + 1, r, edge);
        }
    }

    void dfs(int v, int tl, int tr, DSU& dsu, vector<int>& answers)
    {
        if (tl > tr) return; // <-- КРИТИЧЕСКАЯ ЗАЩИТА
        int checkpoint = dsu.get_checkpoint();

        for (const auto& edge : tree[v])
        {
            dsu.unite(edge.first, edge.second);
        }

        if (tl == tr)
        {
            answers[tl] = dsu.components;
        }
        else
        {
            int tm = (tl + tr) / 2;
            dfs(v * 2, tl, tm, dsu, answers);
            dfs(v * 2 + 1, tm + 1, tr, dsu, answers);
        }

        dsu.rollback_to(checkpoint);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    if (m == 0)
    {
        // Нет запросов — ничего не выводим
        return 0;
    }

    vector<char> type(m);
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        type[i] = s[0];

        if (type[i] == '+' || type[i] == '-')
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            if (u > v) swap(u, v);
            edges[i] = {u, v};
        }
    }

    SegmentTree seg_tree(m);
    map<pair<int, int>, int> start_time;

    for (int i = 0; i < m; i++)
    {
        if (type[i] == '+')
        {
            start_time[edges[i]] = i;
        }
        else if (type[i] == '-')
        {
            auto it = start_time.find(edges[i]);
            if (it != start_time.end())
            {
                int st = it->second;
                if (st <= i - 1)
                {
                    seg_tree.add_edge(1, 0, m - 1, st, i - 1, edges[i]);
                }
                start_time.erase(it);
            }
        }
    }

    for (const auto& [fst, snd] : start_time)
    {
        int st = snd;
        seg_tree.add_edge(1, 0, m - 1, st, m - 1, fst);
    }

    DSU dsu(n);
    vector<int> answers(m, -1);

    seg_tree.dfs(1, 0, m - 1, dsu, answers);

    for (int i = 0; i < m; i++)
    {
        if (type[i] == '?')
        {
            cout << answers[i] << '\n';
        }
    }

    return 0;
}
