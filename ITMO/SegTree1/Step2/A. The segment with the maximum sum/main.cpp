#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct Node {
    int64_t sum_{}, pre_{}, suf_{}, sub_{};
    Node() = default;
    explicit Node(int64_t x);
    Node(const Node &l, const Node &r);
};

class SegmentTree {
    int n_{};
    std::vector<Node> segment_tree_;

public:
    explicit SegmentTree(int n);
    explicit SegmentTree(std::vector<int> const &a);
    void Update(int i, int64_t x);
    [[nodiscard]] auto MaximumSubarraySum() const -> int64_t;

private:
    void Build(std::vector<int> const &a, int node, int start, int end);
    static auto Left(int node) -> int;
    static auto Right(int node) -> int;
    void Apply(int node, int64_t value);
    void Update(int node, int start, int end, int i, int64_t x);
};

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int &x: a)
        std::cin >> x;
    SegmentTree segment_tree(a);
    std::cout << segment_tree.MaximumSubarraySum() << '\n';
    for (int i = 0; i < q; ++i) {
        int idx, x;
        std::cin >> idx >> x;
        segment_tree.Update(idx, x);
        std::cout << segment_tree.MaximumSubarraySum() << '\n';
    }

    return 0;
}

Node::Node(int64_t x) : sum_(x), pre_(x > 0 ? x : 0), suf_(x > 0 ? x : 0), sub_(x > 0 ? x : 0) {}

Node::Node(const Node &l, const Node &r) {
    sum_ = l.sum_ + r.sum_;
    pre_ = std::max(l.pre_, l.sum_ + r.pre_);
    suf_ = std::max(r.suf_, r.sum_ + l.suf_);
    sub_ = std::max({l.sub_, r.sub_, l.suf_ + r.pre_});
}

SegmentTree::SegmentTree(int n) : n_(n), segment_tree_(4LL * n) {}

auto SegmentTree::Left(int node) -> int { return 2 * node; }

auto SegmentTree::Right(int node) -> int { return 2 * node + 1; }

SegmentTree::SegmentTree(std::vector<int> const &a) : SegmentTree(static_cast<int>(a.size())) {
    Build(a, 1, 0, n_ - 1);
}

void SegmentTree::Build(std::vector<int> const &a, int node, int start, int end) {
    if (start == end) {
        segment_tree_[node] = Node(a[start]);
        return;
    }
    int const mid = (start + end) / 2;
    Build(a, Left(node), start, mid);
    Build(a, Right(node), mid + 1, end);
    segment_tree_[node] = Node(segment_tree_[Left(node)], segment_tree_[Right(node)]);
}

void SegmentTree::Apply(int node, int64_t value) { segment_tree_[node] = Node(value); }

void SegmentTree::Update(int node, int start, int end, int i, int64_t x) {
    if (start == end) {
        Apply(node, x);
        return;
    }

    if (int const mid = (start + end) / 2; i <= mid)
        Update(Left(node), start, mid, i, x);
    else
        Update(Right(node), mid + 1, end, i, x);
    segment_tree_[node] = Node(segment_tree_[Left(node)], segment_tree_[Right(node)]);
}

void SegmentTree::Update(int i, int64_t x) { Update(1, 0, n_ - 1, i, x); }

auto SegmentTree::MaximumSubarraySum() const -> int64_t { return segment_tree_[1].sub_; }