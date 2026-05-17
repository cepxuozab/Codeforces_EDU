#include <iostream>
#include <vector>
#include <stack>
#include <ranges>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n + 1);
    for (auto& x : a | std::views::drop(1))
        std::cin >> x;

    std::vector<int> L(n + 1), R(n + 1);

    {
        std::stack<int> q;
        for (int i : std::views::iota(1, n + 1))
        {
            while (!q.empty() && (a[q.top()] | a[i]) == a[i] && a[q.top()] != a[i])
                q.pop();
            L[i] = q.empty() ? 1 : q.top() + 1;
            q.push(i);
        }
    }
    {
        std::stack<int> p;
        for (int i : std::views::iota(1, n + 1) | std::views::reverse)
        {
            while (!p.empty() && (a[p.top()] | a[i]) == a[i])
                p.pop();
            R[i] = p.empty() ? n : p.top() - 1;
            p.push(i);
        }
    }

    long long bad = 0;
    for (int i : std::views::iota(1, n + 1))
        bad += static_cast<long long>(i - L[i]) * (R[i] - i) + (R[i] - L[i]);

    std::cout << static_cast<long long>(n) * (n - 1) / 2 - bad << '\n';
    return 0;
}
