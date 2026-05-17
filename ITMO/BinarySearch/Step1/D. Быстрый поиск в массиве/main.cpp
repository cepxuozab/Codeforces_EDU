#include <iostream>
#include <algorithm>
#include <vector>

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr)std::cin >> a;
    std::ranges::sort(arr);
    int num;
    std::cin >> num;
    for (int i = 0; i < num; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        auto left = std::ranges::lower_bound(arr, l);
        auto right = std::ranges::upper_bound(arr, r);
        std::cout << std::ranges::distance(left, right) << ' ';
    }
}
