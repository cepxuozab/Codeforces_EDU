#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <span>
#include <algorithm>

void radix_sort(std::span<int> sa,
                std::span<const int> rank,
                std::span<int> tmp,
                int offset)
{
    const int n = sa.size();
    const int maxv = std::max(256, n) + 1;

    std::vector<int> count(maxv);

    for (int i = 0; i < n; ++i) {
        int key = (sa[i] + offset < n) ? rank[sa[i] + offset] + 1 : 0;
        ++count[key];
    }

    for (int i = 1; i < maxv; ++i)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        int key = (sa[i] + offset < n) ? rank[sa[i] + offset] + 1 : 0;
        tmp[--count[key]] = sa[i];
    }

    std::copy(tmp.begin(), tmp.end(), sa.begin());

    std::fill(count.begin(), count.end(), 0);

    for (int i = 0; i < n; ++i)
        ++count[rank[sa[i]] + 1];

    for (int i = 1; i < maxv; ++i)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        int key = rank[sa[i]] + 1;
        tmp[--count[key]] = sa[i];
    }

    std::copy(tmp.begin(), tmp.end(), sa.begin());
}

auto build_suffix_array(std::string_view s) -> std::vector<int>
{
    const int n = s.size();

    std::vector<int> sa(n);
    std::vector<int> rank(n);
    std::vector<int> tmp(n);

    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = static_cast<unsigned char>(s[i]);
    }

    for (int k = 1; k < n; k <<= 1) {
        radix_sort(sa, rank, tmp, k);

        tmp[sa[0]] = 0;

        for (int i = 1; i < n; ++i) {
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

auto lower_bound_suffix(std::string_view text,
                       std::span<const int> sa,
                       std::string_view pattern) -> int
{
    int left = 0;
    int right = sa.size();

    while (left < right) {
        int mid = (left + right) / 2;
        std::string_view suffix = text.substr(sa[mid]);

        if (suffix.compare(0, pattern.size(), pattern) < 0)
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

auto next_string(std::string_view s) -> std::string
{
    std::string result(s);

    for (int i = result.size() - 1; i >= 0; --i) {
        if (result[i] != 'z') {
            ++result[i];
            result.resize(i + 1);
            return result;
        }
    }

    result.push_back('{'); // символ после 'z'
    return result;
}

auto count_occurrences(std::string_view text,
                      std::span<const int> sa,
                      std::string_view pattern) -> int
{
    int left = lower_bound_suffix(text, sa, pattern);

    std::string upper = next_string(pattern);
    int right = lower_bound_suffix(text, sa, upper);

    return right - left;
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;

    std::vector<int> sa = build_suffix_array(text);

    int q;
    std::cin >> q;

    std::string pattern;

    while (q--) {
        std::cin >> pattern;
        std::cout << count_occurrences(text, sa, pattern) << '\n';
    }
}