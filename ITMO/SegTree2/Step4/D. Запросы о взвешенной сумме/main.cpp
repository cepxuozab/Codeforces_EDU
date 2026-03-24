#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

struct segtree
{
    struct node
    {
        ll d;
        ll s;
        ll ws;
    };

    ll size;
    vector<node> tree;

    void init(ll n)
    {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2LL * size, {.d = 0, .s = 0, .ws = 0});
    }

    void propagate(ll x, ll lx, ll rx)
    {
        if (tree[x].d == 0 || rx - lx == 1) return;

        tree[2 * x + 1].d += tree[x].d;
        tree[2 * x + 2].d += tree[x].d;

        const ll m = (lx + rx) / 2;

        tree[2 * x + 1].s += (m - lx) * tree[x].d;
        tree[2 * x + 1].ws += tree[x].d * (m - lx) * (m - lx + 1) / 2;

        tree[2 * x + 2].s += (rx - m) * tree[x].d;
        tree[2 * x + 2].ws += tree[x].d * (rx - m) * (rx - m + 1) / 2;

        tree[x].d = 0;
    }

    void modify(ll l, ll r, ll d)
    {
        modify(l, r, d, 0, 0, size);
    }

    void modify(ll l, ll r, ll d, ll x, ll lx, ll rx)
    {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r)
        {
            tree[x].d += d;
            tree[x].s += d * (rx - lx);
            tree[x].ws += d * (rx - lx) * (rx - lx + 1) / 2;
        }
        else
        {
            const ll m = (lx + rx) / 2;
            modify(l, r, d, 2 * x + 1, lx, m);
            modify(l, r, d, 2 * x + 2, m, rx);
            tree[x].s = tree[2 * x + 1].s + tree[2 * x + 2].s;
            tree[x].ws = tree[2 * x + 1].ws + tree[2 * x + 2].ws + (m - lx) * tree[2 * x + 2].s;
        }
    }

    auto query(ll l, ll r) -> ll
    {
        return query(l, r, 0, 0, size).ws;
    }

    static auto add(const node& s1, const node& s2, ll d) -> node
    {
        if (s1.d == 0 && s1.s == LLONG_MIN && s1.ws == LLONG_MIN) return s2;
        if (s2.d == 0 && s2.s == LLONG_MIN && s2.ws == LLONG_MIN) return s1;
        return {.d = 0, .s = s1.s + s2.s, .ws = s1.ws + s2.ws + d * s2.s};
    }

    auto query(ll l, ll r, ll x, ll lx, ll rx) -> node
    {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return {.d = 0, .s = LLONG_MIN, .ws = LLONG_MIN};
        if (lx >= l && rx <= r) return tree[x];
        ll m = (lx + rx) / 2;
        const node s1 = query(l, r, 2 * x + 1, lx, m);
        const node s2 = query(l, r, 2 * x + 2, m, rx);

        return add(s1, s2, m - max(lx, l));
    }
};

auto main() -> int
{
    int n, m;
    cin >> n >> m;

    segtree st;
    st.init(n);

    int v;
    for (int i = 0; i < n; i++)
    {
        cin >> v;
        st.modify(i, i + 1, v);
    }

    int t, l, r, d;
    while (m--)
    {
        cin >> t >> l >> r;
        l--;
        if (t == 1)
        {
            cin >> d;
            st.modify(l, r, d);
        }
        else
        {
            cout << st.query(l, r) << '\n';
        }
    }

    return 0;
}
