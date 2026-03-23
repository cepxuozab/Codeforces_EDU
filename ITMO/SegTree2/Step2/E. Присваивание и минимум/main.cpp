#include <algorithm>
#include <iostream>
#include <vector>

struct SegTree {
    int n;
    std::vector<long long> sign;
    std::vector<long long> minVal;

    explicit SegTree(int n) : n(n), sign(n * 4, 0), minVal(n * 4, 0) {
        build(1, 1, n);
    }

private:
    void pushUp(int rt) {
        minVal[rt] = std::min(minVal[rt * 2], minVal[rt * 2 + 1]);
    }

    void pushDown(int rt) {
        if (sign[rt]) {
            sign[rt * 2]       = sign[rt];
            sign[rt * 2 + 1]   = sign[rt];
            minVal[rt * 2]     = sign[rt];
            minVal[rt * 2 + 1] = sign[rt];
            sign[rt] = 0;
        }
    }

    void build(int rt, int l, int r) {
        sign[rt] = 0;
        if (l == r) {
            minVal[rt] = 1;
            return;
        }
        int m = (l + r) / 2;
        build(rt * 2,     l,     m);
        build(rt * 2 + 1, m + 1, r);
        pushUp(rt);
    }

    void update(int rt, int l, int r, int L, int R, long long val) {
        if (L <= l && r <= R) {
            sign[rt]   = val;
            minVal[rt] = val;
            return;
        }
        pushDown(rt);
        int m = (l + r) / 2;
        if (L <= m) update(rt * 2,     l,     m, L, R, val);
        if (R > m)  update(rt * 2 + 1, m + 1, r, L, R, val);
        pushUp(rt);
    }

    auto queryMin(int rt, int l, int r, int L, int R) -> long long {
        if (L <= l && r <= R) return minVal[rt];
        pushDown(rt);
        int m = (l + r) / 2;
        long long ret = INT64_MAX;
        if (L <= m) ret = std::min(ret, queryMin(rt * 2,     l,     m, L, R));
        if (R > m)  ret = std::min(ret, queryMin(rt * 2 + 1, m + 1, r, L, R));
        return ret;
    }

public:
    void update(int L, int R, long long val) {
        update(1, 1, n, L, R, val);
    }

    auto queryMin(int L, int R) -> long long {
        return queryMin(1, 1, n, L, R);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SegTree seg(n);

    while (m--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int l, r;
            long long v;
            std::cin >> l >> r >> v;
            seg.update(l + 1, r, v + 1);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg.queryMin(l + 1, r) - 1 << '\n';
        }
    }

    return 0;
}