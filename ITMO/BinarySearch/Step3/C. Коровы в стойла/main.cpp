#include <iostream>
#include <algorithm>
#include <span>
#include <vector>

auto check(std::span<int> coords, int x , int k) -> bool {
    int cows = 1;
    int last_cow = coords[0];
    for (int c : coords) {
        if (c - last_cow >= x) {
            cows++;
            last_cow = c;
        }
    }
    return cows >= k;
}

auto search(std::vector<int> coords, int k) -> int
{
    std::ranges::sort(coords);
    int l = 0;
    int r = coords.back() - coords[0] + 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(coords,m,k))
            l = m;
        else
            r = m;
    }
    return l;
}

auto main() -> int
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int& num : nums)std::cin >> num;
    std::cout << search(nums, k);
}
