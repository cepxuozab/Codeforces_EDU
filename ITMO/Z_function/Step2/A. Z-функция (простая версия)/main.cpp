#include <iostream>
#include <string>
#include <vector>
#include <string_view>

auto z_function(std::string_view str) -> std::vector<int>
{
    std::vector<int> z_func(str.size());
    for (size_t i = 1; i < str.size(); ++i)
    {
        while (z_func[i] + i < str.size() && str[z_func[i] + i] == str[z_func[i]])z_func[i]++;
    }
    return z_func;
}

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;
    for (int i : z_function(str))std::cout << i << ' ';
    return 0;
}
