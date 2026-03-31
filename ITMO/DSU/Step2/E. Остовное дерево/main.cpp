#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#define MP make_pair

using namespace std;

vector<int> p;

auto find_set(int x) -> int { return (x == p[x]) ? x : p[x] = find_set(p[x]); }

void unite_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);
    if (x == y)
        return;
    if (rand() % 2)
        swap(x, y);
    p[x] = y;
}

auto main() -> int
{
    int n, m, i, j, k, s = 0, w;
    long long ans = 0;
    cin >> n >> m;
    p.resize(n + 1);
    for (k = 1; k <= n; ++k)
        p[k] = k;
    vector<pair<int, pair<int, int>>> r(m);
    for (k = 0; k < m; ++k)
    {
        cin >> i >> j >> w;
        r[k] = MP(w, MP(i, j));
    }
    sort(r.data(), r.data() + m);
    for (k = 0; k < m && s < n - 1; ++k)
    {
        i = find_set(r[k].second.first);
        j = find_set(r[k].second.second);
        if (i != j)
        {
            ans += r[k].first;
            s++;
            unite_set(i, j);
        }
    }
    cout << ans;
    return 0;
}
