#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class DSU {
    std::vector<int> parent_;
    std::vector<int> size_;

public:
    explicit DSU(int n) : parent_(n + 1), size_(n + 1, 1) {
        std::ranges::iota(parent_, 0);
    }

    auto find(int v) -> int {
        return parent_[v] == v ? v : parent_[v] = find(parent_[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size_[a] < size_[b]) std::swap(a, b);
        parent_[b] = a;
        size_[a] += size_[b];
    }
};

auto solveTestCase() -> bool {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<bool> is_selected(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int v;
        std::cin >> v;
        is_selected[v] = true;
    }

    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        dsu.unite(u, v);
    }

    std::vector<std::vector<int>> components(n + 1);
    for (int v = 1; v <= n; ++v) {
        components[dsu.find(v)].push_back(v);
    }

    for (const auto& comp : components) {
        if (comp.empty()) continue;
        const bool has_selected = std::ranges::any_of(comp, [&is_selected](int v) -> bool { return is_selected[v]; });
        const bool has_unselected = std::ranges::any_of(comp, [&is_selected](int v)->bool { return !is_selected[v]; });
        if (has_selected && has_unselected) return false;
    }
    return true;
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        std::cout << (solveTestCase() ? "YES\n" : "NO\n");
    }
    return 0;
}