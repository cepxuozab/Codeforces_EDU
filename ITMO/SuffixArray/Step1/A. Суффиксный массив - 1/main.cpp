#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


auto buildSuffixArray(std::string_view s) -> std::vector<int>
{
    int n = static_cast<int>(s.length());
    std::vector<int> suffixArray(n);
    std::vector<int> rank(n);
    std::vector<int> tempRank(n);

    // Начальная инициализация: сортируем по одному символу
    for (int i = 0; i < n; i++)
    {
        suffixArray[i] = i;
        rank[i] = static_cast<unsigned char>(s[i]);
    }

    // Вспомогательная структура для сортировки пар
    struct SuffixComparator
    {
        const std::vector<int>& rank;
        int k;

        SuffixComparator(const std::vector<int>& r, int step) : rank(r), k(step)
        {
        }

        auto operator()(int i, int j) const -> bool
        {
            if (rank[i] != rank[j])
            {
                return rank[i] < rank[j];
            }
            // Сравниваем вторые половины
            const int ri = (i + k < (int)rank.size()) ? rank[i + k] : -1;
            const int rj = (j + k < (int)rank.size()) ? rank[j + k] : -1;
            return ri < rj;
        }
    };

    // Итеративно увеличиваем длину сравниваемых префиксов
    for (int k = 1; k < n; k *= 2)
    {
        // Сортируем суффиксы по первым 2k символам
        std::ranges::sort(suffixArray, SuffixComparator(rank, k));

        // Присваиваем новые ранги
        tempRank[suffixArray[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            tempRank[suffixArray[i]] = tempRank[suffixArray[i - 1]];

            // Если текущий суффикс отличается от предыдущего, увеличиваем ранг
            if (SuffixComparator(rank, k)(suffixArray[i - 1], suffixArray[i]))
            {
                tempRank[suffixArray[i]]++;
            }
        }

        rank = tempRank;

        // Если все ранги уникальны, завершаем досрочно
        if (rank[suffixArray.back()] == n - 1)
        {
            break;
        }
    }

    return suffixArray;
}

auto main() -> int
{
    std::string s;

    std::cin >> s;

    // Добавляем символ, который меньше любого другого (для корректной работы)
    // В реальных задачах это не всегда нужно, но помогает избежать проблем
    s += '$';

    auto const suffixArray = buildSuffixArray(s);


    for (int i : suffixArray)
    {
        std::cout << i << " ";
    }
    std::cout << '\n';


    return 0;
}
