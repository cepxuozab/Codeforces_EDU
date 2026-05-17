#include <iostream>
#include <vector>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    constexpr int MAX_W = 1'000'000;

    std::vector<int> present(MAX_W + 1, 0);

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        present[x] = 1;
    }

    // Если универсальных ламп достаточно,
    // можно собрать любую последовательность длины k.
    if (m >= k) {
        std::cout << MAX_W - k + 1 << '\n';
        return 0;
    }

    int need = k - m;

    int cnt = 0;

    // первое окно [1..k]
    for (int i = 1; i <= k; ++i) {
        cnt += present[i];
    }

    long long answer = 0;

    // правая граница окна = R
    for (int R = k; R <= MAX_W; ++R) {
        if (cnt >= need) {
            ++answer;
        }

        // сдвигаем окно:
        // удаляем левый конец
        int left = R - k + 1;
        cnt -= present[left];

        // добавляем новый правый
        if (R + 1 <= MAX_W) {
            cnt += present[R + 1];
        }
    }

    std::cout << answer << '\n';

    return 0;
}