#include <iostream>
#include <vector>

auto main() -> int
{
    int n;
    std::cin >> n;
    std::vector<long long> prefix{0};
    for (int i = 0; i < n; ++i)
    {
        long long x;
        std::cin >> x;
        prefix.push_back(prefix.back() + x);
    }
    for (auto x : prefix) std::cout << x << " ";
}
