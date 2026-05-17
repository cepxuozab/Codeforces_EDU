#include <iostream>

auto main()->int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x;
                std::cin >> x;
                if (x != 0)
                    std::cout << j + 1 << ' ';
            }
            std::cout << '\n';
        }        
    }

    return 0;
}
