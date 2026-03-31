#include <iostream>
#include <vector>
#include <string>

class DSU
{
private:
    std::vector<int> parent_;
    std::vector<long long> addv_;
    std::vector<long long> delta_;

    auto findSet(int x) -> int
    {
        if (parent_[x] == x)
        {
            return x;
        }
        int p = parent_[x];
        parent_[x] = findSet(parent_[x]);
        delta_[x] += delta_[p];
        return parent_[x];
    }

public:
    explicit DSU(int n)
        : parent_(n + 1), addv_(n + 1, 0), delta_(n + 1, 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            parent_[i] = i;
        }
    }

    void join(int x, int y)
    {
        int rx = findSet(x);
        int ry = findSet(y);
        if (rx != ry)
        {
            parent_[ry] = rx;
            delta_[ry] = addv_[ry] - addv_[rx];
        }
    }

    void add(int x, long long v)
    {
        addv_[findSet(x)] += v;
    }

    long long get(int x)
    {
        findSet(x);
        return addv_[parent_[x]] + delta_[x];
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(n);

    while (m--)
    {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "join")
        {
            int x, y;
            std::cin >> x >> y;
            dsu.join(x, y);
        }
        else if (cmd == "add")
        {
            int x;
            long long v;
            std::cin >> x >> v;
            dsu.add(x, v);
        }
        else
        {
            // get
            int x;
            std::cin >> x;
            std::cout << dsu.get(x) << '\n';
        }
    }

    return 0;
}
