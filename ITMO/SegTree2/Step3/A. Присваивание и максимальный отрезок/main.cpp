#include <algorithm>
#include <iostream>
#include <vector>

struct Node {
    long long maxVal = 0;
    long long preVal = 0;
    long long sufVal = 0;
    long long sumVal = 0;

    void set(long long v, int len) {
        sumVal = v * len;
        preVal = sufVal = maxVal = std::max(sumVal, 0LL);
    }
};

Node merge(const Node& a, const Node& b) {
    Node ret;
    ret.sumVal = a.sumVal + b.sumVal;
    ret.preVal = std::max(a.preVal, a.sumVal + b.preVal);
    ret.sufVal = std::max(a.sufVal + b.sumVal, b.sufVal);
    ret.maxVal = std::max({a.maxVal, b.maxVal, a.sufVal + b.preVal});
    return ret;
}

struct SegTree {
    int n;
    std::vector<bool>      sign;
    std::vector<long long> signVal;
    std::vector<Node>      nodes;

    explicit SegTree(int n) : n(n), sign(n * 4, false), signVal(n * 4, 0), nodes(n * 4) {
        build(1, 1, n);
    }

private:
    void applyNode(int rt, int l, int r, long long v) {
        sign[rt]    = true;
        signVal[rt] = v;
        nodes[rt].set(v, r - l + 1);
    }

    void pushUp(int rt) {
        nodes[rt] = merge(nodes[rt * 2], nodes[rt * 2 + 1]);
    }

    void pushDown(int rt, int l, int r) {
        if (sign[rt]) {
            int m = (l + r) / 2;
            applyNode(rt * 2,     l,     m, signVal[rt]);
            applyNode(rt * 2 + 1, m + 1, r, signVal[rt]);
            sign[rt]    = false;
            signVal[rt] = 0;
        }
    }

    void build(int rt, int l, int r) {
        if (l == r) return;
        int m = (l + r) / 2;
        build(rt * 2,     l,     m);
        build(rt * 2 + 1, m + 1, r);
        pushUp(rt);
    }

    void update(int rt, int l, int r, int L, int R, long long val) {
        if (L <= l && r <= R) {
            applyNode(rt, l, r, val);
            return;
        }
        pushDown(rt, l, r);
        int m = (l + r) / 2;
        if (L <= m) update(rt * 2,     l,     m, L, R, val);
        if (R > m)  update(rt * 2 + 1, m + 1, r, L, R, val);
        pushUp(rt);
    }

    Node query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return nodes[rt];
        pushDown(rt, l, r);
        int m = (l + r) / 2;
        if (R <= m) return query(rt * 2,     l,     m, L, R);
        if (L > m)  return query(rt * 2 + 1, m + 1, r, L, R);
        return merge(query(rt * 2, l, m, L, R), query(rt * 2 + 1, m + 1, r, L, R));
    }

public:
    void update(int L, int R, long long val) {
        update(1, 1, n, L, R, val);
    }

    Node query(int L, int R) {
        return query(1, 1, n, L, R);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SegTree seg(n);

    while (m--) {
        int l, r;
        long long v;
        std::cin >> l >> r >> v;
        seg.update(l + 1, r, v);
        std::cout << seg.query(1, n).maxVal << '\n';
    }

    return 0;
}