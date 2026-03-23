#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <span>

void radix_sort(std::span<int> sa,
                std::span<const int> rank,
                std::span<int> tmp,
                int offset)
{
    const int n = sa.size();
    const int maxv = std::max(256, n) + 1;

    std::vector<int> count(maxv);

    for (int i = 0; i < n; ++i)
    {
        int key = (sa[i] + offset < n) ? rank[sa[i] + offset] + 1 : 0;
        ++count[key];
    }

    for (int i = 1; i < maxv; ++i)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; --i)
    {
        int key = (sa[i] + offset < n) ? rank[sa[i] + offset] + 1 : 0;
        tmp[--count[key]] = sa[i];
    }

    std::ranges::copy(tmp, sa.begin());

    std::ranges::fill(count, 0);

    for (int i = 0; i < n; ++i)
        ++count[rank[sa[i]] + 1];

    for (int i = 1; i < maxv; ++i)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; --i)
    {
        int key = rank[sa[i]] + 1;
        tmp[--count[key]] = sa[i];
    }

    std::ranges::copy(tmp, sa.begin());
}

auto build_suffix_array(std::string_view s) -> std::vector<int>
{
    const int n = s.size();

    std::vector<int> sa(n);
    std::vector<int> rank(n);
    std::vector<int> tmp(n);

    for (int i = 0; i < n; ++i)
    {
        sa[i] = i;
        rank[i] = static_cast<unsigned char>(s[i]);
    }

    for (int k = 1; k < n; k <<= 1)
    {
        radix_sort(sa, rank, tmp, k);

        tmp[sa[0]] = 0;

        for (int i = 1; i < n; ++i)
        {
            int a = sa[i - 1];
            int b = sa[i];

            bool diff =
                rank[a] != rank[b] ||
                ((a + k < n ? rank[a + k] : -1) !=
                    (b + k < n ? rank[b + k] : -1));

            tmp[b] = tmp[a] + diff;
        }

        rank.swap(tmp);

        if (rank[sa.back()] == n - 1)
            break;
    }

    return sa;
}


auto build_lcp(std::string_view str, std::span<const int> suf) -> std::vector<int>
{
    int n = static_cast<int>(str.length());
    std::vector<int> pos(n), lcp(n);
    for (int i = 0; i < n; ++i)
    {
        pos[suf[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i)
    {
        if (k > 0)k--;
        if (pos[i] == n - 1)
        {
            lcp[n - 1] = -1;
            k = 0;
            continue;;
        }
        int j = suf[pos[i] + 1];
        while (std::max(i + k, j + k) < n and str[i + k] == str[j + k])k++;
        lcp[pos[i]] = k;
    }
    return lcp;
}


struct SubstringInfo
{
    int length;
    int start_pos; // позиция в объединенной строке
    bool from_first; // true если подстрока из первой строки
};

auto longest_common_substring(std::string_view s1, std::string_view s2) -> std::string
{
    // Используем символ, который точно не встречается в строках
    // Для простоты используем char с кодом 0 (можно заменить на другой разделитель)
    constexpr char delimiter = '\0';

    // Объединяем строки с разделителем
    std::string combined;
    combined.reserve(s1.size() + 1 + s2.size());
    combined.append(s1);
    combined.push_back(delimiter);
    combined.append(s2);

    int n1 = static_cast<int>(s1.size());

    int n = static_cast<int>(combined.size());

    // Строим суффиксный массив для объединенной строки
    std::vector<int> sa = build_suffix_array(combined);

    // Строим LCP массив
    std::vector<int> lcp = build_lcp(combined, sa);

    // Находим максимальный LCP между суффиксами из разных строк
    int max_lcp = 0;
    int best_pos = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        // Проверяем, что lcp[i] больше текущего максимума
        if (lcp[i] > max_lcp)
        {
            // Определяем, из каких строк суффиксы sa[i] и sa[i+1]
            bool first_in_first = sa[i] < n1;
            bool second_in_first = sa[i + 1] < n1;

            // Если суффиксы из разных строк
            if (first_in_first != second_in_first)
            {
                max_lcp = lcp[i];
                best_pos = sa[i]; // сохраняем позицию начала общей подстроки
            }
        }
    }

    // Извлекаем наибольшую общую подстроку
    if (max_lcp > 0)
    {
        return combined.substr(best_pos, max_lcp);
    }

    return ""; // нет общей подстроки
}

// Версия, которая возвращает также информацию о позициях в исходных строках
auto longest_common_substring_with_positions(std::string_view s1, std::string_view s2)
    -> std::tuple<std::string, int, int>
{
    constexpr char delimiter = '\0';

    std::string combined;
    combined.reserve(s1.size() + 1 + s2.size());
    combined.append(s1);
    combined.push_back(delimiter);
    combined.append(s2);

    int n1 = static_cast<int>(s1.size());
    int n = static_cast<int>(combined.size());

    std::vector<int> sa = build_suffix_array(combined);
    std::vector<int> lcp = build_lcp(combined, sa);

    int max_lcp = 0;
    int best_pos_combined = 0;
    int best_pos_s1 = 0;
    int best_pos_s2 = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        if (lcp[i] > max_lcp)
        {
            bool first_in_first = sa[i] < n1;
            bool second_in_first = sa[i + 1] < n1;

            if (first_in_first != second_in_first)
            {
                max_lcp = lcp[i];
                best_pos_combined = sa[i];

                // Определяем позиции в исходных строках
                if (first_in_first)
                {
                    best_pos_s1 = sa[i];
                    best_pos_s2 = sa[i + 1] - n1 - 1; // -1 из-за разделителя
                }
                else
                {
                    best_pos_s1 = sa[i + 1];
                    best_pos_s2 = sa[i] - n1 - 1;
                }
            }
        }
    }

    if (max_lcp > 0)
    {
        return {combined.substr(best_pos_combined, max_lcp), best_pos_s1, best_pos_s2};
    }

    return {"", -1, -1};
}


auto main() -> int
{
    std::string s1;
    std::string s2;
    std::cin >> s1 >> s2;

    std::string lcs = longest_common_substring(s1, s2);
    std::cout << lcs << '\n';


    return 0;
}
