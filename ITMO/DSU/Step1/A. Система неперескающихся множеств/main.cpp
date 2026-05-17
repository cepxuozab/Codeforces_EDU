#include <iostream>
#include <numeric>
#include <vector>

struct DisjoinSet
{
    std::vector<int> parent;
    std::vector<int> size;

    DisjoinSet(int n)
        : parent(n + 1)
          , size(n + 1, 1)
    {
        std::iota(parent.begin(), parent.end(), 0);
    }

    auto get(int a) -> int
    {
        if (a != parent[a])
            parent[a] = get(parent[a]);
        return parent[a];
    }

    void joint(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (size[a] > size[b])
            std::swap(a, b);
        parent[a] = b;
        size[b] += size[a];
    }
};

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    auto dsu = DisjoinSet(n);
    for (int i = 0; i < m; ++i)
    {
        std::string command;
        int a, b;
        std::cin >> command >> a >> b;
        if (command == "union")
            dsu.joint(a, b);
        else
            dsu.get(a) == dsu.get(b) ? puts("YES") : puts("NO");
    }
}
