#include <iostream>
#include <vector>
#include <string>
#include <numeric>

class DSU
{
public:
    explicit DSU(int n) : p(n), r(n, 0)
    {
        std::iota(p.begin(), p.end(), 0);
    }

    auto find(int v) -> int
    {
        if (p[v] == v) return v;
        return p[v] = find(p[v]);
    }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) std::swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
    }

private:
    std::vector<int> p;
    std::vector<int> r;
};

auto calc_z(const std::string& s) -> std::vector<int>
{
    int n = s.size();
    std::vector<int> z(n);
    for (int i = 1; i < n; ++i)
    {
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
    }
    return z;
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    const std::string alphabet =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (t--)
    {
        int n;
        std::cin >> n;

        std::vector<int> z(n);
        for (int& x : z) std::cin >> x;

        bool ok = true;

        DSU dsu(n);
        std::vector<std::pair<int, int>> neq;

        for (int i = 0; i < n; ++i)
        {
            if (z[i] > n - i) ok = false;
        }

        if (ok)
        {
            for (int i = 1; i < n; ++i)
            {
                int k = z[i];

                for (int j = 0; j < k; ++j)
                {
                    dsu.unite(j, i + j);
                }

                if (i + k < n)
                {
                    neq.emplace_back(k, i + k);
                }
            }
        }

        if (ok)
        {
            for (auto [a,b] : neq)
            {
                if (dsu.find(a) == dsu.find(b))
                {
                    ok = false;
                    break;
                }
            }
        }

        if (!ok)
        {
            std::cout << "!\n";
            continue;
        }

        std::vector<int> comp(n);
        for (int i = 0; i < n; ++i) comp[i] = dsu.find(i);

        std::vector<int> id(n, -1);
        int cid = 0;

        for (int i = 0; i < n; ++i)
        {
            if (id[comp[i]] == -1)
            {
                id[comp[i]] = cid++;
            }
        }

        std::vector<int> comp_id(n);
        for (int i = 0; i < n; ++i) comp_id[i] = id[comp[i]];

        std::vector<std::vector<int>> g(cid);

        for (auto [a,b] : neq)
        {
            int u = comp_id[a];
            int v = comp_id[b];
            if (u == v) continue;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        std::vector<char> color(cid, '?');

        for (int v = 0; v < cid; ++v)
        {
            for (char c : alphabet)
            {
                bool good = true;
                for (int to : g[v])
                {
                    if (color[to] == c)
                    {
                        good = false;
                        break;
                    }
                }
                if (good)
                {
                    color[v] = c;
                    break;
                }
            }
            if (color[v] == '?')
            {
                ok = false;
                break;
            }
        }

        if (!ok)
        {
            std::cout << "!\n";
            continue;
        }

        std::string s(n, 'a');
        for (int i = 0; i < n; ++i)
        {
            s[i] = color[comp_id[i]];
        }

        if (std::vector<int> z2 = calc_z(s); z2 != z)
        {
            std::cout << "!\n";
        }
        else
        {
            std::cout << s << "\n";
        }
    }
}
