#include <iostream>
#include <string>
#include <vector>


class DSU
{
private:
    std::vector<int> parent;
    std::vector<bool> present;

public:
    explicit DSU(int n) : parent(n + 2), present(n + 2, true)
    {
        // Изначально каждый человек указывает на следующего
        for (int i = 0; i <= n + 1; i++)
        {
            parent[i] = i;
        }
        // Правее последнего человека нет никого
        parent[n + 1] = -1;
    }

    // Найти корень для позиции x
    auto find(int x) -> int
    {
        if (parent[x] == -1)
            return -1;
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    // Удалить человека на позиции x
    void remove(int x)
    {
        if (!present[x])
            return;
        present[x] = false;
        // Теперь x указывает на следующего живого человека
        parent[x] = find(x + 1);
    }
};

auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(n);

    for (int i = 0; i < m; i++)
    {
        std::string type;
        int x;
        std::cin >> type >> x;

        if (type == "-")
        {
            dsu.remove(x);
        }
        else
        {
            // type == "?"
            const int result = dsu.find(x);
            std::cout << result << "\n";
        }
    }

    return 0;
}
