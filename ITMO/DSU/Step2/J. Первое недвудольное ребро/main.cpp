#include <iostream>
#include <vector>
using namespace std;

struct DSU
{
    vector<int> parent, rank, parity;

    explicit DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        parity.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    auto find(int v) -> pair<int, int>
    {
        if (v == parent[v])
            return {v, 0};
        auto [p, x] = find(parent[v]);
        parity[v] ^= x;
        parent[v] = p;
        return {p, parity[v]};
    }

    auto unite(int u, int v) -> bool
    {
        auto [ru, cu] = find(u);
        auto [rv, cv] = find(v);
        if (ru == rv)
        {
            // уже в одной компоненте
            return cu == cv; // если цвета одинаковы -> создаётся нечётный цикл
        }
        // объединяем
        if (rank[ru] < rank[rv])
        {
            swap(ru, rv);
            swap(cu, cv);
        }
        // хотим cu != (cv xor new_parity)
        // new_parity = ?
        // после слияния цвет v = cv xor parity[rv]
        // цвет u = cu
        // нужно cu != (cv xor parity[rv])
        // parity[rv] = cu ^ cv ^ 1
        parity[rv] = cu ^ cv ^ 1;
        parent[rv] = ru;
        if (rank[ru] == rank[rv])
            rank[ru]++;
        return false; // нечётного цикла нет
    }
};

auto main() -> int
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    DSU dsu(n);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (dsu.unite(u, v))
        {
            cout << i << "\n";
            return 0;
        }
    }

    cout << "-1\n";
    return 0;
}
