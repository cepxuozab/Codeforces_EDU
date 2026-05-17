#include <iostream>
#include <set>
#include <vector>

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<int>> adj_out(n + 1);

        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            adj_out[u].push_back(v);
        }

        for (int v = 1; v <= n; v++) {
            std::set<int> reachable;

            for (int x : adj_out[v]) {
                auto const& arr = adj_out[x];
                reachable.insert(arr.begin(), arr.end());
            }

            for (int u : reachable) {
                std::cout << u << ' ';
            }
            std::cout << '\n';
        }
    }

    return 0;
}
