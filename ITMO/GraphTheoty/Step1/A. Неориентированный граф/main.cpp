#include <iostream>
#include <vector>
#include <algorithm>
#include <span>
#include <set>


auto is_graph(std::span<std::pair<int, int>> edges) -> const char*
{
    std::set<std::pair<int, int>> used;
    for (auto const& [a,b] : edges)
    {
        if (a == b)return "NO";
        auto [x,y] = std::minmax(a, b);
        if (!used.emplace(x, y).second)return "NO";
    }
    return "YES";
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
        puts(is_graph(edges));
    }
}
