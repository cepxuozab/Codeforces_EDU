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
#include <unordered_map>
#include <span>

auto count_good_segments(std::span<const int> arr, int k) -> long long
{
    if (k < 0) return 0;
    if (k == 0) return 0; // отрезок должен содержать хотя бы 1 элемент, а различных 0 — невозможно

    std::unordered_map<int, int> freq;
    long long ans = 0;
    size_t left = 0;

    for (size_t right = 0; right < arr.size(); ++right)
    {
        freq[arr[right]]++;

        while (freq.size() > static_cast<size_t>(k))
        {
            freq[arr[left]]--;
            if (freq[arr[left]] == 0)
                freq.erase(arr[left]);
            ++left;
        }

        ans += static_cast<long long>(right - left + 1);
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
    std::cout << count_good_segments(arr, s);
}
