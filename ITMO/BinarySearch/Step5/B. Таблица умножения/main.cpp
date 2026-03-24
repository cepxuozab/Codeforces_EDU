#include <iostream>
#include <algorithm>

using int64 = long long;

class Solver
{
public:
    Solver(int64 n, int64 k) : n_(n), k_(k)
    {
    }

    [[nodiscard]] auto good(int64 M) const -> bool
    {
        int64 count = 0;

        for (int64 i = 1; i <= n_; ++i)
        {
            if (M % i == 0)
            {
                count += std::min(n_, M / i - 1);
            }
            else
            {
                count += std::min(n_, M / i);
            }
        }

        return count < k_;
    }

    [[nodiscard]] auto solve() const -> int64
    {
        int64 left = 0;
        int64 right = 1'000'000'000'000'000'000LL;

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
    int64 n_;
    int64 k_;
};

auto main() -> int
{
    int64 n, k;
    std::cin >> n >> k;

    Solver solver(n, k);
    std::cout << solver.solve() << '\n';

    return 0;
}
