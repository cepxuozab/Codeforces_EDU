#include <algorithm>
#include <iostream>
#include <vector>

auto Z_function(const std::vector<int>& s) -> std::vector<size_t>
{
    size_t n = s.size();
    std::vector<size_t> z(s.size());
    for (size_t i = 1, l = 0, r = 0; i < s.size(); i++)
    {
        if (r >= i)
        {
            z[i] = std::min(z[i - l], r - i + 1);
        }
        while (z[i] + i < n && s[z[i]] == s[z[i] + i])
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(2 * n + 1, -1);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        a[2 * n - i] = a[i];
    }
    auto z = Z_function(a);
    for (size_t i = n + 1; i < z.size(); i++)
    {
        if (z[i] % 2 == 0 && i + z[i] == a.size())
        {
            std::cout << n - z[i] / 2 << " ";
        }
    }
    std::cout << n;
    return 0;
}
