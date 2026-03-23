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
            std::string s, t;
            std::cin >> s >> t;

            int n = static_cast<int>(s.length());
            // Если длины различаются (хотя по условию они равны), сдвиг невозможен
            if (static_cast<int>(t.length()) != n)
            {
                std::cout << "-1\n";
                continue;
            }

            // Чтобы найти циклический сдвиг, нужно проверить, является ли t подстрокой s + s.
            // Однако нам нужно найти конкретный сдвиг k (0 <= k < n).
            // Мы конструируем строку pattern = t + '#' + s + s.
            // Но достаточно s + s[0...n-2], чтобы избежать лишнего полного совпадения в конце,
            // однако для простоты и так как ограничения позволяют, используем s + s.
            // Мы будем искать вхождения t в s + s только в пределах первых n позиций s+s.

            // Конструируем строку для Z-функции: t + '#' + s + s
            // Разделитель '#' должен быть символом, которого нет в s и t.
            // Так как s и t состоят из букв и цифр, можно использовать любой спецсимвол, например '#'.
            std::string combined;
            combined.reserve(2 * n + 1 + n);
            combined += t;
            combined += '#';
            combined += s;
            combined += s;

            std::vector<int> z = compute_z_function(combined);

            int shift = -1;
            int t_len = static_cast<int>(t.length());
            int start_search = t_len + 1; // Начало части s + s в строке combined

            // Ищем совпадение длины t в первой половине s + s (чтобы k < n)
            // Проверяем позиции от start_search до start_search + n - 1
            for (int i = start_search; i < start_search + n; ++i)
            {
                if (z[i] == t_len)
                {
                    shift = i - start_search;
                    break;
                }
            }

            std::cout << shift << "\n";
        }
    }
    return 0;
}
