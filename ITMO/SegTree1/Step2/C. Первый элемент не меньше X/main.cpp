#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

class SegmentTree
{
private:
    std::vector<int> tree;
    int size{};

    void build(const std::vector<int>& arr, int node, int left, int right)
    {
        if (right - left == 1)
        {
            // Используем std::cmp_less для сравнения знакового left с беззнаковым arr.size()
            if (std::cmp_less(left, arr.size()))
            {
                tree[node] = arr[left];
            }
            return;
        }

        int mid = left + (right - left) / 2;
        build(arr, 2 * node + 1, left, mid);
        build(arr, 2 * node + 2, mid, right);
        tree[node] = std::max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void set(int index, int value, int node, int left, int right)
    {
        if (right - left == 1)
        {
            tree[node] = value;
            return;
        }

        int mid = left + (right - left) / 2;
        // Здесь оба значения знаковые, std::cmp_less не нужен
        if (index < mid)
        {
            set(index, value, 2 * node + 1, left, mid);
        }
        else
        {
            set(index, value, 2 * node + 2, mid, right);
        }
        tree[node] = std::max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    [[nodiscard]] auto findAbove(int threshold, int node, int left, int right) const -> int
    {
        if (right - left == 1)
        {
            return tree[node] >= threshold ? left : -1;
        }

        int mid = left + (right - left) / 2;
        if (tree[2 * node + 1] >= threshold)
        {
            return findAbove(threshold, 2 * node + 1, left, mid);
        }
        return findAbove(threshold, 2 * node + 2, mid, right);
    }

public:
    void build(const std::vector<int>& arr)
    {
        size = 1;
        // Используем std::cmp_less для сравнения знакового size с беззнаковым arr.size()
        while (std::cmp_less(size, arr.size()))
        {
            size *= 2;
        }
        tree.assign(2 * size - 1, 0);
        build(arr, 0, 0, size);
    }

    void set(int index, int value)
    {
        set(index, value, 0, 0, size);
    }

    [[nodiscard]] auto findAbove(int threshold) const -> int
    {
        if (tree[0] < threshold)
        {
            return -1;
        }
        return findAbove(threshold, 0, 0, size);
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    SegmentTree segmentTree;
    segmentTree.build(arr);

    for (int i = 0; i < m; ++i)
    {
        int operationType;
        std::cin >> operationType;

        if (operationType == 1)
        {
            int index, value;
            std::cin >> index >> value;
            segmentTree.set(index, value);
        }
        else
        {
            int threshold;
            std::cin >> threshold;
            std::cout << segmentTree.findAbove(threshold) << '\n';
        }
    }

    return 0;
}
