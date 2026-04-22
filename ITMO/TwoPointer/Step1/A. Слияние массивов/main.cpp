#include <iostream>
#include <vector>
#include <span>

auto merge_array(std::span<int> lhs, std::span<int> rhs) -> std::vector<int>
{
    std::vector<int> ans;
    ans.reserve(lhs.size() + rhs.size());
    size_t i = 0, j = 0;
    while (i < lhs.size() && j < rhs.size())
    {
        if (lhs[i] < rhs[j])
        {
            ans.push_back(lhs[i]);
            i++;
        }
        else
        {
            ans.push_back(rhs[j]);
            j++;
        }
    }
    while (i < lhs.size())ans.push_back(lhs[i++]);
    while (j < rhs.size())ans.push_back(rhs[j++]);
    return ans;
}

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> lhs(n), rhs(m);
    for (auto& i : lhs)std::cin >> i;
    for (auto& i : rhs)std::cin >> i;
    auto res = merge_array(lhs, rhs);
    for (int i : res)std::cout << i << ' ';
}
