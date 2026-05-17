#include <algorithm>
#include <functional>
#include <iostream>
#include <span>
#include <utility>
#include <vector>

using Edge = std::pair<int, int>;
using VertexDegree = std::pair<int, int>;

auto constructGraph(std::span<const int> degree_sequence) -> std::vector<Edge> {
    const auto n = static_cast<int>(degree_sequence.size());

    std::vector<VertexDegree> degrees;
    degrees.reserve(n);
    for (auto i = 0; i < n; ++i) {
        degrees.emplace_back(degree_sequence[i], i + 1);
    }

    std::vector<Edge> edges;
    edges.reserve(n);

    while (!std::ranges::all_of(degrees, [](const VertexDegree& p) -> bool { return p.first == 0; })) {
        std::ranges::sort(degrees, std::greater<>{}, &VertexDegree::first);

        const auto [max_degree, vertex] = degrees[0];
        if (max_degree == 0) break;

        for (auto i = 1; i <= max_degree && i < n; ++i) {
            if (degrees[i].first == 0) break;
            edges.emplace_back(vertex, degrees[i].second);
            --degrees[i].first;
        }
        degrees[0].first = 0;
    }

    return edges;
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> degrees(n);
        for (auto& d : degrees) {
            std::cin >> d;
        }

        const auto edges = constructGraph(degrees);

        std::cout << edges.size() << '\n';
        for (const auto& [u, v] : edges) {
            std::cout << u << ' ' << v << '\n';
        }
    }

    return 0;
}