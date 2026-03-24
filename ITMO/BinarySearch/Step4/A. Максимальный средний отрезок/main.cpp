#include <iostream>
#include <vector>
#include <utility>
#include <optional>

struct Segment
{
    int left;
    int right;
};

auto good(const std::vector<int>& a, int d, double x) -> std::optional<Segment>
{
    const int n = static_cast<int>(a.size());

    std::vector<double> prefix(n);
    std::vector<std::pair<double, int>> min_prefix(n);

    prefix[0] = a[0] - x;
    min_prefix[0] = {prefix[0], 0};

    for (int i = 1; i < n; ++i)
    {
        prefix[i] = prefix[i - 1] + (a[i] - x);

        if (prefix[i] <= min_prefix[i - 1].first)
        {
            min_prefix[i] = {prefix[i], i};
        }
        else
        {
            min_prefix[i] = min_prefix[i - 1];
        }
    }

    for (int i = n - 1; i >= d - 1; --i)
    {
        if (prefix[i] >= 0.0)
        {
            return Segment{.left = 0, .right = i};
        }

        const auto& [min_val, idx] = min_prefix[i - d];
        if (min_val <= prefix[i])
        {
            return Segment{.left = idx + 1, .right = i};
        }
    }

    return std::nullopt;
}

auto main() -> int
{
    int n, d;
    std::cin >> n >> d;

    std::vector<int> a(n);
    for (int& v : a)
    {
        std::cin >> v;
    }

    double left = 0.0;
    double right = 110.0;

    for (int i = 0; i < 110; ++i)
    {
        double mid = (left + right) / 2.0;

        if (good(a, d, mid))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }


    if (auto answer = good(a, d, left))
    {
        std::cout << answer->left + 1 << " " << answer->right + 1 << '\n';
    }
}
