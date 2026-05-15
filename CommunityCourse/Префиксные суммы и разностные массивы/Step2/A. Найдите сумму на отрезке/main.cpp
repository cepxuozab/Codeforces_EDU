#include <iostream>
#include <vector>
#include <span>
#include <cstdint>

auto prefix_sum(std::span<const int> arr) -> std::vector<int64_t>
{
    std::vector<int64_t> prefix{0};
    for (int i : arr) prefix.push_back(prefix.back() + i);
    return prefix;
}

auto main() -> int //NOLINT
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& i : arr) std::cin >> i;
    auto const prefix = prefix_sum(arr);
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << prefix[r] - prefix[l - 1] << '\n';
    }
}
