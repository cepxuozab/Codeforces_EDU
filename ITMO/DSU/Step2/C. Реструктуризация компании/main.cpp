#include <iostream>
#include <vector>

class UFDS
{
private:
    std::vector<int> p, rank, next;

public:
    UFDS(int n) : p(n), rank(n), next(n)
    {
        for (int i = 0; i < n; i++)
        {
            p[i] = i;
            next[i] = i + 1;
        }
    }

    auto find_set(int i) -> int { return p[i] == i ? i : p[i] = find_set(p[i]); }
    
    auto same_set(int i, int j) -> bool { return find_set(i) == find_set(j); }

    void merge(int i, int j)
    {
        if (!same_set(i, j))
        {
            int x = find_set(i);
            int y = find_set(j);
            if (rank[x] > rank[y]) std::swap(x, y);
            if (rank[x] == rank[y]) ++rank[y];
            p[x] = y;
        }
    }

    void merge_range(int l, int r)
    {
        if (r < l) std::swap(l, r);
        ++l;
        while (l <= r)
        {
            merge(l - 1, l);
            int t = next[l];
            next[l] = std::max(next[l], r);
            l = t;
        }
    }
};

void solve()
{
    int n, q;
    std::cin >> n >> q;
    UFDS ufds(n);
    while (q--)
    {
        int t, x, y;
        std::cin >> t >> x >> y;
        --x, --y;
        if (t == 1)
        {
            ufds.merge(x, y);
        }
        else if (t == 2)
        {
            ufds.merge_range(x, y);
        }
        else
        {
            std::cout << (ufds.same_set(x, y) ? "YES\n" : "NO\n");
        }
    }
}

auto main() -> signed
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
}
