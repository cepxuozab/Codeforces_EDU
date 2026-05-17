#include <iostream>
#include <vector>
#include <algorithm>

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> arr(n);
    for (int& a : arr)std::cin >> a;
    for (int i = 0; i < m; ++i)
    {
        int x;
        std::cin >> x;
        std::cout<<std::ranges::upper_bound(arr,x)-arr.begin()<<'\n';
    }
}
