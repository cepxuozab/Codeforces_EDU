#include <iostream>

auto z_gray(int k, int j) -> int {
    if (j == 0) {
        return 0;
    }
    if (k == 1) {
        return 0;
    }

    int mid = (1 << (k - 1)) - 1;

    if (j < mid) {
        return z_gray(k - 1, j);
    } else if (j == mid) {
        return 0;
    } else {
        int j_prime = j - mid - 1;
        if (j_prime == 0) {
            return (1 << (k - 1)) - 1;
        } else {
            return z_gray(k - 1, j_prime);
        }
    }
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int k, j;
        std::cin >> k >> j;
        std::cout << z_gray(k, j) << "\n";
    }

    return 0;
}