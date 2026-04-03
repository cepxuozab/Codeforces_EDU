#include <iostream>
#include <vector>
#include <span>


auto degrees(std::span<std::pair<int, int>> edges, int vertex) -> std::vector<int>
{
    std::vector<int> ans(vertex);
    for (auto const& [a,b] : edges)
    {
        ans[a - 1]++;
        ans[b - 1]++;
    }
    return ans;
}

auto main() -> int
{
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
    {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::pair<int, int>> edges(m);
        for (auto& [a,b] : edges)std::cin >> a >> b;
        auto ans = degrees(edges, n);
        for (int u : ans)std::cout << u << ' ';
        std::cout << '\n';
    }
}
