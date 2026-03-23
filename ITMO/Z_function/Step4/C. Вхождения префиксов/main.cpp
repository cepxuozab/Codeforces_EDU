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
    // Оптимизация ввода-вывода
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    if (std::cin >> q)
    {
        while (q--)
        {
            std::string s;
            std::cin >> s;

            int n = static_cast<int>(s.length());
            std::vector<int> z = compute_z_function(s);

            // cnt[i] будет хранить количество вхождений префикса длины i
            // Используем метод разностного массива для эффективного подсчёта
            std::vector<int> cnt(n + 2, 0);

            // Для каждой позиции i, z[i] означает, что префиксы длины 1, 2, ..., z[i]
            // встречаются начиная с позиции i
            for (int i = 1; i < n; ++i)
            {
                if (z[i] > 0)
                {
                    cnt[1]++;
                    cnt[z[i] + 1]--;
                }
            }

            // Вычисляем префиксные суммы для получения фактических количеств
            for (int i = 1; i <= n; ++i)
            {
                cnt[i] += cnt[i - 1];
            }

            // Каждый префикс встречается как минимум один раз (в начале строки, позиция 0)
            for (int i = 1; i <= n; ++i)
            {
                cnt[i]++;
            }

            // Вывод результатов
            for (int i = 1; i <= n; ++i)
            {
                std::cout << cnt[i] << (i == n ? "" : " ");
            }
            std::cout << "\n";
        }
    }
    return 0;
}
