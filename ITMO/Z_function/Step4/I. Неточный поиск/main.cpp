
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

    std::string t, p;
    int k;

    if (!(std::cin >> t >> p >> k)) {
        return 0;
    }

    int n = static_cast<int>(t.length());
    int m = static_cast<int>(p.length());

    if (m > n) {
        std::cout << "0\n\n";
        return 0;
    }

    // Вычисляем Z-функцию для p + '#' + t (для префиксных совпадений)
    std::string combined_fwd = p;
    combined_fwd += '#';
    combined_fwd += t;
    std::vector<int> z_fwd = compute_z_function(combined_fwd);

    // Вычисляем Z-функцию для reverse(p) + '#' + reverse(t) (для суффиксных совпадений)
    std::string rp = p;
    std::string rt = t;
    std::reverse(rp.begin(), rp.end());
    std::reverse(rt.begin(), rt.end());

    std::string combined_rev = rp;
    combined_rev += '#';
    combined_rev += rt;
    std::vector<int> z_rev = compute_z_function(combined_rev);

    std::vector<int> matches;
    int separator_pos = m + 1;

    // Для каждой позиции d в тексте проверяем, является ли она неточным вхождением
    for (int d = 0; d <= n - m; ++d) {
        // Длина совпадения префикса образца с подстрокой текста, начинающейся в d
        int prefix_match = z_fwd[separator_pos + d];
        if (prefix_match > m) {
            prefix_match = m;
        }

        // Длина совпадения суффикса образца с подстрокой текста, начинающейся в d
        // В обратных строках позиция d соответствует позиции (n - m - d) в rt
        int suffix_match = z_rev[separator_pos + (n - m - d)];
        if (suffix_match > m) {
            suffix_match = m;
        }

        // Несовпадающая часть находится между префиксом и суффиксом
        // Её длина = m - prefix_match - suffix_match (но не меньше 0)
        int mismatch_window = std::max(0, m - prefix_match - suffix_match);

        // Если все несовпадения можно покрыть окном размера ≤ k, это неточное вхождение
        if (mismatch_window <= k) {
            matches.push_back(d + 1);  // Выводим 1-индексированную позицию
        }
    }

    // Вывод результата
    std::cout << matches.size() << "\n";
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << matches[i] << (i == matches.size() - 1 ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}