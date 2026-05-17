#include <iostream>
#include <vector>
#include <cstddef>

namespace {
    constexpr long long MOD = 1'000'000'007LL;

    [[nodiscard]] constexpr auto mod_mul(long long a, long long b) noexcept -> long long {
        return (a % MOD) * (b % MOD) % MOD;
    }

    [[nodiscard]] constexpr auto mod_add(long long a, long long b) noexcept -> long long {
        long long s = a + b;
        if (s >= MOD) s -= MOD;
        if (s < 0) s += MOD;
        return s;
    }
} // anonymous namespace

struct SegmentTree {
    explicit SegmentTree(std::size_t n)
        : sum_tree{}
        , lazy_mult{} {
        while (size < n) size *= 2;
        sum_tree.assign(2 * size, 1LL);
        lazy_mult.assign(2 * size, 1LL);
        // Initial leaves [0, n) are 1; [n, size) are 0 (neutral for sum)
        for (std::size_t i = 0; i < n; ++i) {
            sum_tree[size + i] = 1;
        }
        for (std::size_t i = n; i < size; ++i) {
            sum_tree[size + i] = 0;
        }
        for (std::size_t i = size - 1; i > 0; --i) {
            sum_tree[i] = mod_add(sum_tree[2 * i], sum_tree[2 * i + 1]);
        }
    }

    void push(std::size_t node, std::size_t left, std::size_t right) {
        if (lazy_mult[node] != 1) {
            sum_tree[node] = mod_mul(sum_tree[node], lazy_mult[node]);
            if (right - left > 1) {
                lazy_mult[2 * node]     = mod_mul(lazy_mult[2 * node],     lazy_mult[node]);
                lazy_mult[2 * node + 1] = mod_mul(lazy_mult[2 * node + 1], lazy_mult[node]);
            }
            lazy_mult[node] = 1;
        }
    }

    void update_range(std::size_t node, std::size_t left, std::size_t right,
                      std::size_t l, std::size_t r, long long factor) {
        push(node, left, right);
        if (r <= left || right <= l) return;
        if (l <= left && right <= r) {
            lazy_mult[node] = mod_mul(lazy_mult[node], factor);
            push(node, left, right);
            return;
        }
        std::size_t mid = (left + right) / 2;
        update_range(2 * node,     left, mid, l, r, factor);
        update_range(2 * node + 1, mid,   right, l, r, factor);
        // After children are updated (and pushed inside recursion), combine
        long long left_sum  = sum_tree[2 * node];
        long long right_sum = sum_tree[2 * node + 1];
        // But children might still have lazy values! So we must ensure they're clean.
        // Alternative: re-push them or compute with lazy included.
        // Safer approach: query their effective value via temporary push simulation.
        // However, since we just recursed into them and they called push at entry,
        // and we don't modify them after, their sum_tree entries are up-to-date.
        sum_tree[node] = mod_add(left_sum, right_sum);
    }

    [[nodiscard]] auto query_sum(std::size_t node, std::size_t left, std::size_t right,
                                      std::size_t l, std::size_t r) const -> long long {
        if (r <= left || right <= l) return 0LL;
        if (l <= left && right <= r) {
            return mod_mul(sum_tree[node], lazy_mult[node]);
        }
        std::size_t mid = (left + right) / 2;
        long long left_val  = query_sum(2 * node,     left, mid, l, r);
        long long right_val = query_sum(2 * node + 1, mid,   right, l, r);
        long long combined = mod_add(left_val, right_val);
        return mod_mul(combined, lazy_mult[node]);
    }

    void multiply(std::size_t l, std::size_t r, long long v) {
        update_range(1, 0, size, l, r, v);
    }

    [[nodiscard]] auto sum_on(std::size_t l, std::size_t r) const -> long long {
        return query_sum(1, 0, size, l, r);
    }

private:
    std::size_t size{1};
    mutable std::vector<long long> sum_tree;
    mutable std::vector<long long> lazy_mult;
};

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n, m;
    std::cin >> n >> m;

    SegmentTree segtree{n};

    for (std::size_t i = 0; i < m; ++i) {
        int op;
        std::cin >> op;
        if (op == 1) {
            std::size_t l, r;
            long long v;
            std::cin >> l >> r >> v;
            segtree.multiply(l, r, v % MOD);
        } else if (op == 2) {
            std::size_t l, r;
            std::cin >> l >> r;
            std::cout << segtree.sum_on(l, r) << '\n';
        }
    }

    return 0;
}