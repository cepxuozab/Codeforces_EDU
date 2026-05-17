#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Функция для вычисления Z-функции строки s
// z[i] — длина наибольшего общего префикса строки s и суффикса s, начинающегося в i
auto compute_z_function(std::string const& s) -> std::vector<int> {
    int n = static_cast<int>(s.length());
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// Вычисляет суммарную длину всех различных подстрок строки s
// Идея: для каждой позиции i считаем, сколько новых подстрок начинается в этой позиции
// Подстрока s[i...i+len-1] новая, если она не встречалась раньше (не начинается в позиции j < i)
// Для этого находим max_lcp[i] = максимальную длину общего префикса суффикса i с любым суффиксом j < i
auto sum_of_distinct_substring_lengths(std::string const& s) -> long long {
    int n = static_cast<int>(s.length());
    std::vector<int> max_lcp(n, 0);

    // Для каждого суффикса j вычисляем Z-функцию и обновляем max_lcp для всех i > j
    // z[k] в Z-функции суффикса j показывает LCP между суффиксом j и суффиксом j+k
    for (int j = 0; j < n; ++j) {
        std::string_view suffix(s.c_str() + j, n - j);
        std::string suffix_str(suffix);
        std::vector<int> z = compute_z_function(suffix_str);

        for (int k = 1; k < static_cast<int>(z.size()); ++k) {
            int i = j + k;  // позиция в исходной строке
            if (i < n) {
                max_lcp[i] = std::max(max_lcp[i], z[k]);
            }
        }
    }

    long long total = 0;
    for (int i = 0; i < n; ++i) {
        // Длина текущего суффикса
        int suffix_len = n - i;

        // Максимальная длина префикса этого суффикса, который уже встречался в предыдущих суффиксах
        int lcp = max_lcp[i];

        // Новые подстроки, которые добавляет этот суффикс, имеют длины от (lcp + 1) до suffix_len
        // Сумма арифметической прогрессии: (lcp+1) + (lcp+2) + ... + suffix_len
        long long sum_all = static_cast<long long>(suffix_len) * (suffix_len + 1) / 2;
        long long sum_duplicate = static_cast<long long>(lcp) * (lcp + 1) / 2;
        
        total += sum_all - sum_duplicate;
    }
    
    return total;
}

auto main() -> int {
    // Оптимизация ввода-вывода
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    if (std::cin >> s) {
        std::cout << sum_of_distinct_substring_lengths(s) << "\n";
    }
    return 0;
}