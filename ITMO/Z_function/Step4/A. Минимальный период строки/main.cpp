#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Функция для вычисления Z-функции строки s
// z[i] — длина наибольшего общего префикса строки s и суффикса s, начинающегося в i
auto compute_z_function(std::string const& s) -> std::vector<int>
{
    int n = static_cast<int>(s.length());
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
        {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            ++z[i];
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    if (std::cin >> t)
    {
        while (t--)
        {
            std::string s;
            std::cin >> s;

            int n = static_cast<int>(s.length());
            std::vector<int> z = compute_z_function(s);

            int period_length = n;
            // Ищем наименьшее k (1 <= k < n), такое что z[k] == n - k.
            // Это условие означает, что суффикс строки, начинающийся с позиции k,
            // полностью совпадает с префиксом строки длины n - k.
            // Следовательно, строка имеет период длины k.
            for (int k = 1; k < n; ++k)
            {
                if (z[k] == n - k)
                {
                    period_length = k;
                    break;
                }
            }

            // Выводим подстроку, являющуюся минимальным периодом
            std::cout << s.substr(0, period_length) << "\n";
        }
    }
    return 0;
}
