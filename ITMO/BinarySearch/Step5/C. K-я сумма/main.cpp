#include <algorithm>
#include <iostream>
#include <vector>

using int64 = long long;

class Solver
{
public:
    Solver(std::vector<int64> a, std::vector<int64> b, int64 k)
        : a_(std::move(a)), b_(std::move(b)), k_(k)
    {
        std::ranges::sort(a_);
        std::ranges::sort(b_);
    }

    [[nodiscard]] auto good(int64 M) const -> bool
    {
        int64 count = 0;

        for (const auto& ai : a_)
        {
            if (ai >= M) continue;

            count += std::ranges::lower_bound(
                b_,
                M - ai
            ) - b_.begin();
        }

        return count < k_;
    }

    [[nodiscard]] auto solve() const -> int64
    {
        int64 left = 0;
        int64 right = 2'000'000'000'000'000'000LL;

        while (right > left + 1)
        {
            int64 mid = (left + right) / 2;

            if (good(mid))
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }

        return left;
    }

private:
    std::vector<int64> a_;
    std::vector<int64> b_;
    int64 k_;
};

auto main() -> int
{
    int64 n, k;
    std::cin >> n >> k;

    std::vector<int64> a(n), b(n);
    for (auto& x : a)
    {
        std::cin >> x;
    }
    for (auto& x : b)
    {
        std::cin >> x;
    }

    Solver solver(std::move(a), std::move(b), k);
    std::cout << solver.solve() << '\n';

    return 0;
}