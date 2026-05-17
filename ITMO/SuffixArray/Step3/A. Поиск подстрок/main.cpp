#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <span>
#include <ranges>
#include <algorithm>
#include <utility>

 void radix_sort(std::span<int> sa, std::span<int> rank, std::span<int> tmp, int k) {
    const int n = sa.size();
    const int maxv = std::max(256, n) + 2;

    std::vector<int> cnt(maxv);

    for (int i = 0; i < n; ++i) {
        int idx = std::cmp_less(sa[i] + k, n) ? rank[sa[i] + k] + 1 : 0;
        ++cnt[idx];
    }

    for (int i = 1; i < maxv; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        int idx = std::cmp_less(sa[i] + k, n) ? rank[sa[i] + k] + 1 : 0;
        tmp[--cnt[idx]] = sa[i];
    }

    std::ranges::copy(tmp, sa.begin());

    std::ranges::fill(cnt, 0);

    for (int i = 0; i < n; ++i)
        ++cnt[rank[sa[i]] + 1];

    for (int i = 1; i < maxv; ++i)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        int idx = rank[sa[i]] + 1;
        tmp[--cnt[idx]] = sa[i];
    }

    std::ranges::copy(tmp, sa.begin());
}

 auto build_suffix_array(std::string_view s) -> std::vector<int> {
    const int n = s.size();

    std::vector<int> sa(n);
    std::vector<int> rank(n);
    std::vector<int> tmp(n);

    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = static_cast<unsigned char>(s[i]);
    }

    for (int k = 1; std::cmp_less(k, n); k <<= 1) {
        radix_sort(sa, rank, tmp, k);

        tmp[sa[0]] = 0;

        for (int i = 1; i < n; ++i) {
            int a = sa[i - 1];
            int b = sa[i];

            int ra1 = rank[a];
            int rb1 = rank[b];

            int ra2 = std::cmp_less(a + k, n) ? rank[a + k] : -1;
            int rb2 = std::cmp_less(b + k, n) ? rank[b + k] : -1;

            bool diff = (ra1 != rb1) || (ra2 != rb2);

            tmp[b] = tmp[a] + diff;
        }

        rank.swap(tmp);

        if (std::cmp_equal(rank[sa[n - 1]], n - 1))
            break;
    }

    return sa;
}

 auto contains_substring(
    std::string_view t,
    std::span<const int> sa,
    std::string_view pattern
) -> bool {
    int l = 0;
    int r = sa.size();

    while (std::cmp_less(l, r)) {
        int m = (l + r) / 2;

        std::string_view suf = t.substr(sa[m]);

        if (suf.compare(0, pattern.size(), pattern) < 0)
            l = m + 1;
        else
            r = m;
    }

    if (!std::cmp_less(l, sa.size()))
        return false;

    return t.substr(sa[l]).starts_with(pattern);
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string t;
    std::cin >> t;

    auto sa = build_suffix_array(t);

    int n;
    std::cin >> n;

    std::string query;

    while (n--) {
        std::cin >> query;

        if (contains_substring(t, sa, query))
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
}