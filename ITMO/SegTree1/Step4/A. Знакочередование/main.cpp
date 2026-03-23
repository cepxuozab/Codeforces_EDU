#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long s0; // alternating sum starting with +
    long long s1; // alternating sum starting with -
    int len;      // length of the segment
};

class SegTree {
public:
    vector<Node> tree;
    vector<long long> arr;
    int n;

    SegTree(const vector<long long>& input) : arr(input), n(input.size()) {
        tree.resize(4LL * n);
        build(0, 0, n - 1);
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = { .s0=arr[tl], .s1=-arr[tl], .len=1 };
        } else {
            const int tm = (tl + tr) / 2;
            build(2*v+1, tl, tm);
            build(2*v+2, tm+1, tr);
            tree[v] = merge(tree[2*v+1], tree[2*v+2]);
        }
    }

    void update(int v, int tl, int tr, int pos, long long val) {
        if (tl == tr) {
            arr[pos] = val;
            tree[v] = { .s0=val, .s1=-val, .len=1 };
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(2*v+1, tl, tm, pos, val);
            } else {
                update(2*v+2, tm+1, tr, pos, val);
            }
            tree[v] = merge(tree[2*v+1], tree[2*v+2]);
        }
    }

    [[nodiscard]] auto query(int v, int tl, int tr, int l, int r) const  -> Node {
        if (l > r) {
            return {.s0=0, .s1=0, .len=0};
        }
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        const Node left_res = query(2*v+1, tl, tm, l, min(r, tm));
        const Node right_res = query(2*v+2, tm+1, tr, max(l, tm+1), r);
        if (left_res.len == 0) return right_res;
        if (right_res.len == 0) return left_res;
        return merge(left_res, right_res);
    }

    void update(int pos, long long val) {
        update(0, 0, n - 1, pos, val);
    }

    [[nodiscard]] auto query_sum(int l, int r) const -> long long {
        const Node res = query(0, 0, n - 1, l, r);
        return res.s0;
    }

private:
    static auto merge(const Node& left, const Node& right) -> Node {
        Node res;
        res.len = left.len + right.len;
        if (left.len % 2 == 0) {
            res.s0 = left.s0 + right.s0;
            res.s1 = left.s1 + right.s1;
        } else {
            res.s0 = left.s0 + right.s1;
            res.s1 = left.s1 + right.s0;
        }
        return res;
    }
};

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegTree st(a);

    int m;
    cin >> m;
    while (m--) {
        int op;
        cin >> op;
        if (op == 0) {
            int i, j;
            cin >> i >> j;
            st.update(i - 1, j); // to 0-indexed
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query_sum(l - 1, r - 1) << '\n';
        }
    }

    return 0;
}