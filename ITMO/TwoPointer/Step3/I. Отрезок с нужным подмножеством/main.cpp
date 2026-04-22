#include <iostream>
#include <vector>
#include <algorithm>


auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, s;
    std::cin >> n >> s;
    std::vector<int> a(n);
    for (auto& i : a) std::cin >> i;

    int ans = INT_MAX;

    std::vector<int> prev(s + 1, INT_MAX);
    std::vector<int> curr(s + 1, INT_MAX);

    for (int i = 0; i < n; ++i)
    {
        std::ranges::fill(curr, INT_MAX);

        // База: отрезок из одного элемента [i, i]
        if (a[i] <= s)
        {
            curr[a[i]] = 1;
        }
        curr[0] = 0; // пустое подмножество

        if (i > 0)
        {
            // Переносим DP с предыдущей позиции
            for (int sum = 0; sum <= s; ++sum)
            {
                if (prev[sum] != INT_MAX)
                {
                    // Не используем a[i]
                    curr[sum] = std::min(curr[sum], prev[sum] + 1);

                    // Используем a[i]
                    if (sum + a[i] <= s)
                    {
                        curr[sum + a[i]] = std::min(curr[sum + a[i]], prev[sum] + 1);
                    }
                }
            }
        }

        ans = std::min(ans, curr[s]);

        swap(prev, curr);
    }

    std::cout << (ans == INT_MAX ? -1 : ans) << '\n';
    return 0;
}
