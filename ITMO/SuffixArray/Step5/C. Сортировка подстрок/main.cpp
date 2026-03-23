#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <span>
#include <tuple>

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


struct Substring
{
    int l; // 1-indexed позиция левого конца
    int r; // 1-indexed позиция правого конца
    int index; // исходный индекс для сохранения порядка вывода

    // Длина подстроки
    [[nodiscard]] auto length() const -> int
    {
        return r - l + 1;
    }
};

// Функция для построения RMQ (Range Minimum Query) над LCP массивом
// Нужна для быстрого вычисления LCP между любыми двумя суффиксами
class LCPRMQ
{
private:
    std::vector<std::vector<int>> st;
    std::vector<int> log;
    std::vector<int> lcp;
    std::vector<int> pos; // позиция суффикса в суффиксном массиве

public:
    LCPRMQ(const std::vector<int>& lcp_array, const std::vector<int>& pos_array)
        : lcp(lcp_array), pos(pos_array)
    {
        int n = lcp.size();
        log.resize(n + 1);
        log[1] = 0;
        for (int i = 2; i <= n; i++)
        {
            log[i] = log[i / 2] + 1;
        }

        int k = log[n] + 1;
        st.resize(n, std::vector<int>(k));

        for (int i = 0; i < n; i++)
        {
            st[i][0] = lcp[i];
        }

        for (int j = 1; j < k; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Запрос минимального LCP на отрезке [l, r] в массиве LCP
    [[nodiscard]] auto query(int l, int r) const -> int
    {
        if (l > r) std::swap(l, r);
        int j = log[r - l + 1];
        return std::min(st[l][j], st[r - (1 << j) + 1][j]);
    }

    // Вычисление LCP между суффиксами, начинающимися в позициях i и j
    [[nodiscard]] auto get_lcp(int i, int j, int n) const -> int
    {
        if (i == j) return n - i;

        int pi = pos[i];
        int pj = pos[j];

        if (pi > pj) std::swap(pi, pj);

        // LCP между суффиксами i и j равно минимуму LCP на отрезке [pi, pj-1]
        return query(pi, pj - 1);
    }
};

// Компаратор для сортировки подстрок
class SubstringComparator
{
private:
    std::string_view s;
    const LCPRMQ& lcp_rmq;

public:
    SubstringComparator(std::string_view str, const LCPRMQ& rmq)
        : s(str), lcp_rmq(rmq)
    {
    }

    auto operator()(const Substring& a, const Substring& b) const -> bool
    {
        int len_a = a.length();
        int len_b = b.length();

        // Позиции в строке (переводим из 1-indexed в 0-indexed)
        int pos_a = a.l - 1;
        int pos_b = b.l - 1;

        // Вычисляем LCP между началами подстрок
        int lcp_len = lcp_rmq.get_lcp(pos_a, pos_b, s.size());

        if (lcp_len >= std::min(len_a, len_b))
        {
            // Одна подстрока является префиксом другой
            if (len_a != len_b)
            {
                return len_a < len_b;
            }
            // Если равны, сравниваем по паре (l, r)
            return std::tie(a.l, a.r) < std::tie(b.l, b.r);
        }
        else
        {
            // Сравниваем первый различающийся символ
            return s[pos_a + lcp_len] < s[pos_b + lcp_len];
        }
    }
};

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Чтение строки
    std::string s;
    std::getline(std::cin, s);

    // Построение суффиксного массива и LCP
    std::vector<int> sa = build_suffix_array(s);
    std::vector<int> lcp = build_lcp(s, sa);

    // Построение массива позиций (обратный к суффиксному массиву)
    int n = static_cast<int>(s.size());
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i)
    {
        pos[sa[i]] = i;
    }

    // Построение RMQ над LCP
    LCPRMQ lcp_rmq(lcp, pos);

    // Чтение количества подстрок
    int m;
    std::cin >> m;

    std::vector<Substring> substrings(m);
    for (int i = 0; i < m; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        substrings[i] = {.l = l, .r = r, .index = i};
    }

    // Создаем компаратор
    SubstringComparator cmp(s, lcp_rmq);

    // Сортируем подстроки
    std::ranges::sort(substrings, cmp);

    // Выводим результат
    for (const auto& sub : substrings)
    {
        std::cout << sub.l << " " << sub.r << "\n";
    }

    return 0;
}
