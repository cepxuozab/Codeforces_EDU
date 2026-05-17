

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

auto main() -> int {
    // Оптимизация ввода-вывода
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t;
    if (std::cin >> s >> t) {
        int n = static_cast<int>(s.length());
        int m = static_cast<int>(t.length());

        // Если длины различаются, операция невозможна
        if (n != m) {
            std::cout << "No\n";
            return 0;
        }

        // После операции с параметром k строка s превращается в:
        // s[k...n-1] + reverse(s[0...k-1]) (0-индексация)
        // 
        // Это должно равняться t, значит:
        // 1. t[0...n-k-1] == s[k...n-1] (префикс t длины n-k равен суффиксу s длины n-k)
        // 2. t[n-k...n-1] == reverse(s[0...k-1]) (суффикс t длины k равен reverse(префикса s длины k))
        //
        // Условие 2 эквивалентно: reverse(t[n-k...n-1]) == s[0...k-1]
        // То есть префикс s длины k равен reverse(суффикса t длины k) = префиксу reverse(t) длины k

        // Создаём reverse(t) для проверки второго условия
        std::string rt = t;
        std::reverse(rt.begin(), rt.end());

        // Для проверки условия 1: используем z-функцию на строке t + '#' + s
        // z-значения в части s покажут, насколько суффиксы s совпадают с префиксом t
        std::string combined1 = t;
        combined1 += '#';
        combined1 += s;
        std::vector<int> z1 = compute_z_function(combined1);

        // Для проверки условия 2: используем z-функцию на строке s + '#' + rt
        // z-значения в начале rt покажут, насколько префикс rt совпадает с префиксом s
        std::string combined2 = s;
        combined2 += '#';
        combined2 += rt;
        std::vector<int> z2 = compute_z_function(combined2);

        int s_start_in_c1 = n + 1; // Позиция начала s в combined1
        int rt_start_in_c2 = n + 1; // Позиция начала rt в combined2
        
        // z2[rt_start_in_c2] tells us the longest prefix match between rt and s
        int max_prefix_match = z2[rt_start_in_c2];

        bool found = false;
        int best_k = -1;

        // Перебираем k от 0 до n (минимальное k ищем первым)
        for (int k = 0; k <= n; ++k) {
            // Условие 1: префикс t длины n-k должен совпадать с суффиксом s длины n-k
            // В combined1 суффикс s длины n-k начинается с позиции s_start_in_c1 + k
            bool cond1 = true;
            if (n - k > 0) {
                int idx1 = s_start_in_c1 + k;
                if (idx1 < static_cast<int>(combined1.length()) && z1[idx1] < n - k) {
                    cond1 = false;
                }
            }

            // Условие 2: префикс s длины k должен совпадать с префиксом rt длины k
            // Это верно, если max_prefix_match >= k
            bool cond2 = (k <= max_prefix_match);

            if (cond1 && cond2) {
                found = true;
                best_k = k;
                break;
            }
        }

        if (found) {
            std::cout << "Yes\n";
            std::cout << best_k << "\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}