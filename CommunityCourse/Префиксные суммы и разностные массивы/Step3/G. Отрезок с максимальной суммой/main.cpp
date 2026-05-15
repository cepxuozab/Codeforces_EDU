#include <iostream>
#include <vector>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (auto& i : arr) std::cin >> i;
    int max_sum = arr[0], cur_sum = arr[0], beg = 0, end = 0, tmp = 0;

    for (int i = 1; i < n; ++i)
    {
        if (cur_sum < 0)
        {
            cur_sum = arr[i];
            tmp = i;
        }
        else
            cur_sum += arr[i];

        if (cur_sum > max_sum)
        {
            max_sum = cur_sum;
            beg = tmp;
            end = i;
        }
    }
    std::cout << beg + 1 << ' ' << end + 1 << ' ' << max_sum;
}
