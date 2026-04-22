#include <iostream>
#include <vector>
#include <span>

auto less_them(std::span<const int> lhs, std::span<const int> rhs) -> std::vector<int>
{
    std::vector<int> ans;
    ans.reserve(rhs.size());
    for (size_t i = 0, j = 0; i < rhs.size(); ++i)
    {
        while (j < lhs.size() && lhs[j] < rhs[i])j++;
        ans.emplace_back(j);
    }
    return ans;
}

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> lhs(n), rhs(m);
    for (auto& i : lhs)std::cin >> i;
    for (auto& i : rhs)std::cin >> i;
    for (const auto res = less_them(lhs, rhs); int i : res)std::cout << i << ' ';
}