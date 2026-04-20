#include <iostream>
#include <vector>

void buildRegularGraph(int n, int k) {
    std::vector<std::pair<int, int>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k / 2; j++) {
            int neighbor = (i + j) % n;
            edges.emplace_back(i + 1, neighbor + 1); // +1 дл€ нумерации с 1
        }
    }

    // ≈сли k нечетное, нужно добавить "диаметральные" ребра
    if (k % 2 == 1) {
        for (int i = 0; i < n / 2; i++) {
            edges.emplace_back(i + 1, i + n / 2 + 1);
        }
    }

    std::cout << "YES\n" << edges.size() << "\n";
    for (auto const& [from, to] : edges) {
        std::cout << from << " " << to << "\n";
    }
}

auto main() -> int { // NOLINT
    int t;
    std::cin >> t;

    while (t--) {
        int n, k;
        std::cin >> n >> k;
        // ѕроверка условий существовани€
        if (k >= n) {
            std::cout << "NO\n";
            continue;
        }

        if ((n * k) % 2 != 0) {
            std::cout << "NO\n";
            continue;
        }

        // ќсобый случай: если k нечетное, n должно быть четным
        if (k % 2 == 1 && n % 2 != 0) {
            std::cout << "NO\n";
            continue;
        }

        buildRegularGraph(n, k);
    }

    return 0;
}
