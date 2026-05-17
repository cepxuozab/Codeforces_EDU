#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using int64 = long long;

class Solver {
public:
    explicit Solver(std::vector<std::pair<int64, int64>> segments, int64 k)
        : segments_(std::move(segments)), k_(k) {}

    [[nodiscard]] auto good(int64 M) const -> bool {
        int64 count = 0;

        for (const auto& [l, r] : segments_) {
            if (M > r) {
                count += std::min(r, M) - l + 1;
            } else if (M > l) {
                count += M - l;
            }
        }

        return count <= k_;
    }

    [[nodiscard]] auto solve() const -> int64 {
        int64 left = -10000000000LL;
        int64 right = 10000000000LL;

        while (right > left + 1) {
            int64 mid = (left + right) / 2;

            if (good(mid)) {
                left = mid;
            } else {
                right = mid;
            }
        }

        return left;
    }

private:
    std::vector<std::pair<int64, int64>> segments_;
    int64 k_;
};

auto main() -> int {
    int n;
    int64 k;
    std::cin >> n >> k;

    std::vector<std::pair<int64, int64>> segments(n);
    for (auto& [l, r] : segments) {
        std::cin >> l >> r;
    }

    Solver solver(std::move(segments), k);
    std::cout << solver.solve() << '\n';

    return 0;
}