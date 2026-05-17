#include <iostream>

auto main()->int {//NOLINT
    int t;
    std::cin >> t;

    while (t--) {
        int d1, d2;
        std::cin >> d1 >> d2;
        if (d1 != d2) {
            std::cout << "NO\n";
            continue;
        }

        int d = d1;
        int n = d;
        int m = n * d;

        std::cout << "YES\n";
        std::cout << n << " " << m << "\n";

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    std::cout << i << " " << j << "\n";
                }
            }
            // петля
            std::cout << i << " " << i << "\n";
        }
    }

    return 0;
}
