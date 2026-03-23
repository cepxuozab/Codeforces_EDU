#include <algorithm>
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

    std::string s;
    if (std::cin >> s)
    {
        int n = static_cast<int>(s.length());
        std::string r = s;
        std::ranges::reverse(r);

        // Конструируем строку T = s + '#' + r
        // Разделитель '#' гарантирует, что префикс не перейдет границу между s и r
        std::string t = s;
        t += '#';
        t += r;

        std::vector<int> z = compute_z_function(t);

        int max_palindrome_len = 1;
        int t_len = static_cast<int>(t.length());

        // Мы ищем максимальное k такое, что префикс s длины k равен суффиксу r длины k.
        // Суффикс r длины k начинается в строке T с позиции t_len - k.
        // Если z[t_len - k] == k, значит префикс T (который есть s) совпадает с суффиксом T (который есть суффикс r) длины k.
        // Поскольку r — это перевернутая s, совпадение префикса s и суффикса r длины k
        // означает, что префикс s длины k равен своему обратному виду, т.е. является палиндромом.

        // Проверяем k от n до 1
        for (int k = n; k >= 1; --k) {
            int idx = 2 * n + 1 - k;
            if (idx < t_len && z[idx] == k) {
                max_palindrome_len = k;
                break;
            }
        }

        std::cout << max_palindrome_len << "\n";
    }
    return 0;
}
