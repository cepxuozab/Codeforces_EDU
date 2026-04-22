#include <iostream>
#include <vector>
#include <span>
#include <utility>


auto great_sum_segment(std::span<int> arr, long long s) -> int
{
    long long sum = 0;
    int ans = INT_MAX;
    int left = 0;
    for (int right = 0; std::cmp_less(right, arr.size()); ++right)
    {
        sum += arr[right];
        while (sum - arr[left] >= s)
        {
            sum -= arr[left];
            left++;
        }
        if (sum >= s)
        {
            ans = std::min(ans, right - left + 1);
        }
    }
    return ans == INT_MAX ? -1 : ans;
}

auto main() -> int
{
    int n;
    long long s;
    std::cin >> n >> s;
    std::vector<int> arr(n);
    for (int& i : arr)std::cin >> i;
    std::cout << great_sum_segment(arr, s);
}
