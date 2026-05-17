#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_A = 40;

struct Node {
    array<int, MAX_A + 1> cnt{};
    long long inv = 0;

    Node() = default;

    static auto leaf(int value) -> Node {
        Node n;
        n.cnt[value] = 1;
        return n;
    }
};

auto merge_nodes(const Node& L, const Node& R) -> Node {
    Node res;
    for (int i = 1; i <= MAX_A; ++i) {
        res.cnt[i] = L.cnt[i] + R.cnt[i];
    }

    // Префиксные суммы для R
    array<int, MAX_A + 1> pref{};
    for (int i = 1; i <= MAX_A; ++i) {
        pref[i] = pref[i - 1] + R.cnt[i];
    }

    long long cross = 0;
    for (int x = 2; x <= MAX_A; ++x) {
        cross += 1LL * L.cnt[x] * pref[x - 1];
    }

    res.inv = L.inv + R.inv + cross;
    return res;
}

class SegTree {
private:
    vector<Node> t;
    int n;

    void build(int v, int tl, int tr, const vector<int>& arr) {
        if (tl == tr) {
            t[v] = Node::leaf(arr[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, arr);
            build(v * 2 + 1, tm + 1, tr, arr);
            t[v] = merge_nodes(t[v * 2], t[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] = Node::leaf(val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v * 2, tl, tm, pos, val);
            else
                update(v * 2 + 1, tm + 1, tr, pos, val);
            t[v] = merge_nodes(t[v * 2], t[v * 2 + 1]);
        }
    }

    auto query(int v, int tl, int tr, int l, int r) -> Node {
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        if (r <= tm) {
            return query(v * 2, tl, tm, l, r);
        } else if (l > tm) {
            return query(v * 2 + 1, tm + 1, tr, l, r);
        } else {
            Node left_node = query(v * 2, tl, tm, l, tm);
            Node right_node = query(v * 2 + 1, tm + 1, tr, tm + 1, r);
            return merge_nodes(left_node, right_node);
        }
    }

public:
    explicit SegTree(const vector<int>& arr) : n((int)arr.size()) {
        t.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    void update(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }

    auto query_inv(int l, int r) -> long long {
        Node res = query(1, 0, n - 1, l, r);
        return res.inv;
    }
};

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegTree st(a);

    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            // query inversions on [x, y] (1-indexed)
            cout << st.query_inv(x - 1, y - 1) << '\n';
        } else {
            // update position x to value y
            st.update(x - 1, y);
        }
    }

    return 0;
}