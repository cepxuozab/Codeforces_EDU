#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    multiset<long long> window;
    long long ans = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        window.insert(a[right]);

        while (*window.rbegin() - *window.begin() > k) {
            window.erase(window.find(a[left]));
            ++left;
        }

        ans += (right - left + 1);
    }

    cout << ans << '\n';

    return 0;
}