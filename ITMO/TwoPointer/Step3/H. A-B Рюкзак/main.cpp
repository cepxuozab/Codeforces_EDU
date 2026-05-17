#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, s, A, B;
    cin >> n >> m >> s >> A >> B;

    vector<long long> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    // Сортируем по убыванию
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    // Префиксные суммы (включая 0)
    vector<long long> prefA(n + 1, 0), prefB(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefA[i + 1] = prefA[i] + a[i];
    }
    for (int i = 0; i < m; ++i) {
        prefB[i + 1] = prefB[i] + b[i];
    }

    long long best = 0;

    // Перебираем количество предметов типа A
    for (long long i = 0; i <= n; ++i) {
        long long weightA = i * A;
        if (weightA > s) break;

        long long rem = s - weightA;
        long long j = rem / B;          // сколько B можно взять по весу
        if (j > m) j = m;               // но не больше, чем есть

        long long total = prefA[i] + prefB[j];
        if (total > best) best = total;
    }

    cout << best << '\n';

    return 0;
}