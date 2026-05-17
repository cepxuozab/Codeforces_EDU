#include <iostream>
#include <vector>
#include <algorithm>

struct Fenwick {
    std::vector<int> bit;
    int n;

    explicit Fenwick(int n) : n(n) {
        bit.assign(n + 1, 0);
    }

    void update(int idx, int delta) {
        for (++idx; idx <= n; idx += idx & -idx) {
            bit[idx] += delta;
        }
    }

    auto query(int idx) -> int {
        if (idx < 0) return 0;
        if (idx >= n) idx = n - 1;
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx) {
            res += bit[idx];
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> L(n + 1, -1), R(n + 1, -1);
    for (int i = 0; i < 2 * n; ++i) {
        int x = a[i];
        if (L[x] == -1) {
            L[x] = i;
        } else {
            R[x] = i;
        }
    }

    // Создаём список индексов 1..n
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i + 1;
    }

    // Сортируем по L убыванию
    std::sort(indices.begin(), indices.end(), [&](int i, int j) {
        return L[i] > L[j];
    });

    Fenwick fenw(2 * n);
    std::vector<int> ans(n + 1, 0);

    for (int x : indices) {
        ans[x] = fenw.query(R[x] - 1);
        fenw.update(R[x], 1);
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}