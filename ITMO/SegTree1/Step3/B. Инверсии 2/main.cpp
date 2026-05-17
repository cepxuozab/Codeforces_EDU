#include <iostream>
#include <vector>

class SegmentTree {
private:
    std::vector<int> tree;
    int n;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node] = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    auto find_kth(int node, int l, int r, int k) -> int {
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        if (k <= tree[node * 2]) {
            return find_kth(node * 2, l, mid, k);
        } else {
            return find_kth(node * 2 + 1, mid + 1, r, k - tree[node * 2]);
        }
    }

    void update(int node, int l, int r, int idx) {
        if (l == r) {
            tree[node] = 0;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) {
            update(node * 2, l, mid, idx);
        } else {
            update(node * 2 + 1, mid + 1, r, idx);
        }
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

public:
    explicit SegmentTree(int size) : n(size) {
        tree.resize(4 * n);
        build(1, 1, n); // значения от 1 до n
    }

    auto kth_smallest(int k) -> int {
        return find_kth(1, 1, n, k);
    }

    void remove(int value) {
        update(1, 1, n, value);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    SegmentTree st(n);
    std::vector<int> ans(n);

    for (int i = n - 1; i >= 0; --i) {
        int S = i + 1;               // сколько чисел ещё не расставлено
        int k = S - a[i];            // k-е наименьшее свободное число
        int value = st.kth_smallest(k);
        ans[i] = value;
        st.remove(value);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " ";
    }
    std::cout << "\n";

    return 0;
}