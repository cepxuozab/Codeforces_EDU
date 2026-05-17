#include <algorithm>
#include <iostream>
#include <vector>

struct Edge
{
    int u, v;
    long long cost;
    int id;
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

    int n, m;
    long long s;
    std::cin >> n >> m >> s;

    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].cost;
        edges[i].id = i + 1;
    }

    // Сортируем для построения MST из самых дорогих
    std::vector<Edge> edges_sorted = edges;
    std::ranges::sort(edges_sorted, std::greater<>{}, &Edge::cost);

    DSU dsu(n);
    std::vector<bool> in_mst(m + 1, false);

    for (const Edge& e : edges_sorted)
    {
        if (dsu.unite(e.u, e.v))
        {
            in_mst[e.id] = true;
        }
    }

    // Кандидаты на удаление — рёбра не в MST
    std::vector<Edge> to_delete;
    for (const Edge& e : edges)
    {
        if (!in_mst[e.id])
        {
            to_delete.push_back(e);
        }
    }

    // Сортируем кандидатов по возрастанию стоимости
    std::ranges::sort(to_delete, {}, &Edge::cost);

    std::vector<int> deleted_ids;
    long long total_cost = 0;

    for (const Edge& e : to_delete)
    {
        if (total_cost + e.cost <= s)
        {
            total_cost += e.cost;
            deleted_ids.push_back(e.id);
        }
        else
        {
            break;
        }
    }

    std::cout << deleted_ids.size() << "\n";
    if (!deleted_ids.empty())
    {
        for (size_t i = 0; i < deleted_ids.size(); i++)
        {
            if (i > 0) std::cout << " ";
            std::cout << deleted_ids[i];
        }
        std::cout << "\n";
    }

    return 0;
}
