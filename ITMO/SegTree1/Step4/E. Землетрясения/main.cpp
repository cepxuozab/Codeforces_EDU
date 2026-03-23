#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9 + 10;

class SegTree
{
public:
    vector<int> min_val;
    int n;
    vector<int> arr;


    explicit SegTree(int size) : n(size), arr(size, 0)
    {
        min_val.resize(4 * n, INF);
    }

    void build(int v, int tl, int tr)
    {
        if (tl == tr)
        {
            min_val[v] = INF;
        }
        else
        {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm);
            build(v * 2 + 1, tm + 1, tr);
            min_val[v] = min(min_val[v * 2], min_val[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int pos, int val)
    {
        if (tl == tr)
        {
            arr[pos] = val;
            min_val[v] = (val == 0 ? INF : val);
        }
        else
        {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
            {
                update(v * 2, tl, tm, pos, val);
            }
            else
            {
                update(v * 2 + 1, tm + 1, tr, pos, val);
            }
            min_val[v] = min(min_val[v * 2], min_val[v * 2 + 1]);
        }
    }

    auto remove_rec(int v, int tl, int tr, int l, int r, int p) -> int
    {
        if (tr < l || tl > r) return 0;
        if (min_val[v] > p) return 0;

        if (tl == tr)
        {
            if (arr[tl] != 0 && arr[tl] <= p)
            {
                arr[tl] = 0;
                min_val[v] = INF;
                return 1;
            }
            return 0;
        }

        int tm = (tl + tr) / 2;
        int left_removed = remove_rec(v * 2, tl, tm, l, r, p);
        int right_removed = remove_rec(v * 2 + 1, tm + 1, tr, l, r, p);
        min_val[v] = min(min_val[v * 2], min_val[v * 2 + 1]);
        return left_removed + right_removed;
    }

    void point_update(int pos, int val)
    {
        update(1, 0, n - 1, pos, val);
    }

    auto remove_and_count(int l, int r, int p) -> int
    {
        return remove_rec(1, 0, n - 1, l, r, p);
    }
};

auto main() -> int
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegTree st(n);
    st.build(1, 0, n - 1);

    while (m--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int i, h;
            cin >> i >> h;
            st.point_update(i, h);
        }
        else
        {
            int l, r, p;
            cin >> l >> r >> p;
            cout << st.remove_and_count(l, r - 1, p) << '\n';
        }
    }

    return 0;
}
