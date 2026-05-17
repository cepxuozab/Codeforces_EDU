#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTreeAssign {
public:
    int n;
    int size;
    vector<long long> lazy_val;
    vector<int> lazy_ver; // версия (временная метка)
    int global_version = 0;

    SegmentTreeAssign(int n_) : n(n_) {
        size = 1;
        while (size < n) size *= 2;
        lazy_val.assign(2 * size, 0LL);
        lazy_ver.assign(2 * size, -1); // -1 означает "никогда не присваивалось"
    }

    // Присвоить v всем элементам [l, r)
    void assign(int l, int r, long long v) {
        ++global_version; // новая версия
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) {
                lazy_val[l] = v;
                lazy_ver[l] = global_version;
                ++l;
            }
            if (r & 1) {
                --r;
                lazy_val[r] = v;
                lazy_ver[r] = global_version;
            }
            l /= 2;
            r /= 2;
        }
    }

    // Получить значение a[i]
    long long get(int i) {
        int pos = i + size;
        long long best_val = 0;
        int best_ver = -1;

        while (pos > 0) {
            if (lazy_ver[pos] > best_ver) {
                best_ver = lazy_ver[pos];
                best_val = lazy_val[pos];
            }
            pos /= 2;
        }

        // Если ни разу не присваивалось, значение = 0 (по условию)
        return best_val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTreeAssign st(n);

    for (int op_idx = 0; op_idx < m; ++op_idx) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            st.assign(l, r, v);
        } else if (op == 2) {
            int i;
            cin >> i;
            cout << st.get(i) << '\n';
        }
    }

    return 0;
}