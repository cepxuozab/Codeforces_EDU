#include <iostream>
#include <vector>
#include <cstdint>

class SegmentTree
{
private:
    std::vector<int64_t> tree;
    int n;

    void build(const std::vector<int64_t>& arr, int node, int left, int right)
    {
        if (left == right)
        {
            tree[node] = arr[left];
            return;
        }
        int mid = (left + right) / 2;
        build(arr, node * 2, left, mid);
        build(arr, node * 2 + 1, mid + 1, right);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int node, int left, int right, int idx, int64_t value)
    {
        if (left == right)
        {
            tree[node] = value;
            return;
        }
        int mid = (left + right) / 2;
        if (idx <= mid)
        {
            update(node * 2, left, mid, idx, value);
        }
        else
        {
            update(node * 2 + 1, mid + 1, right, idx, value);
        }
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int64_t query(int node, int left, int right, int ql, int qr)
    {
        if (ql > qr) return 0;
        if (ql == left && qr == right)
        {
            return tree[node];
        }
        int mid = (left + right) / 2;
        return query(node * 2, left, mid, ql, std::min(qr, mid)) +
            query(node * 2 + 1, mid + 1, right, std::max(ql, mid + 1), qr);
    }

public:
    SegmentTree(int size) : n(size)
    {
        tree.resize(4 * size);
        std::vector<int64_t> init(size, 0);
        build(init, 1, 0, size - 1);
    }

    void set(int idx, int64_t value)
    {
        update(1, 0, n - 1, idx, value);
    }

    int64_t sum(int left, int right)
    {
        return query(1, 0, n - 1, left, right);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> permutation(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> permutation[i];
        permutation[i]--; // преобразуем к 0-индексации
    }

    SegmentTree tree(n);
    std::vector<int> result(n);

    for (int i = 0; i < n; ++i)
    {
        // считаем количество элементов больше permutation[i] среди предыдущих
        result[i] = tree.sum(permutation[i] + 1, n - 1);
        // отмечаем текущий элемент как встреченный
        tree.set(permutation[i], 1);
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << result[i] << " \n"[i == n - 1];
    }

    return 0;
}
