#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

auto make_suffix_array(std::string_view str) -> std::vector<int>
{
    std::string s(str);
    s += '$';
    const int n = s.size();

    std::vector<std::pair<std::pair<int, int>, int>> suffs(n);
    for (int i = 0; i < n; i++)
    {
        suffs[i] = {{s[i], s[i]}, i};
    }
    std::ranges::sort(suffs);

    std::vector<int> equiv(n);
    for (int i = 1; i < n; i++)
    {
        auto [c_val, cs] = suffs[i];
        auto [p_val, ps] = suffs[i - 1];
        equiv[cs] = equiv[ps] + (c_val > p_val);
    }

    auto radix_sort = [](std::vector<std::pair<std::pair<int, int>, int>>& arr) -> void
    {
        // with radix sort, we actually have to sort by the second element first
        for (int i : std::vector<int>{2, 1})
        {
            auto key = [&](const std::pair<std::pair<int, int>, int>& x) -> int
            {
                return i == 1 ? x.first.first : x.first.second;
            };
            int max = 0;
            for (const auto& u : arr)
            {
                max = std::max(max, key(u));
            }
            std::vector<int> occs(max + 1);
            for (const auto& u : arr)
            {
                occs[key(u)]++;
            }
            std::vector<int> start(max + 1);
            for (int u = 1; u <= max; u++)
            {
                start[u] = start[u - 1] + occs[u - 1];
            }

            std::vector<std::pair<std::pair<int, int>, int>> new_arr(arr.size());
            for (const auto& u : arr)
            {
                new_arr[start[key(u)]] = u;
                start[key(u)]++;
            }
            arr.swap(new_arr);
        }
    };

    for (int cmp_amt = 1; cmp_amt < n; cmp_amt *= 2)
    {
        for (auto& [val, idx] : suffs)
        {
            // the order numbers for the left half and right half respectively
            val = {equiv[idx], equiv[(idx + cmp_amt) % n]};
        }
        // without the radix sort optimization, we would use `std::sort`
        radix_sort(suffs);

        // assign numbers to the newly sorted suffixes
        for (int i = 1; i < n; i++)
        {
            auto [c_val, cs] = suffs[i];
            auto [p_val, ps] = suffs[i - 1];
            equiv[cs] = equiv[ps] + (c_val > p_val);
        }
    }

    std::vector<int> result(n);
    for (int i = 0; i < n; i++)
    {
        result[i] = suffs[i].second;
    }
    return result;
}

auto main() -> int
{
    std::string str;
    std::getline(std::cin, str);

    auto suffix_array = make_suffix_array(str);

    for (size_t i = 0; i < suffix_array.size(); i++)
    {
        std::cout << suffix_array[i];
        if (i < suffix_array.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << '\n';

    return 0;
}
