#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

bool good(const std::vector<std::pair<int, int>>& items, int k, double x) {
    const int n = static_cast<int>(items.size());

    std::vector<double> transformed(n);
    for (int i = 0; i < n; ++i) {
        transformed[i] = items[i].first - x * items[i].second;
    }

    std::sort(transformed.begin(), transformed.end());

    double sum = 0.0;
    for (int i = n - 1; i >= n - k; --i) {
        sum += transformed[i];
    }

    return sum >= 0.0;
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::pair<int, int>> items(n);
    for (auto& [a, b] : items) {
        std::cin >> a >> b;
    }

    double left = 0.0;
    double right = 100000.0;

    for (int i = 0; i < 80; ++i) {
        const double mid = (left + right) / 2.0;

        if (good(items, k, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    std::cout << std::setprecision(10) << left << '\n';
}