#include <iostream>
#include <vector>

struct SegTree
{
    int n;
    std::vector<bool> sign;
    std::vector<int> sum;

    explicit SegTree(int n) : n(n), sign(n * 4, false), sum(n * 4, 0)
    {
    }

private:
    void flipNode(int rt, int l, int r)
    {
        sign[rt] = !sign[rt];
        sum[rt] = (r - l + 1) - sum[rt];
    }

    void pushUp(int rt)
    {
        sum[rt] = sum[rt * 2] + sum[rt * 2 + 1];
    }

    void pushDown(int rt, int l, int r)
    {
        if (sign[rt])
        {
            int m = (l + r) / 2;
            flipNode(rt * 2, l, m);
            flipNode(rt * 2 + 1, m + 1, r);
            sign[rt] = false;
        }
    }

    void update(int rt, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
        {
            flipNode(rt, l, r);
            return;
        }
        pushDown(rt, l, r);
        int m = (l + r) / 2;
        if (L <= m) update(rt * 2, l, m, L, R);
        if (R > m) update(rt * 2 + 1, m + 1, r, L, R);
        pushUp(rt);
    }

    auto querySum(int rt, int l, int r, int L, int R) -> int
    {
        if (L <= l && r <= R) return sum[rt];
        pushDown(rt, l, r);
        int m = (l + r) / 2;
        if (R <= m) return querySum(rt * 2, l, m, L, R);
        if (L > m) return querySum(rt * 2 + 1, m + 1, r, L, R);
        return querySum(rt * 2, l, m, L, R) + querySum(rt * 2 + 1, m + 1, r, L, R);
    }

    auto kthOne(int rt, int l, int r, int k) -> int
    {
        if (l == r) return l;
        pushDown(rt, l, r);
        int m = (l + r) / 2;
        if (sum[rt * 2] >= k) return kthOne(rt * 2, l, m, k);
        else return kthOne(rt * 2 + 1, m + 1, r, k - sum[rt * 2]);
    }

public:
    void update(int L, int R)
    {
        update(1, 1, n, L, R);
    }

    auto kthOne(int k) -> int
    {
        return kthOne(1, 1, n, k);
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SegTree seg(n);

    while (m--)
    {
        int op;
        std::cin >> op;
        if (op == 1)
        {
            int l, r;
            std::cin >> l >> r;
            seg.update(l + 1, r);
        }
        else
        {
            int k;
            std::cin >> k;
            std::cout << seg.kthOne(k + 1) - 1 << '\n';
        }
    }

    return 0;
}
