#include <iostream>
#include <vector>
#include <cstdint>
#include <utility>

class SegmentTree
{
    int size = 1;
    std::vector<int64_t> tree;

public:
    explicit SegmentTree(int n) { init(n); }

    void build(std::vector<int> const& arr)
    {
        build(arr, 0, 0, size);
    }

    [[nodiscard]] auto sum(int l, int r) const -> int64_t
    {
        return sum(l, r, 0, 0, size);
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

private:
    void init(int n)
    {
        while (size < n)
        {
            size *= 2;
        }
        tree.assign(2LL * size, 0LL);
    }

    void build(std::vector<int> const& a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (std::cmp_less(lx, a.size()))
            {
                tree[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    [[nodiscard]] auto sum(int l, int r, int x, int lx, int rx) const -> int64_t
    {
        if (lx >= r || l >= rx)
        {
            return 0;
        }

        if (lx >= l && rx <= r)
        {
            return tree[x];
        }

        int m = (lx + rx) / 2;
        auto s1 = sum(l, r, 2 * x + 1, lx, m);
        auto s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
};

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> arr(n);
    for (int& a : arr)std::cin >> a;
    auto seg_tree = SegmentTree(n);
    seg_tree.build(arr);
    for (int i = 0; i < m; ++i)
    {
        int op;
        std::cin >> op;
        if (op == 1)
        {
            int idx, v;
            std::cin >> idx >> v;
            seg_tree.set(idx, v);
        }
        else
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg_tree.sum(l, r) << '\n';
        }
    }
}
