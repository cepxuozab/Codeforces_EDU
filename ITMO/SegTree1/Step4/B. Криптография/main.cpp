#include <iostream>
#include <vector>
#include <cstdint>

class Matrix2x2 {
public:
    std::int64_t a11{};
    std::int64_t a12{};
    std::int64_t a21{};
    std::int64_t a22{};

    Matrix2x2() = default;

    Matrix2x2(std::int64_t m11, std::int64_t m12,
              std::int64_t m21, std::int64_t m22)
        : a11(m11), a12(m12), a21(m21), a22(m22) {}

    [[nodiscard]] auto multiply(const Matrix2x2& other, std::int64_t mod) const -> Matrix2x2 {
        return {
            (a11 * other.a11 + a12 * other.a21) % mod,
            (a11 * other.a12 + a12 * other.a22) % mod,
            (a21 * other.a11 + a22 * other.a21) % mod,
            (a21 * other.a12 + a22 * other.a22) % mod
        };
    }

    static auto identity() -> Matrix2x2 {
        return {1, 0, 0, 1};
    }
};

class SegmentTree {
public:
    SegmentTree(std::vector<Matrix2x2> data, std::int64_t modulus)
        : data_(std::move(data)), mod_(modulus)
    {
        tree_.resize(data_.size() * 4);
        build(1, 0, static_cast<int>(data_.size()) - 1);
    }

    [[nodiscard]] auto query(int left, int right) const -> Matrix2x2 {
        return query_impl(1, 0, static_cast<int>(data_.size()) - 1, left, right);
    }

private:
    std::vector<Matrix2x2> data_;
    std::vector<Matrix2x2> tree_;
    std::int64_t mod_;

    [[nodiscard]] static auto get_middle(int left, int right) -> int {
        return left + (right - left) / 2;
    }

    auto build(int node, int left, int right) -> void {
        if (left == right) {
            tree_[node] = data_[left];
        } else {
            int mid = get_middle(left, right);
            build(node * 2, left, mid);
            build(node * 2 + 1, mid + 1, right);
            tree_[node] = tree_[node * 2].multiply(tree_[node * 2 + 1], mod_);
        }
    }

    [[nodiscard]] auto query_impl(int node, int seg_left, int seg_right,
                    int query_left, int query_right) const -> Matrix2x2
    {
        if (seg_right < query_left || seg_left > query_right) {
            return Matrix2x2::identity();
        }

        if (query_left <= seg_left && seg_right <= query_right) {
            return tree_[node];
        }

        int mid = get_middle(seg_left, seg_right);
        Matrix2x2 left_result =
            query_impl(node * 2, seg_left, mid, query_left, query_right);
        Matrix2x2 right_result =
            query_impl(node * 2 + 1, mid + 1, seg_right, query_left, query_right);

        return left_result.multiply(right_result, mod_);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int modulus = 0;
    int matrix_count = 0;
    int query_count = 0;

    std::cin >> modulus >> matrix_count >> query_count;

    std::vector<Matrix2x2> matrices(static_cast<std::size_t>(matrix_count));

    for (int i = 0; i < matrix_count; ++i) {
        std::int64_t a11, a12, a21, a22;
        std::cin >> a11 >> a12 >> a21 >> a22;
        matrices[i] = Matrix2x2(a11, a12, a21, a22);
    }

    SegmentTree segment_tree(matrices, modulus);

    for (int i = 0; i < query_count; ++i) {
        int left = 0;
        int right = 0;
        std::cin >> left >> right;

        Matrix2x2 result =
            segment_tree.query(left - 1, right - 1);

        std::cout << result.a11 << " " << result.a12 << '\n';
        std::cout << result.a21 << " " << result.a22 << '\n';

        if (i + 1 < query_count) {
            std::cout << '\n';
        }
    }

    return 0;
}