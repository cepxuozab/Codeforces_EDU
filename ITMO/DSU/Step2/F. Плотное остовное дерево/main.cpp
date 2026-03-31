#include <algorithm>
#include <iostream>
#include <vector>


struct Edge
{
    int u, v;
    long long w;
};


struct DSU
{
    std::vector<int> parent, rank;

    DSU(int n) : parent(n + 1), rank(n + 1)
    {
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    auto find(int x) -> int
    {
        while (parent[x] != x)
        {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    auto unite(int x, int y) -> bool
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (rank[x] < rank[y])
            parent[x] = y;
        else if (rank[x] > rank[y])
            parent[y] = x;
        else
        {
            parent[y] = x;
            rank[x]++;
        }
        return true;
    }
};

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    std::ranges::sort(edges, {}, &Edge::w);

    // Проверим связность вообще
    DSU dsu_check(n);
    int components = n;
    for (Edge& e : edges)
    {
        if (dsu_check.unite(e.u, e.v))
        {
            components--;
        }
    }
    if (components > 1)
    {
        std::cout << "NO\n";
        return 0;
    }

    long long best_diff = 1LL << 62; // большое число

    for (int i = 0; i < m; i++)
    {
        DSU dsu(n);
        int edges_used = 0;
        long long min_w = edges[i].w;
        long long max_w = edges[i].w;

        // Пытаемся построить остов, начиная с ребра i
        for (int j = i; j < m; j++)
        {
            if (dsu.unite(edges[j].u, edges[j].v))
            {
                edges_used++;
                max_w = std::max(max_w, edges[j].w);
                if (edges_used == n - 1)
                {
                    best_diff = std::min(best_diff, max_w - min_w);
                    break;
                }
            }
        }
        // Если не удалось построить остов, дальше для больших i тоже не получится (рёбер
        // меньше)
        if (edges_used != n - 1)
            break;
    }

    std::cout << "YES\n" << best_diff << "\n";

    return 0;
}
