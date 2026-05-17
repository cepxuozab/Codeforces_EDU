#include <iostream>
#include <vector>
#include <string>
#include <numeric>

class DSU
{
public:
    explicit DSU(int n)
        : parent_(n + 1)
    {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    auto find(int x) -> int
    {
        if (parent_[x] == x)
        {
            return x;
        }
        return parent_[x] = find(parent_[x]);
    }

    auto unite(int x, int y) -> bool
    {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry)
        {
            return false;
        }

        parent_[rx] = ry;
        return true;
    }

    auto same(int x, int y) -> bool
    {
        return find(x) == find(y);
    }

private:
    std::vector<int> parent_;
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    // рёбра не нужны (важен только порядок cut)
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;
    }

    struct Command
    {
        bool is_ask;
        int u;
        int v;
    };

    std::vector<Command> commands(k);
    for (int i = 0; i < k; ++i)
    {
        std::string op;
        std::cin >> op >> commands[i].u >> commands[i].v;
        commands[i].is_ask = (op == "ask");
    }

    DSU dsu(n);
    std::vector<bool> answer(k);

    for (int i = k - 1; i >= 0; --i)
    {
        if (commands[i].is_ask)
        {
            answer[i] = dsu.same(commands[i].u, commands[i].v);
        }
        else
        {
            dsu.unite(commands[i].u, commands[i].v);
        }
    }

    for (int i = 0; i < k; ++i)
    {
        if (commands[i].is_ask)
        {
            std::cout << (answer[i] ? "YES\n" : "NO\n");
        }
    }

    return 0;
}
