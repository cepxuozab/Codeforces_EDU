#include <iostream>
#include <vector>


struct DSU
{
    std::vector<int> parent;
    std::vector<int> depth; // глубина (расстояние до корня)
    std::vector<int> rank; // ранг для объединения

    DSU(int n) : parent(n + 1), depth(n + 1), rank(n + 1)
    {
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    // Найти корень и обновить глубину
    auto find(int x) -> int
    {
        if (parent[x] != x)
        {
            int root = find(parent[x]);
            // При подъеме к корню накапливаем глубину
            depth[x] += depth[parent[x]];
            parent[x] = root;
        }
        return parent[x];
    }

    // a становится подчиненным b (a -> b)
    void unite(int a, int b)
    {
        // a и b — начальники, поэтому parent[a] == a, parent[b] == b
        // a перестает быть корнем, теперь его корень — b
        parent[a] = b;
        depth[a] = 1; // расстояние от a до нового корня b равно 1
        // Ранг не нужен, так как объединение всегда корня с корнем
    }

    // Получить глубину (расстояние до корня)
    auto getDepth(int x) -> int
    {
        find(x); // чтобы обновить глубину
        return depth[x];
    }
};

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(n);

    for (int i = 0; i < m; i++)
    {
        int type;
        std::cin >> type;
        if (type == 1)
        {
            int a, b;
            std::cin >> a >> b;
            dsu.unite(a, b);
        }
        else
        {
            // type == 2
            int c;
            std::cin >> c;
            std::cout << dsu.getDepth(c) << '\n';
        }
    }

    return 0;
}
