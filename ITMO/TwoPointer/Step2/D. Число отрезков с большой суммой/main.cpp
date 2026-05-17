#include <iostream>
#include <vector>
#include <span>
#include <utility>

auto small_sum_segment(std::span<int> arr, long long s) -> int
{
    int ans = 0;
    int left = 0;
    long long sum = 0;
    for (int right = 0; std::cmp_less(right, arr.size()); ++right)
    {
        sum += arr[right];
        while (sum > s)
        {
            sum -= arr[left];
            left++;
        }
        ans = std::max(ans, right - left + 1);
    }
    return ans;
}

auto count_small_sum_segment(std::span<int> arr, long long s) -> long long
{
    long long ans = 0;
    int left = 0;
    long long sum = 0;
    for (int right = 0; std::cmp_less(right, arr.size()); ++right)
    {
        sum += arr[right];
        while (sum > s)
        {
            sum -= arr[left];
            left++;
        }
        ans += right - left + 1;
    }
    return ans;
}
auto count_small_equal_sum_segment(std::span<int> arr, long long s) -> long long
{
    long long ans = 0;
    int left = 0;
    long long sum = 0;
    for (int right = 0; std::cmp_less(right, arr.size()); ++right)
    {
        sum += arr[right];
        while (sum >= s)
        {
            sum -= arr[left];
            left++;
        }
        ans += right - left + 1;
    }
    return ans;
}

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

auto count_great_sum_segment(std::span<int> arr, long long s) -> long long
{
    auto bad = count_small_equal_sum_segment(arr,s);
    long long total = arr.size() * (arr.size() + 1) / 2;
    return total - bad;
}

auto main() -> int
{
    int n;
    long long s;
    std::cin >> n >> s;
    std::vector<int> arr(n);
    for (int& i : arr)std::cin >> i;
    std::cout << count_great_sum_segment(arr, s);
}
