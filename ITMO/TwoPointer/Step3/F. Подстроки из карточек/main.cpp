#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s, cards;
    cin >> s;
    cin >> cards;

    // Частоты букв на карточках
    vector<int> card_freq(26, 0);
    for (char c : cards) {
        card_freq[c - 'a']++;
    }

    // Частоты в текущем окне
    vector<int> window_freq(26, 0);

    long long total_substrings = 0;
    int right = 0;

    for (int left = 0; left < n; ++left) {
        // Расширяем right, пока можно
        while (right < n) {
            char next_char = s[right];
            int idx = next_char - 'a';

            // Проверяем, можно ли добавить этот символ
            if (window_freq[idx] + 1 <= card_freq[idx]) {
                window_freq[idx]++;
                right++;
            } else {
                break;
            }
        }

        // Все подстроки, начинающиеся в left и заканчивающиеся в [left, right-1] — допустимы
        total_substrings += (right - left);

        // Удаляем s[left] из окна
        window_freq[s[left] - 'a']--;
    }

    cout << total_substrings << '\n';

    return 0;
}