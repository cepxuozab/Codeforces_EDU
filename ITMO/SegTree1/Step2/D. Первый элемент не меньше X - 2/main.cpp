#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

class SegmentTree {
private:
    std::vector<int> tree;
    int size{};

    [[nodiscard]] auto findFirstGreaterEqualImpl(int node, int left, int right, int threshold, int minIndex) const -> int {
        if (right <= minIndex) {
            return -1;
        }

        if (tree[node] < threshold) {
            return -1;
        }

        if (right - left == 1) {
            return left;
        }

        int mid = left + (right - left) / 2;

        if (mid > minIndex) {
            int leftResult = findFirstGreaterEqualImpl(2 * node, left, mid, threshold, minIndex);
            if (leftResult != -1) {
                return leftResult;
            }
        }

        return findFirstGreaterEqualImpl(2 * node + 1, mid, right, threshold, minIndex);
    }

public:
    void build(const std::vector<int>& arr) {
        size = 1;
        while (std::cmp_less(size, arr.size())) {
            size *= 2;
        }
        tree.assign(2LL * size, -1);

        for (int i = 0; std::cmp_less(i, arr.size()); ++i) {
            tree[size + i] = arr[i];
        }

        for (int i = size - 1; i >= 1; --i) {
            tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void set(int index, int value) {
        int pos = size + index;
        tree[pos] = value;

        for (pos /= 2; pos >= 1; pos /= 2) {
            tree[pos] = std::max(tree[2 * pos], tree[2 * pos + 1]);
        }
    }

    [[nodiscard]] auto findFirstGreaterEqual(int threshold, int minIndex) const -> int {
        int result = findFirstGreaterEqualImpl(1, 0, size, threshold, minIndex);

        if (result != -1 && std::cmp_less(result, size)) {
            return result;
        }
        return -1;
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    SegmentTree segmentTree;
    segmentTree.build(arr);

    for (int i = 0; i < m; ++i) {
        int operationType;
        std::cin >> operationType;

        if (operationType == 1) {
            int index, value;
            std::cin >> index >> value;
            segmentTree.set(index, value);
        } else {
            int threshold, minIndex;
            std::cin >> threshold >> minIndex;
            std::cout << segmentTree.findFirstGreaterEqual(threshold, minIndex) << '\n';
        }
    }

    return 0;
}