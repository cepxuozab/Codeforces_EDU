#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

auto check(vector<double> const& v, int k, double x) -> bool
{

    int sum = 0;
    for (auto const& e : v) {
        sum += int(e / x);
    }

    return sum >= k;
}

auto bs(vector<double> const& v, int k) -> double
{

    double l = 0;
    double r = 1e8;

    for (double i = 0; i < 100; ++i) {

        double mid = (l + r) / 2;

        if (check(v, k, mid))
            l = mid;
        else
            r = mid;
    }

    return l;
}

auto main() -> int
{
    int n, k;
    cin >> n >> k;

    vector<double> v(n);
    for (auto& e : v)
        std::cin >> e;

    cout << setprecision(9) << bs(v, k);

    return 0;
}
