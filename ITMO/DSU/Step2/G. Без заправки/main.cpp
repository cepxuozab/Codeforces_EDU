#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int u, v;
    int weight;
};

struct DSU
{
    std::vector<int> parent, rank;

    explicit DSU(int n) : parent(n + 1), rank(n + 1)
    {
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
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
        if (x == y) return false;
        if (rank[x] < rank[y]) parent[x] = y;
        else if (rank[x] > rank[y]) parent[y] = x;
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

    int n, k;
    std::cin >> n >> k;

    std::vector<Edge> edges(k);
    for (int i = 0; i < k; i++)
    {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    std::ranges::sort(edges, {}, &Edge::weight);

    DSU dsu(n);
    int edges_used = 0;
    int max_edge_in_mst = 0;

    for (const Edge& e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            edges_used++;
            max_edge_in_mst = std::max(max_edge_in_mst, e.weight);
            if (edges_used == n - 1) break;
        }
    }

    // Граф связный по условию, но на всякий случай проверим
    if (edges_used != n - 1)
    {
        // Хотя по условию граф связный, это не должно случиться
        std::cout << "-1\n";
        return 0;
    }

    std::cout << max_edge_in_mst << "\n";

    return 0;
}
