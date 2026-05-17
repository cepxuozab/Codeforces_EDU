#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

struct Node {
    int min_val;
    int count;

    Node() : min_val(INT_MAX), count(0) {}
    Node(int val) : min_val(val), count(1) {}
    Node(int val, int cnt):min_val(val),count(cnt){}
};

class SegmentTree {
private:
    std::vector<Node> tree;
    std::vector<int> arr;
    int n = 0;

    void build_impl(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = Node(arr[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build_impl(v * 2, tl, tm);
            build_impl(v * 2 + 1, tm + 1, tr);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    static auto combine(const Node& left, const Node& right) -> Node {
        if (left.min_val < right.min_val) {
            return left;
        } else if (right.min_val < left.min_val) {
            return right;
        } else {
            return {left.min_val, left.count + right.count};
        }
    }

    void update_impl(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = Node(new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update_impl(v * 2, tl, tm, pos, new_val);
            } else {
                update_impl(v * 2 + 1, tm + 1, tr, pos, new_val);
            }
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
        }
    }

    auto query_impl(int v, int tl, int tr, int l, int r) -> Node {
        if (l > r) {
            return {}; // neutral element
        }
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        Node left_res = query_impl(v * 2, tl, tm, l, std::min(r, tm));
        Node right_res = query_impl(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
        if (left_res.count == 0) return right_res;
        if (right_res.count == 0) return left_res;
        return combine(left_res, right_res);
    }

public:
    void init(int size) {
        n = size;
        arr.assign(n, 0);
        tree.resize(4LL * n);
    }

    void build(const std::vector<int>& input_arr) {
        arr = input_arr;
        build_impl(1, 0, n - 1);
    }

    void update(int pos, int new_val) {
        update_impl(1, 0, n - 1, pos, new_val);
        arr[pos] = new_val;
    }

    auto number_of_minima(int left, int right) -> std::pair<int, int> {
        // Query on [left, right)
        Node res = query_impl(1, 0, n - 1, left, right - 1);
        return {res.min_val, res.count};
    }
};

// Пример использования в main (для проверки):

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    SegmentTree st;
    st.init(n);
    st.build(a);

    for (int i = 0; i < m; ++i) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int idx, val;
            std::cin >> idx >> val;
            st.update(idx, val);
        } else if (op == 2) {
            int l, r;
            std::cin >> l >> r;
            auto [min_val, cnt] = st.number_of_minima(l, r);
            std::cout << min_val << " " << cnt << "\n";
        }
    }

    return 0;
}
