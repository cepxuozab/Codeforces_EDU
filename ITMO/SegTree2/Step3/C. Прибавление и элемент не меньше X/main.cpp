#include <algorithm>
#include <iostream>
#include <vector>

struct SegTree {
    int n;
    std::vector<long long> lazy;
    std::vector<long long> maxVal;

    explicit SegTree(int n) : n(n), lazy(n * 4, 0), maxVal(n * 4, 0) {}

private:
    void applyNode(int rt, long long v) {
        lazy[rt]   += v;
        maxVal[rt] += v;
    }

    void pushUp(int rt) {
        maxVal[rt] = std::max(maxVal[rt * 2], maxVal[rt * 2 + 1]);
    }

    void pushDown(int rt) {
        if (lazy[rt]) {
            applyNode(rt * 2,     lazy[rt]);
            applyNode(rt * 2 + 1, lazy[rt]);
            lazy[rt] = 0;
        }
    }

    void update(int rt, int l, int r, int L, int R, long long v) {
        if (L <= l && r <= R) {
            applyNode(rt, v);
            return;
        }
        pushDown(rt);
        int m = (l + r) / 2;
        if (L <= m) update(rt * 2,     l,     m, L, R, v);
        if (R > m)  update(rt * 2 + 1, m + 1, r, L, R, v);
        pushUp(rt);
    }

    int findFirst(int rt, int l, int r, int L, long long x) {
        if (r < L || maxVal[rt] < x) return -1;
        if (l == r) return l;
        pushDown(rt);
        int m = (l + r) / 2;
        int res = findFirst(rt * 2, l, m, L, x);
        if (res == -1) res = findFirst(rt * 2 + 1, m + 1, r, L, x);
        return res;
    }

public:
    void update(int L, int R, long long v) {
        update(1, 1, n, L, R, v);
    }

    int findFirst(int L, long long x) {
        return findFirst(1, 1, n, L, x);
    }
};

int main() {
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
            seg.update(l + 1, r, v);
        } else {
            long long x;
            int l;
            std::cin >> x >> l;
            int res = seg.findFirst(l + 1, x);
            std::cout << (res == -1 ? -1 : res - 1) << '\n';
        }
    }

    return 0;
}