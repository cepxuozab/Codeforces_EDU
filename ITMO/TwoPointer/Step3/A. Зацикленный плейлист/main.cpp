#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p;
    cin >> n >> p;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long S = 0;
    for (long long x : a) S += x;

    // Сколько полных кругов и остаток
    long long cycles = p / S;
    long long rem = p % S;

    if (rem == 0) {
        rem = S;
        cycles--;
    }

    // Дублируем массив
    vector<long long> b(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        b[i] = a[i % n];
    }

    const long long INF = (long long)4e18;
    long long best_len = INF;
    int best_start = 0;

    long long sum = 0;
    int r = 0;

    for (int l = 0; l < n; l++) {
        while (r < l + n && sum < rem) {
            sum += b[r];
            r++;
        }

        if (sum >= rem) {
            long long len = r - l;
            if (len < best_len) {
                best_len = len;
                best_start = l;
            }
        }

        sum -= b[l];
    }

    long long total_songs = cycles * n + best_len;

    // +1, так как нумерация с 1
    cout << best_start + 1 << " " << total_songs << "\n";

    return 0;
}
