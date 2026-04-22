#include <iostream>
#include <vector>
#include <span>
#include <utility>

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


auto main() -> int
{
    int n;
    long long s;
    std::cin >> n >> s;
    std::vector<int> arr(n);
    for (int& i : arr)std::cin >> i;
    std::cout << count_small_sum_segment(arr, s);
}
