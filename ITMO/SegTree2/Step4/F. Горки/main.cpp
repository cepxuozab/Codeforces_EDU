#include <iostream>
#include <memory>
#include <cstdio>
#include <algorithm>

using namespace std;

constexpr long long MAX = 1000000001;

int n;

struct Node
{
    int maxx = 0;
    int sum = 0;
    int set = MAX;
    int id = 0;

    unique_ptr<Node> l = nullptr;
    unique_ptr<Node> r = nullptr;

    Node() = default;

    explicit Node(int index) : id(index)
    {
    }

    Node(unique_ptr<Node> x, unique_ptr<Node> y)
        : l(std::move(x)), r(std::move(y))
    {
    }

    // запрещаем копирование
    Node(const Node&) = delete;
    auto operator=(const Node&) -> Node& = delete;

    // разрешаем перемещение
    Node(Node&&) = default;
    auto operator=(Node&&) -> Node& = default;

    void updatemax()
    {
        maxx = max(l->maxx, r->maxx + l->sum);
        sum = l->sum + r->sum;
    }
};

Node t;

void push(Node* v)
{
    v->l->set = v->set;
    v->r->set = v->set;
}

void getChild(Node* v, int l, int r)
{
    if (!v->l)
    {
        int leftid = v->id * 2 + 1;
        int rightid = v->id * 2 + 2;

        v->l = make_unique<Node>(leftid);
        v->r = make_unique<Node>(rightid);
    }

    if (v->set == MAX)
        return;

    v->sum = v->set * (r - l + 1);
    v->maxx = v->sum;

    if (l != r)
    {
        push(v);
    }

    v->set = MAX;
}

void set(Node* v, int l, int r, int tl, int tr, int value)
{
    getChild(v, l, r);

    if (tl > r || l > tr)
        return;

    if (l >= tl && r <= tr)
    {
        v->set = value;
        getChild(v, l, r);
        return;
    }

    int tm = l + (r - l) / 2;

    set(v->l.get(), l, tm, tl, tr, value);
    set(v->r.get(), tm + 1, r, tl, tr, value);

    v->updatemax();
}

auto get(Node* v, int l, int r, int height) -> long long
{
    getChild(v, l, r);

    if (l == r)
        return r;

    int m = l + (r - l) / 2;

    getChild(v->l.get(), l, m);

    if (v->l->maxx <= height)
    {
        getChild(v->r.get(), m + 1, r);
        height -= v->l->sum;
        return get(v->r.get(), m + 1, r, height);
    }
    else
    {
        return get(v->l.get(), l, m, height);
    }
}

auto main() -> int
{
    scanf("%d", &n);

    char s;

    while (scanf(" %c", &s) != EOF)
    {
        if (s == 'E')
            return 0;

        if (s == 'I')
        {
            int a, b, D;
            scanf("%d %d %d", &a, &b, &D);
            a -= 1;
            b -= 1;
            set(&t, 0, n, a, b, D);
        }

        if (s == 'Q')
        {
            int height;
            scanf("%d", &height);
            printf("%lld\n", get(&t, 0, n, height));
        }
    }

    return 0;
}
