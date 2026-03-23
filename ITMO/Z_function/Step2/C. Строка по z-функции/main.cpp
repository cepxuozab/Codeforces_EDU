#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <utility>
#include <span>

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


auto build_string(std::span<const int> z, std::string_view alphabet) -> std::string
{
    std::string s;
    int prefixLength = 0;
    int j = 0;
    int newCharacter = 0;

    for (int zi : z)
    {
        // range-based for loop
        if (zi == 0 && prefixLength == 0)
        {
            if (std::cmp_less(newCharacter, alphabet.size()))
            {
                s += alphabet[newCharacter];
                ++newCharacter;
            }
            else
            {
                s += alphabet.back(); 
            }
        }

        if (zi > prefixLength)
        {
            prefixLength = zi;
            j = 0;
        }

        if (prefixLength > 0)
        {
            if (std::cmp_greater_equal(j,s.size())) return "1";
            s += s[j];
            ++j;
            --prefixLength;
        }
    }

    return s;
}


auto main() -> int
{
    std::string_view alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int sz;
        std::cin >> sz;
        std::vector<int> arr(sz);
        for (int& a : arr)std::cin >> a;
        auto str = build_string(arr, alphabet);
        auto tmp = calc_z(str);
        if (tmp != arr) std::cout << '!' << '\n';
        else std::cout << str << '\n';
    }
}
