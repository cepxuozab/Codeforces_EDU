#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

struct Graph {
    int n;
    int maxEdges;
    std::vector<std::vector<std::pair<int, long long>>> adjacency;

    Graph(int vertices, int maxD)
        : n(vertices)
        , maxEdges(maxD)
        , adjacency(vertices + 1) {}

    void addEdge(int from, int to, long long weight) {
        adjacency[from].emplace_back(to, weight);
    }

    bool canReachWithMaxWeight(long long maxWeight, std::vector<int>& predecessor) const {
        predecessor.assign(n + 1, -1);
        std::queue<std::pair<int, int>> q; // (steps, vertex)
        q.emplace(0, 1);
        predecessor[1] = 0;

        while (!q.empty()) {
            auto [steps, vertex] = q.front();
            q.pop();

            for (const auto& [nextVertex, weight] : adjacency[vertex]) {
                if (weight > maxWeight) continue;
                if (predecessor[nextVertex] != -1) continue;
                if (steps + 1 > maxEdges) continue;

                q.emplace(steps + 1, nextVertex);
                predecessor[nextVertex] = vertex;
            }
        }

        return predecessor[n] != -1;
    }
};

struct PathFinder {
    const Graph& graph;
    std::vector<int> path;

    PathFinder(const Graph& g) : graph(g) {}

    long long findMinMaxWeight() {
        long long left = 0;
        long long right = 1'000'000'000; // maximum possible weight

        std::vector<int> predecessor;

        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (graph.canReachWithMaxWeight(mid, predecessor)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        // Reconstruct path with the optimal max weight
        if (graph.canReachWithMaxWeight(right, predecessor)) {
            path.clear();
            int current = graph.n;
            path.push_back(current);
            while (current != 1) {
                current = predecessor[current];
                path.push_back(current);
            }
            std::reverse(path.begin(), path.end());
        }

        return right;
    }

    void printResult() const {
        if (path.empty()) {
            printf("-1\n");
        } else {
            int edges = static_cast<int>(path.size()) - 1;
            printf("%d\n", edges);
            for (size_t i = 0; i < path.size(); i++) {
                printf("%d%c", path[i], i + 1 == path.size() ? '\n' : ' ');
            }
        }
    }
};

int main() {
    int n, m, d;
    if (scanf("%d%d%d", &n, &m, &d) != 3) {
        return 1;
    }

    Graph graph(n, d);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        if (scanf("%d%d%lld", &a, &b, &c) != 3) {
            return 1;
        }
        graph.addEdge(a, b, c);
    }

    PathFinder finder(graph);
    finder.findMinMaxWeight();
    finder.printResult();

    return 0;
}