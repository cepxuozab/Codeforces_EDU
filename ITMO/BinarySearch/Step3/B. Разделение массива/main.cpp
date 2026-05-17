#include <iostream>
#include <algorithm>
#include <span>
#include <vector>
#include <format>

auto check(std::span<int> nums, int64_t sum, int k)
{
    int num = 0;
    int64_t pre = 0;

    for (auto v : nums)
    {
        if (sum < v) return false;
        if (pre + v > sum)
        {
            num++;
            if (num >= k) return false;
            pre = 0;
        }
        pre += v;
    }
    if (pre)
    {
        num++;
    }

    return num <= k;
}

auto search(std::span<int> nums, int k) -> int64_t
{
    int64_t left = 1, right = int64_t(nums.size()) * std::ranges::max(nums);
    while (left < right)
    {
        auto m = (left + right) / 2;
        if (check(nums, m, k))
        {
            right = m;
        }
        else
        {
            left = m + 1;
        }
    }
    return right;
}

auto main() -> int
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int& num : nums)std::cin >> num;
    std::cout << search(nums, k);
}
