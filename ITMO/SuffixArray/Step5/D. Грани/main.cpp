#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <tuple>

void radix_sort(std::span<int> sa,
                std::span<const int> rank,
                std::span<int> tmp,
                int offset,
                int maxv)
{
    const int n = sa.size();
    std::vector<int> count(maxv, 0);

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
    std::ranges::copy(tmp, sa.begin());
    std::ranges::fill(count, 0);
}

auto build_suffix_array(std::string_view s) -> std::vector<int>
{
    const int n = s.size();
    const int alphabet = 256;

    std::vector<int> sa(n), rank(n), tmp(n);

    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = static_cast<unsigned char>(s[i]);
    }

    for (int k = 1; k < n; k <<= 1) {
        radix_sort(sa, rank, tmp, k, std::max(alphabet, n) + 1);
        radix_sort(sa, rank, tmp, 0, std::max(alphabet, n) + 1);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int a = sa[i - 1], b = sa[i];
            bool diff = rank[a] != rank[b] ||
                ((a + k < n ? rank[a + k] : -1) != (b + k < n ? rank[b + k] : -1));
            tmp[b] = tmp[a] + diff;
        }
        rank.swap(tmp);

        if (rank[sa.back()] == n - 1)
            break;
    }
    return sa;
}

auto build_lcp(std::string_view str, std::span<const int> sa) -> std::vector<int>
{
    int n = static_cast<int>(str.length());
    std::vector<int> pos(n), lcp(n, 0);

    for (int i = 0; i < n; ++i)
        pos[sa[i]] = i;

    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == 0) {
            k = 0;
            continue;
        }
        if (k > 0) k--;
        int j = sa[pos[i] - 1];
        while (i + k < n && j + k < n && str[i + k] == str[j + k]) k++;
        lcp[pos[i]] = k;
    }
    return lcp;
}

auto solve_borders(const std::string& s) -> int64_t {
    //int64_t len = s.size();
    std::string extended_s = s + char(0);
    int64_t n = extended_s.size();

    std::vector<int> sa = build_suffix_array(extended_s);
    std::vector<int> lcp = build_lcp(extended_s, sa);

    int64_t ans = n * (n - 1) / 2;

    std::vector<std::tuple<int64_t, int64_t, int64_t>> sta;
    sta.reserve(n + 2);

    sta.emplace_back(0, 0, 0);
    sta.emplace_back(1, 1, 1);

    for (int64_t i = 1; i < n; ++i) {
        int64_t h = lcp[i];
        int64_t p = sa[i];

        if (h == 0) {
            sta.resize(1);
        } else {
            int64_t num = 0;
            while (std::get<0>(sta.back()) >= h) {
                num += std::get<1>(sta.back());
                sta.pop_back();
            }
            int64_t sum = std::get<2>(sta.back()) + h * num;
            ans += sum;
            sta.emplace_back(h, num, sum);
        }
        sta.emplace_back(n - p, 1, n - p);
    }

    return ans;
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    std::cout << solve_borders(s) << '\n';
    
    return 0;
}