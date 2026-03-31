#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

struct DisjointSet {
    std::vector<int> parent;
    std::vector<int> size;
    std::vector<int> mini;
    std::vector<int> maxi;

    DisjointSet(int n)
        : parent(n + 1)
        , size(n + 1, 1)
        , mini(n + 1)
        , maxi(n + 1)
    {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            mini[i] = i;
            maxi[i] = i;
        }
    }

    auto get(int a) -> int
    {
        if (a != parent[a])
            parent[a] = get(parent[a]);
        return parent[a];
    }

    void unite(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (a == b)
            return;

        // Объединяем меньшее множество с большим (по размеру)
        if (size[a] > size[b])
            std::swap(a, b);

        parent[a] = b;
        size[b] += size[a];
        mini[b] = std::min(mini[a], mini[b]);
        maxi[b] = std::max(maxi[a], maxi[b]);
    }
};

auto main() -> int
{
#ifdef _DEBUG
    if (!freopen("input.txt", "r", stdin))
        return 0;
#endif

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DisjointSet dsu(n);

    for (int i = 0; i < m; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "union") {
            int a, b;
            std::cin >> a >> b;
            dsu.unite(a, b);
        } else if (command == "get") {
            int v;
            std::cin >> v;
            int root = dsu.get(v);
            std::cout << dsu.mini[root] << ' ' << dsu.maxi[root] << ' ' << dsu.size[root]
                      << '\n';
        }
    }

    return 0;
}
