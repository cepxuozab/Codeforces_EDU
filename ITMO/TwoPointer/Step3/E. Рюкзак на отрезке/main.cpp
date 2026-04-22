#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long s; // s может быть до 1e9, но сумма весов может превысить int
    cin >> n >> s;

    vector<long long> w(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    long long max_cost = 0;
    long long curr_weight = 0;
    long long curr_cost = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        curr_weight += w[right];
        curr_cost += c[right];

        // Сжимаем окно слева, пока вес превышает лимит
        while (curr_weight > s) {
            curr_weight -= w[left];
            curr_cost -= c[left];
            ++left;
        }

        // Теперь curr_weight <= s — обновляем ответ
        if (curr_cost > max_cost) {
            max_cost = curr_cost;
        }
    }

    cout << max_cost << '\n';

    return 0;
}