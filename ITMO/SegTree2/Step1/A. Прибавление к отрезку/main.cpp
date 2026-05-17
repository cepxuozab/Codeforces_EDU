#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree {
public:
    int n{};               // исходный размер
    int size{};            // степень двойки >= n
    vector<long long> lazy;

    SegmentTree(int n_) : n(n_) {
        size = 1;
        while (size < n) size *= 2;
        lazy.assign(2 * size, 0);
    }

    // Прибавить v ко всем элементам [l, r)
    void add(int l, int r, long long v) {
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) {
                lazy[l] += v;
                ++l;
            }
            if (r & 1) {
                --r;
                lazy[r] += v;
            }
            l /= 2;
            r /= 2;
        }
    }

    // Получить значение в позиции i
    [[nodiscard]] auto get(int i) const -> long long {
        long long res = 0;
        int pos = i + size;
        while (pos > 0) {
            res += lazy[pos];
            pos /= 2;
        }
        return res;
    }
};

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTree st(n);

    for (int _ = 0; _ < m; ++_) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            st.add(l, r, v);
        } else if (op == 2) {
            int i;
            cin >> i;
            cout << st.get(i) << '\n';
        }
    }

    return 0;
}