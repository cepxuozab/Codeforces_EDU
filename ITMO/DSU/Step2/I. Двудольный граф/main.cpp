#include <iostream>
#include <vector>


struct DSU
{
    std::vector<int> parent, rank, diff;

    explicit DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        diff.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    auto find(int v) -> std::pair<int, int>
    {
        if (v == parent[v])
            return {v, 0};
        auto [p, d] = find(parent[v]);
        diff[v] ^= d;
        parent[v] = p;
        return {p, diff[v]};
    }

    auto unite(int x, int y) -> bool
    {
        auto [rx, cx] = find(x);
        auto [ry, cy] = find(y);
        if (rx == ry)
        {
            return false;
        }
        if (rank[rx] < rank[ry])
        {
            std::swap(rx, ry);
            std::swap(cx, cy);
        }
        // нужно, чтобы cx xor (new_diff[ry]) xor cy == 1
        // new_diff[ry] = ?
        // сейчас цвет ry относительно rx = cy (относительно ry) xor diff[ry]? нет, cy уже относительно ry.
        // При слиянии: цвет ry должен стать таким, чтобы (цвет x) != (цвет y)
        // цвет x = cx (относительно rx)
        // цвет y = cy (относительно ry)
        // после соединения ry к rx: цвет ry = cx xor 1 xor cy
        // diff[ry] = (cx xor cy xor 1)
        parent[ry] = rx;
        diff[ry] = cx ^ cy ^ 1;
        if (rank[rx] == rank[ry])
            rank[rx]++;
        return true;
    }

    auto same_color(int x, int y) -> bool
    {
        auto [rx, cx] = find(x);
        auto [ry, cy] = find(y);
        return (cx == cy);
    }
};

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    DSU dsu(n);
    int shift = 0;

    while (m--)
    {
        int t, a, b;
        std::cin >> t >> a >> b;
        a--;
        b--;
        int x = (a + shift) % n;
        int y = (b + shift) % n;

        if (t == 0)
        {
            dsu.unite(x, y);
        }
        else
        {
            if (dsu.same_color(x, y))
            {
                std::cout << "YES\n";
                shift = (shift + 1) % n;
            }
            else
            {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}
