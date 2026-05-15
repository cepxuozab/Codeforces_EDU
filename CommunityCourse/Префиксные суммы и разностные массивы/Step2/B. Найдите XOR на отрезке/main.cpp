#include <iostream>
#include <vector>
#include <span>
#include <cstdint>

auto prefix_xor(std::span<const int> arr) -> std::vector<int64_t>
{
    std::vector<int64_t> prefix{0};
    prefix.reserve(arr.size() + 1);
    for (int i : arr) prefix.push_back(prefix.back() ^ i);
    return prefix;
}

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& i : arr) std::cin >> i;
    auto const prefix = prefix_xor(arr);
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << (prefix[r] ^ prefix[l - 1]) << '\n';
    }
}
