#include <iostream>
#include <vector>
#include <span>

auto count_equal_pairs(std::span<const int> a, std::span<const int> b) -> long long
{
    size_t i = 0, j = 0;
    long long total = 0;
    const size_t n = a.size();
    const size_t m = b.size();

    while (i < n && j < m)
    {
        if (a[i] < b[j])
        {
            ++i;
        }
        else if (a[i] > b[j])
        {
            ++j;
        }
        else
        {
            // a[i] == b[j]
            long long count_a = 0, count_b = 0;
            const int value = a[i];

            // Считаем, сколько раз value встречается в a, начиная с i
            while (i < n && a[i] == value)
            {
                ++count_a;
                ++i;
            }

            // Считаем, сколько раз value встречается в b, начиная с j
            while (j < m && b[j] == value)
            {
                ++count_b;
                ++j;
            }

            total += count_a * count_b;
        }
    }

    return total;
}

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> lhs(n), rhs(m);
    for (auto& i : lhs)std::cin >> i;
    for (auto& i : rhs)std::cin >> i;
    const auto res = count_equal_pairs(lhs, rhs);
    std::cout << res;
}
