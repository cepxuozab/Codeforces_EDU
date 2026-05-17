#include <iostream>
#include <string>
#include <vector>
#include <span>

auto main() -> int
{
    int n;
    std::cin >> n;

    auto print_arr = [](std::span<const int> arr)-> void
    {
        std::cout << arr.size() << '\n';
        for (int i : arr)
        {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    };
    for (int i = 0; i < n; ++i)
    {
        std::string text, pattern;
        std::cin >> text >> pattern;
        std::vector<int> ans;
        if (pattern.size() > text.size())
        {
            print_arr(ans);
            continue;
        }
        for (size_t j = 0; j + pattern.size() <= text.size(); ++j)
        {
            auto tmp = text.substr(j, pattern.size());
            bool is_sub = true;
            for (size_t k = 0; k < tmp.size(); ++k)
            {
                if (pattern[k] == '?') continue;
                if (pattern[k] != tmp[k])
                {
                    is_sub = false;
                    break;
                }
            }
            if (is_sub)ans.emplace_back(j);
        }
        print_arr(ans);
    }
}
