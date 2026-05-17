#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i)
    {
        std::string s, t;
        std::cin >> s >> t;

        const size_t n = s.length();
        const size_t m = t.length();

        std::vector<size_t> bad_positions;

        for (size_t j = 0; j + m <= n; ++j)
        {
            if (s.substr(j, m) == t)
            {
                bad_positions.push_back(j);
            }
        }

        unsigned long long ans = 0;
        size_t bad_idx = 0;

        for (size_t start = 0; start < n; ++start)
        {
            while (bad_idx < bad_positions.size() && bad_positions[bad_idx] < start)
            {
                ++bad_idx;
            }

            if (bad_idx < bad_positions.size())
            {
                const size_t first_bad = bad_positions[bad_idx];

                if (const size_t max_end = first_bad + m - 1; max_end > start)
                {
                    ans += max_end - start;
                }
            }
            else
            {
                ans += n - start;
            }
        }

        std::cout << ans << '\n';
    }

    return 0;
}
