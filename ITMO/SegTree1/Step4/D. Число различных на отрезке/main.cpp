#include <bits/stdc++.h>
using namespace std;

class SegTree {
private:
    vector<uint64_t> tree;
    int n;

    void build(int v, int tl, int tr, const vector<int>& arr) {
        if (tl == tr) {
            tree[v] = (1ULL << arr[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, arr);
            build(v * 2 + 1, tm + 1, tr, arr);
            tree[v] = tree[v * 2] | tree[v * 2 + 1];
        }
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            tree[v] = (1ULL << val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(v * 2, tl, tm, pos, val);
            } else {
                update(v * 2 + 1, tm + 1, tr, pos, val);
            }
            tree[v] = tree[v * 2] | tree[v * 2 + 1];
        }
    }

    auto query(int v, int tl, int tr, int l, int r) -> uint64_t {
        if (l > r) {
            return 0;
        }
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        uint64_t left_mask = query(v * 2, tl, tm, l, min(r, tm));
        uint64_t right_mask = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
        return left_mask | right_mask;
    }

public:
    explicit SegTree(const vector<int>& arr) : n((int)arr.size()) {
        tree.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    void update(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }

    auto query_distinct(int l, int r) -> int {
        uint64_t mask = query(1, 0, n - 1, l, r);
        return __builtin_popcountll(mask);
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
            // Запрос количества различных на [x, y] (1-indexed)
            cout << st.query_distinct(x - 1, y - 1) << '\n';
        } else {
            // Обновление: a[x] = y
            st.update(x - 1, y);
        }
    }

    return 0;
}