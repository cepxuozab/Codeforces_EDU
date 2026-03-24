#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

class Graph {
public:
    struct Edge {
        int to;
        int weight;
    };

    explicit Graph(int n) : adj_(n + 1), n_(n) {}

    void add_edge(int from, int to, int weight) {
        adj_[from].push_back({to, weight});
    }

    auto good(double M) const -> bool {
        std::vector<double> dp(n_ + 1, INF);
        dp[1] = 0.0;

        for (int i = 1; i <= n_; ++i) {
            if (dp[i] == INF) continue;
            for (const auto& e : adj_[i]) {
                dp[e.to] = std::min(dp[e.to], dp[i] + e.weight - M);
            }
        }

        return dp[n_] <= 0.0;
    }

    auto restore_path(double M) const -> std::vector<int> {
        std::vector<double> dp(n_ + 1, INF);
        std::vector<int> parent(n_ + 1, -1);

        dp[1] = 0.0;

        for (int i = 1; i <= n_; ++i) {
            if (dp[i] == INF) continue;
            for (const auto& e : adj_[i]) {
                if (dp[e.to] > dp[i] + e.weight - M) {
                    dp[e.to] = dp[i] + e.weight - M;
                    parent[e.to] = i;
                }
            }
        }

        std::vector<int> path;
        int cur = n_;

        while (cur != -1) {
            path.push_back(cur);
            if (cur == 1) break;
            cur = parent[cur];
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

private:
    static constexpr double INF = std::numeric_limits<double>::infinity();

    std::vector<std::vector<Edge>> adj_;
    int n_;
};

auto main() -> int {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        graph.add_edge(a, b, c);
    }

    double left = -1.0;
    double right = 101.0;

    for (int i = 0; i < 80; ++i) {
        double mid = (left + right) / 2.0;

        if (graph.good(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }


    std::vector<int> path = graph.restore_path(right);

    std::cout << static_cast<int>(path.size()) - 1 << '\n';
    for (int v : path) {
        std::cout << v << " ";
    }
    std::cout << '\n';

    return 0;
}