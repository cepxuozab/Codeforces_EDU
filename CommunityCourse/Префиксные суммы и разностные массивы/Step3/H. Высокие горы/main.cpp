#include <iostream>
#include <vector>
#include <map>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> sp(n);
    for (auto& i : sp) std::cin >> i;
    int q;
    std::cin >> q;
    std::map<int, int> dct;
    for (int i = 0; i < q; ++i)
    {
        int k, x;
        std::cin >> k >> x;
        dct[n - k] += x;
    }
    int d = 0;
    for (int j = dct.begin()->first; j < n; ++j)
    {
        d += dct[j];
        sp[j] += d;
    }
    for (auto i : sp) std::cout << i << " ";
}


