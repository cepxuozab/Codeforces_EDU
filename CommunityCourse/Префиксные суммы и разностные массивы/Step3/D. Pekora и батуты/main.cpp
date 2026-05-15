#include <iostream>
#include <vector>
#include <cstdint>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i)
    {
        int n;
        std::cin >> n;
        std::vector<int> arr(n);
        for (int& a : arr) std::cin >> a;
        std::vector<int64_t> curr(n+5);
        int64_t ans = 0;
        for (int x = 0; x < n; ++x)
        {
            int64_t temp = curr[x];

            if (temp < arr[x] - 1)
            {
                ans += arr[x] - 1 - temp;
                temp += arr[x] - 1 - temp;
            }

            curr[x + 1] += temp - arr[x] + 1;
            if (x + 2 < n) for (int y = x + 2; y < std::min(n, x + arr[x] + 1); ++y) curr[y]++;
        }
        std::cout << ans << '\n';
    }
}
