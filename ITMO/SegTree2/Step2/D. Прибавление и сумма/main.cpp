#include <iostream>
#include <vector>
#include <cstdint>

class SegmentTree
{
private:
    std::vector<int64_t> tree;
    std::vector<int64_t> lazy;
    size_t n;

    void build(size_t idx, size_t l, size_t r)
    {
        if (l + 1 == r)
        {
            tree[idx] = 0; // initial array is all zeros
        }
        else
        {
            size_t mid = (l + r) / 2;
            build(2 * idx + 1, l, mid);
            build(2 * idx + 2, mid, r);
            tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
        }
    }

    void push(size_t idx, size_t l, size_t r)
    {
        if (lazy[idx] != 0)
        {
            tree[idx] += lazy[idx] * static_cast<int64_t>(r - l);
            if (r - l > 1)
            {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }

    void update_range(size_t idx, size_t seg_l, size_t seg_r, size_t l, size_t r, int64_t v)
    {
        push(idx, seg_l, seg_r);
        if (seg_r <= l || r <= seg_l)
        {
            return;
        }
        if (l <= seg_l && seg_r <= r)
        {
            lazy[idx] += v;
            push(idx, seg_l, seg_r);
            return;
        }
        size_t mid = (seg_l + seg_r) / 2;
        update_range(2 * idx + 1, seg_l, mid, l, r, v);
        update_range(2 * idx + 2, mid, seg_r, l, r, v);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    auto query_sum(size_t idx, size_t seg_l, size_t seg_r, size_t l, size_t r) -> int64_t
    {
        push(idx, seg_l, seg_r);
        if (seg_r <= l || r <= seg_l)
        {
            return 0;
        }
        if (l <= seg_l && seg_r <= r)
        {
            return tree[idx];
        }
        size_t mid = (seg_l + seg_r) / 2;
        int64_t left_sum = query_sum(2 * idx + 1, seg_l, mid, l, r);
        int64_t right_sum = query_sum(2 * idx + 2, mid, seg_r, l, r);
        return left_sum + right_sum;
    }

public:
    explicit SegmentTree(size_t size) : n(size)
    {
        size_t height = 1;
        while (height < n)
        {
            height *= 2;
        }
        tree.resize(2 * height, 0);
        lazy.resize(2 * height, 0);
        build(0, 0, n);
    }

    void add(size_t l, size_t r, int64_t v)
    {
        update_range(0, 0, n, l, r, v);
    }

    auto sum(size_t l, size_t r) -> int64_t
    {
        return query_sum(0, 0, n, l, r);
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    SegmentTree seg_tree(n);

    for (size_t i = 0; i < m; ++i)
    {
        int op;
        std::cin >> op;
        if (op == 1)
        {
            size_t l, r;
            int64_t v;
            std::cin >> l >> r >> v;
            seg_tree.add(l, r, v);
        }
        else if (op == 2)
        {
            size_t l, r;
            std::cin >> l >> r;
            std::cout << seg_tree.sum(l, r) << '\n';
        }
    }

    return 0;
}
