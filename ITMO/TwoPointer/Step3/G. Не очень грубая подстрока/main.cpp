#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, c;
    cin >> n >> c;
    string s;
    cin >> s;

    long long count_a = 0, count_b = 0;
    long long curr_rudeness = 0;
    int left = 0;
    int max_len = 0;

    for (int right = 0; right < n; ++right) {
        char ch = s[right];
        if (ch == 'b') {
            curr_rudeness += count_a;
            count_b++;
        } else if (ch == 'a') {
            count_a++;
        }

        // Сжимаем окно, пока грубость > c
        while (curr_rudeness > c && left <= right) {
            char left_ch = s[left];
            if (left_ch == 'a') {
                count_a--;
                curr_rudeness -= count_b;
            } else if (left_ch == 'b') {
                count_b--;
                // грубость не уменьшается
            }
            left++;
        }

        // Теперь окно [left, right] допустимо
        max_len = max(max_len, right - left + 1);
    }

    cout << max_len << '\n';

    return 0;
}