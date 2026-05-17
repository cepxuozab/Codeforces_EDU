#include <iostream>
#include <vector>

using namespace std;

struct segment_tree
{
    vector<int> tree;
    int size = 0;

    void init(int n)
    {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, 0);
    }

    void build(vector<int> const& a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
            {
                tree[x] = a[lx];
            }
        }
        else
        {
            int mid = lx + (rx - lx) / 2;
            build(a, 2 * x + 1, lx, mid);
            build(a, 2 * x + 2, mid, rx);
            tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        }
    }

    void build(vector<int> const& a)
    {
        init(a.size());
        build(a, 0, 0, size);
    }

    void set(int i, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (tree[x] == 1)
            {
                tree[x] = 0;
            }
            else
            {
                tree[x] = 1;
            }
        }
        else
        {
            int mid = lx + (rx - lx) / 2;

            if (i < mid)
            {
                set(i, 2 * x + 1, lx, mid);
            }
            else
            {
                set(i, 2 * x + 2, mid, rx);
            }
            tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        }
    }

    void set(int i)
    {
        set(i, 0, 0, size);
    }

    auto k_th_one(int k, int x, int lx, int rx) -> int
    {
        if (rx - lx == 1)
        {
            return lx;
        }
        int mid = lx + (rx - lx) * .5;
        if (k < tree[2 * x + 1])
        {
            return k_th_one(k, 2 * x + 1, lx, mid);
        }
        else
        {
            return k_th_one(k - tree[2 * x + 1], 2 * x + 2, mid, rx);
        }
    }

    auto k_th_one(int k) -> int
    {
        return k_th_one(k, 0, 0, size);
    }
};

auto main() -> int
{
    ios::sync_with_stdio(false);

    size_t n, m;
    cin >> n >> m;

    vector<int> a(n);

    for (size_t i = 0; i < n; ++i) cin >> a[i];

    segment_tree st;

    st.build(a);

    int x;
    for (size_t j = 0; j < m; ++j)
    {
        cin >> x;
        if (x == 1)
        {
            int i;
            cin >> i;
            st.set(i);
        }
        else
        {
            int k;
            cin >> k;
            cout << st.k_th_one(k) << '\n';
        }
    }

    return 0;
}
