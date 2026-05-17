#include <iostream>
#include <vector>

class SegmentTree {
private:
    std::vector<long long> tree;
    int n;

    void update(int node, int l, int r, int idx, long long delta) {
        if (l == r) {
            tree[node] += delta;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) {
            update(node * 2, l, mid, idx, delta);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, delta);
        }
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    auto query(int node, int l, int r, int ql, int qr) -> long long {
        if (ql > qr) return 0;
        if (ql == l && qr == r) {
            return tree[node];
        }
        const int mid = (l + r) / 2;
        long long res = 0;
        if (ql <= mid) {
            res += query(node * 2, l, mid, ql, std::min(qr, mid));
        }
        if (qr > mid) {
            res += query(node * 2 + 1, mid + 1, r, std::max(ql, mid + 1), qr);
        }
        return res;
    }

public:
    explicit SegmentTree(int size) : n(size) {
        tree.resize(4LL * n, 0);
    }

    void update(int idx, long long delta) {
        update(1, 0, n - 1, idx, delta);
    }

    auto prefix_sum(int idx) -> long long {
        if (idx < 0) return 0;
        return query(1, 0, n - 1, 0, idx);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    // Дерево отрезков для разностного массива d[0..n-1]
    // (d[n] не используется, так как i < n)
    SegmentTree st(n + 1); // на всякий случай выделим n+1

    while (m--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int l, r;
            long long v;
            std::cin >> l >> r >> v;
            st.update(l, v);
            if (r < n) {
                st.update(r, -v);
            }
        } else {
            int i;
            std::cin >> i;
            std::cout << st.prefix_sum(i) << '\n';
        }
    }

    return 0;
}