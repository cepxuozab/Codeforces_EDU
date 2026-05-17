#include <iostream>
#include <algorithm>
#include <vector>
#include <span>

auto bin_search(std::span<int> arr, int target) -> const char*
{
    if (arr.empty())return "NO";
    int left = 0, right = static_cast<int>(arr.size()) - 1;
    while (left <= right)
    {
        auto mid = left + (right - left) / 2;
        if (arr[mid] == target)return "YES";
        arr[mid] < target ? left = mid + 1 : right = mid - 1;
    }
    return "NO";
}

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int num;
    std::cin >> num;
    std::vector<int> arr(n);
    for (int& a : arr)std::cin >> a;
    std::ranges::sort(arr);

    for (int i = 0; i < num; ++i)
    {
        int target;
        std::cin >> target;
        puts(bin_search(arr, target));
    }
}
