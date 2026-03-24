#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    for (int i = 0; i < k; ++i) {
        int query;
        std::cin >> query;

        auto it = std::ranges::lower_bound(arr, query);

        auto index = std::distance(arr.begin(), it) + 1;
        std::cout << index << "\n";
    }

    return 0;
}