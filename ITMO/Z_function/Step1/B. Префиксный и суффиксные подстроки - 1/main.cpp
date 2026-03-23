#include <iostream>
#include <string>

auto main() -> int
{
    int n;
    std::cin >> n;


    for (int i = 0; i < n; ++i)
    {
        int ans = 0;
        std::string str;
        std::cin >> str;
        for (size_t u = 0; u < str.size(); ++u)
        {
            for (size_t v = u; v < str.size(); ++v)
            {
                auto tmp = str.substr(u, v - u + 1);
                if (str.starts_with(tmp) && str.ends_with(tmp))continue;
                if (str.starts_with(tmp) || str.ends_with(tmp))ans++;
            }
        }
        std::cout << ans << '\n';
    }
}
