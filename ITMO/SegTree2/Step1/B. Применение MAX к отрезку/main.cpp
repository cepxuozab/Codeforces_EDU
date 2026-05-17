#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTreeMax
{
public:
    int n;
    int size;
    vector<long long> lazy; // хранит текущий максимум, применённый к отрезку

    SegmentTreeMax(int n_) : n(n_)
    {
        size = 1;
        while (size < n) size *= 2;
        lazy.assign(2 * size, 0LL); // изначально всё 0
    }

    // Применить a[i] = max(a[i], v) для i ∈ [l, r)
    void apply_max(int l, int r, long long v)
    {
        l += size;
        r += size;
        while (l < r)
        {
            if (l & 1)
            {
                lazy[l] = max(lazy[l], v);
                ++l;
            }
            if (r & 1)
            {
                --r;
                lazy[r] = max(lazy[r], v);
            }
            l /= 2;
            r /= 2;
        }
    }

    // Получить текущее значение a[i]
    [[nodiscard]] auto get(int i) const -> long long
    {
        long long res = 0;
        int pos = i + size;
        while (pos > 0)
        {
            res = max(res, lazy[pos]);
            pos /= 2;
        }
        return res;
    }
};

auto main() -> int
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTreeMax st(n);

    for (int op_idx = 0; op_idx < m; ++op_idx)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            st.apply_max(l, r, v);
        }
        else if (op == 2)
        {
            int i;
            cin >> i;
            cout << st.get(i) << '\n';
        }
    }

    return 0;
}
