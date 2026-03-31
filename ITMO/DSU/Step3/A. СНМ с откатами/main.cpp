#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

struct DSU
{
    std::vector<int> parent;
    std::vector<int> size;
    int num_sets;

    struct HistoryEntry
    {
        int child{};
        int old_parent_child{};
        int root{};
        int old_size_root{};
    };

    std::vector<HistoryEntry> history;
    std::stack<size_t> checkpoints;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1), num_sets(n)
    {
        for (int i = 1; i <= n; ++i)
        {
            parent[i] = i;
        }
    }

    [[nodiscard]] auto find(int x) const -> int
    {
        while (parent[x] != x)
        {
            x = parent[x];
        }
        return x;
    }

    void do_union(int u, int v)
    {
        int ru = find(u);
        int rv = find(v);

        if (ru == rv)
        {
            return;
        }

        if (size[ru] < size[rv])
        {
            std::swap(ru, rv);
        }

        // ru — новый корень
        int old_parent_rv = parent[rv];
        int old_size_ru = size[ru];

        parent[rv] = ru;
        size[ru] += size[rv];
        --num_sets;

        history.push_back({.child = rv, .old_parent_child = old_parent_rv, .root = ru, .old_size_root = old_size_ru});
    }

    void persist()
    {
        checkpoints.push(history.size());
    }

    void rollback()
    {
        if (checkpoints.empty()) return; // по условию не должно происходить

        size_t target_size = checkpoints.top();
        checkpoints.pop();

        while (history.size() > target_size)
        {
            auto& entry = history.back();
            parent[entry.child] = entry.old_parent_child;
            size[entry.root] = entry.old_size_root;
            ++num_sets;
            history.pop_back();
        }
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    DSU dsu(n);
    std::vector<int> output;

    for (int i = 0; i < m; ++i)
    {
        std::string op;
        std::cin >> op;

        if (op == "union")
        {
            int u, v;
            std::cin >> u >> v;
            dsu.do_union(u, v);
            output.push_back(dsu.num_sets);
        }
        else if (op == "persist")
        {
            dsu.persist();
        }
        else if (op == "rollback")
        {
            dsu.rollback();
            output.push_back(dsu.num_sets);
        }
    }

    for (const auto& s : output)
    {
        std::cout << s << '\n';
    }

    return 0;
}
