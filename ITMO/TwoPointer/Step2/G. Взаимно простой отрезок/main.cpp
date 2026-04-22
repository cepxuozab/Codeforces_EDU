#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

auto gcd(long long a, long long b) -> long long
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

auto main() -> int
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        if (a[i] == 1)
        {
            cout << 1 << '\n';
            return 0;
        }
    }

    // Проверим, есть ли вообще хороший отрезок
    long long total_gcd = a[0];
    for (int i = 1; i < n; ++i)
    {
        total_gcd = gcd(total_gcd, a[i]);
    }
    if (total_gcd != 1)
    {
        cout << -1 << '\n';
        return 0;
    }

    int ans = INT_MAX;
    // map: gcd_value -> minimal length of segment ending at current position with this gcd
    map<long long, int> prev;

    for (int i = 0; i < n; ++i)
    {
        map<long long, int> curr;
        // Новый отрезок, начинающийся и заканчивающийся в i
        curr[a[i]] = 1;

        // Продолжаем все отрезки из prev
        for (auto& p : prev)
        {
            long long g = gcd(p.first, a[i]);
            int len = p.second + 1;
            // Сохраняем минимальную длину для данного gcd
            if (curr.contains(g))
            {
                curr[g] = min(curr[g], len);
            }
            else
            {
                curr[g] = len;
            }
        }

        // Проверяем, есть ли gcd = 1
        if (curr.contains(1))
        {
            ans = min(ans, curr[1]);
        }

        prev = std::move(curr);
    }

    cout << ans << '\n';
    return 0;
}
