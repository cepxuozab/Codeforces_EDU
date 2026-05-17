#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>
using namespace std;

auto build_suffix_array(const string& s) -> vector<int> {
    int n = s.size();
    vector<int> sa(n), rank(n), tmp(n);
    std::ranges::iota(sa, 0);
    std::ranges::sort(sa, [&](int i, int j) -> bool { return s[i] < s[j]; });
    rank[sa[0]] = 0;
    for (int i = 1; i < n; ++i)
        rank[sa[i]] = rank[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int i, int j) -> bool {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = i + k < n ? rank[i + k] : -1;
            int rj = j + k < n ? rank[j + k] : -1;
            return ri < rj;
        };
        ranges::sort(sa, cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rank = tmp;
    }
    return sa;
}

auto build_lcp(const string& s, const vector<int>& sa) -> vector<int> {
    int n = s.size();
    vector<int> rank(n);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    vector<int> lcp(max(0, n - 1));
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) { h = 0; continue; }
        int j = sa[rank[i] + 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
        if (n > 1) lcp[rank[i]] = h;
        if (h) --h;
    }
    return lcp;
}

struct RMQ {
    vector<vector<int>> st;
    vector<int> log;

    RMQ(const vector<int>& a) {
        int n = a.size();
        if (n == 0) return;
        log.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) log[i] = log[i / 2] + 1;
        int k = log[n] + 1;
        st.assign(k, vector<int>(n));
        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        for (int j = 1; j < k; ++j)
            for (int i = 0; i + (1 << j) <= n; ++i)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }

    auto query(int l, int r) -> int {
        if (st.empty() || l > r) return 0;
        if (l >= (int)st[0].size() || r >= (int)st[0].size()) return 0;
        int j = log[r - l + 1];
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

auto main() -> int {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> sa = build_suffix_array(s);
    vector<int> lcp = build_lcp(s, sa);
    RMQ rmq(lcp);

    vector<int> rank(n);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;

    int ans = 1;
    for (int p = 1; p <= n; ++p) {
        for (int i = 0; i + p < n; i += p) {
            int l = rank[i], r = rank[i + p];
            if (l > r) swap(l, r);
            int common = (l < r) ? rmq.query(l, r - 1) : 0;
            int k = 1 + common / p;
            ans = max(ans, k);

            // Проверяем смещённую позицию
            int offset = p - (common % p);
            int j = i - offset;
            if (j >= 0 && j + p < n) {
                l = rank[j], r = rank[j + p];
                if (l > r) swap(l, r);
                common = (l < r) ? rmq.query(l, r - 1) : 0;
                k = 1 + common / p;
                ans = max(ans, k);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}