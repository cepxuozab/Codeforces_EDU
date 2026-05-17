#include <iostream>
#include <vector>
using namespace std;

int MOD = 500000;

struct segtree {
    struct val {
        int count;
        int sum;
        char left;
        char right;
    };

    struct node {
        char paint;
        val value;
    };

    char NO_OP = 'N';

    int size;
    vector<node> tree;

    void build(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2LL * size, {.paint=NO_OP, .value={.count=0, .sum=0, .left='W', .right='W'}});
    }

    static auto combine(const val &a, const val &b) -> val {
        int new_count = a.count + b.count;
        if (a.right == 'B' && b.left == 'B') {
            new_count--;
        }

        return {
            .count=new_count,
            .sum=a.sum + b.sum,
            .left=a.left,
            .right=b.right
        };
    }

    void propagate(int x, int lx, int rx) {
        if (tree[x].paint == NO_OP || rx - lx == 1) return;

        int m = (lx + rx) / 2;

        tree[2*x+1].paint = tree[x].paint;
        tree[2*x+2].paint = tree[x].paint;

        if (tree[x].paint == 'W') {
            tree[2*x+1].value = {.count=0, .sum=0, .left='W', .right='W'};
            tree[2*x+2].value = {.count=0, .sum=0, .left='W', .right='W'};
        } else {
            tree[2*x+1].value = {.count=1, .sum=m - lx, .left='B', .right='B'};
            tree[2*x+2].value = {.count=1, .sum=rx - m, .left='B', .right='B'};
        }

        tree[x].paint = NO_OP;
    }

    void modify(int l, int r, char v) {
        modify(l, r, v, 0, 0, size);
    }

    void modify(int l, int r, char v, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            if (v == 'W') {
                tree[x].paint = 'W';
                tree[x].value = {.count=0, .sum=0, .left='W', .right='W'};
            } else {
                tree[x].paint = 'B';
                tree[x].value = {.count=1, .sum=rx - lx, .left='B', .right='B'};
            }
        } else {
            int m = (lx + rx) / 2;
            modify(l, r, v, 2 * x + 1, lx, m);
            modify(l, r, v, 2 * x + 2, m, rx);
            tree[x].value = combine(tree[2*x+1].value, tree[2*x+2].value);
        }
    }

    auto info() -> node {
        return info(0, 0, size);
    }

    auto info(int x, int lx, int rx) -> node {
        propagate(x, lx, rx);
        return tree[0];
    }
};

auto main() -> int {
    int n;
    cin >> n;

    segtree st;
    st.build(1e6);

    char c;
    int x, l;

    for (int i = 0; i < n; i++) {
        cin >> c >> x >> l;
        x += MOD;

        st.modify(x, x + l, c);
        auto x0 = st.info();
        cout << x0.value.count << " " << x0.value.sum << '\n';
    }

    return 0;
}