#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <utility>

auto calc_z(std::string_view str) -> std::vector<int>
{
    std::vector<int> z(str.size());
    for (int i = 1, l = 0, r = 0; std::cmp_less(i, str.size()); ++i)
    {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);
        while (std::cmp_less(i + z[i], str.size()) && str[z[i]] == str[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

auto main() -> int
{
    std::string str;
    std::cin >> str;
    auto z_func = calc_z(str);
    for (int i : z_func)std::cout << i << ' ';
}
