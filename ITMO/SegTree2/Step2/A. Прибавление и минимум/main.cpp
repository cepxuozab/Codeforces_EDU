#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstddef>

struct SegmentTree
{
    explicit SegmentTree(std::size_t n)
    {
        while (size < n) size *= 2;
        tree.assign(2 * size, 0LL);
        lazy.assign(2 * size, 0LL);
    }

    void push(std::size_t node, std::size_t left, std::size_t right)
    {
        if (lazy[node] != 0)
        {
            tree[node] += lazy[node];
            if (right - left > 1)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(std::size_t node, std::size_t left, std::size_t right,
                      std::size_t l, std::size_t r, long long delta)
    {
        push(node, left, right);
        if (r <= left || right <= l) return;
        if (l <= left && right <= r)
        {
            lazy[node] += delta;
            push(node, left, right);
            return;
        }
        std::size_t mid = (left + right) / 2;
        update_range(2 * node, left, mid, l, r, delta);
        update_range(2 * node + 1, mid, right, l, r, delta);
        tree[node] = std::min(tree[2 * node], tree[2 * node + 1]);
    }

    [[nodiscard]] auto query_min(std::size_t node, std::size_t left, std::size_t right,
                                 std::size_t l, std::size_t r) const -> long long
    {
        if (r <= left || right <= l) return LLONG_MAX;
        if (l <= left && right <= r)
        {
            return tree[node] + lazy[node];
        }
        const std::size_t mid = (left + right) / 2;
        const long long left_val = query_min(2 * node, left, mid, l, r);
        const long long right_val = query_min(2 * node + 1, mid, right, l, r);
        long long current_min = std::min(left_val, right_val);
        return current_min + lazy[node];
    }

    // Public interface
    void add(std::size_t l, std::size_t r, long long v)
    {
        update_range(1, 0, size, l, r, v);
    }

    [[nodiscard]] auto min_on(std::size_t l, std::size_t r) const -> long long
    {
        return query_min(1, 0, size, l, r);
    }

private:
    std::size_t size{1};
    std::vector<long long> tree;
    std::vector<long long> lazy;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::cin >> n >> m;

    SegmentTree segtree{n};

    for (std::size_t i = 0; i < m; ++i)
    {
        int op;
        std::cin >> op;
        if (op == 1)
        {
            std::size_t l, r;
            long long v;
            std::cin >> l >> r >> v;
            segtree.add(l, r, v);
        }
        else if (op == 2)
        {
            std::size_t l, r;
            std::cin >> l >> r;
            std::cout << segtree.min_on(l, r) << '\n';
        }
    }

    return 0;
}
