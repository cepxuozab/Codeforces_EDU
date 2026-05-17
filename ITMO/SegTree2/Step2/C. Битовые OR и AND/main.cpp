#include <iostream>
#include <vector>
#include <cstdint>

class SegmentTree {
private:
    struct Node {
        int32_t and_value;
        int32_t or_value;
        int32_t lazy;

        Node() : and_value(0), or_value(0), lazy(0) {}
    };

    int size;
    std::vector<Node> tree;

    static Node combine(const Node& left, const Node& right) {
        Node result;
        result.and_value = left.and_value & right.and_value;
        result.or_value = left.or_value | right.or_value;
        result.lazy = 0;
        return result;
    }

    void apply_operation(int idx, int32_t value) {
        tree[idx].and_value |= value;
        tree[idx].or_value |= value;
        tree[idx].lazy |= value;
    }

    void push_lazy(int idx) {
        if (tree[idx].lazy != 0) {
            apply_operation(idx * 2, tree[idx].lazy);
            apply_operation(idx * 2 + 1, tree[idx].lazy);
            tree[idx].lazy = 0;
        }
    }

    void build_tree(int idx, int left, int right) {
        if (left + 1 == right) {
            tree[idx] = Node();
            return;
        }

        int mid = (left + right) / 2;
        build_tree(idx * 2, left, mid);
        build_tree(idx * 2 + 1, mid, right);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update_range(int idx, int left, int right, int ql, int qr, int32_t value) {
        if (ql >= right || qr <= left) {
            return;
        }

        if (ql <= left && right <= qr) {
            apply_operation(idx, value);
            return;
        }

        push_lazy(idx);
        int mid = (left + right) / 2;
        update_range(idx * 2, left, mid, ql, qr, value);
        update_range(idx * 2 + 1, mid, right, ql, qr, value);
        tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
    }

    int32_t query_range(int idx, int left, int right, int ql, int qr) {
        if (ql >= right || qr <= left) {
            return ~static_cast<int32_t>(0);
        }

        if (ql <= left && right <= qr) {
            return tree[idx].and_value;
        }

        push_lazy(idx);
        int mid = (left + right) / 2;
        int32_t left_result = query_range(idx * 2, left, mid, ql, qr);
        int32_t right_result = query_range(idx * 2 + 1, mid, right, ql, qr);
        return left_result & right_result;
    }

public:
    SegmentTree(int n) : size(n), tree(4 * n) {
        build_tree(1, 0, n);
    }

    void apply_or(int l, int r, int32_t value) {
        update_range(1, 0, size, l, r, value);
    }

    int32_t get_and(int l, int r) {
        return query_range(1, 0, size, l, r);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    SegmentTree seg_tree(n);

    for (int i = 0; i < m; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int l, r;
            int32_t v;
            std::cin >> l >> r >> v;
            seg_tree.apply_or(l, r, v);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << seg_tree.get_and(l, r) << '\n';
        }
    }

    return 0;
}