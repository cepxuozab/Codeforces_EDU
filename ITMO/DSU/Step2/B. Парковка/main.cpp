#include <iostream>
#include <vector>

using namespace std;

auto main() -> int
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    // Используем DSU для эффективного поиска свободных мест
    vector<int> next(n + 2);
    for (int i = 1; i <= n + 1; i++)
    {
        next[i] = i;
    }

    vector<int> result(n);

    // Функция для поиска следующего свободного места
    auto findNext = [&](auto&& self, int x)
    -> auto {
        // Реализация DSU с эвристикой сжатия путей
        if (next[x] == x)
            return x;
        return next[x] = self(self, next[x]);
    };

    for (int i = 0; i < n; i++)
    {
        int desired = p[i];
        // Находим ближайшее свободное место
        int spot = findNext(findNext, desired);

        // Если дошли до n+1, значит нужно начать с 1
        if (spot == n + 1)
        {
            spot = findNext(findNext, 1);
        }

        result[i] = spot;
        // "Занимаем" это место - связываем его со следующим
        next[spot] = findNext(findNext, spot + 1);
    }

    // Выводим результат
    for (int i = 0; i < n; i++)
    {
        cout << result[i] << (i < n - 1 ? " " : "\n");
    }

    return 0;
}
