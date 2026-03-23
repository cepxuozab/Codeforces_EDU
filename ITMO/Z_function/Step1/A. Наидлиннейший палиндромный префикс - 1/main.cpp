#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

constexpr auto is_palindrome(std::string_view s) -> bool
{
    return std::equal(s.cbegin(), s.cbegin() + s.size() / 2, s.crbegin());
}

auto longest_palindrome_prefix(std::string_view s) -> size_t
{
    size_t ans = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        auto prefix = s.substr(0, i + 1);
        if (is_palindrome(prefix))ans = prefix.size();
    }
    return ans;
}

auto main() -> int
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;
        std::cout << longest_palindrome_prefix(str) << '\n';
    }
}
