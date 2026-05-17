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

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;
    text += '$';

    std::vector<int> sa = build_suffix_array(text);
    auto lcp = build_lcp(text, sa);
    lcp.pop_back();
    for (int i : sa)std::cout << i << ' ';
    std::cout << '\n';
    for (int i : lcp)std::cout << i << ' ';
}
