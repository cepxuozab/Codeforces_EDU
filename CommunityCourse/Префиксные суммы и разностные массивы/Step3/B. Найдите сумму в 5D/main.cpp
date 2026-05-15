#include <array>
#include <cstdint>
#include <iostream>

static int64_t P[17][17][17][17][17];

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n1, n2, n3, n4, n5;
    std::cin >> n1 >> n2 >> n3 >> n4 >> n5;

    for (int i = 1; i <= n1; ++i)
        for (int j = 1; j <= n2; ++j)
            for (int k = 1; k <= n3; ++k)
                for (int l = 1; l <= n4; ++l)
                    for (int m = 1; m <= n5; ++m)
                        std::cin >> P[i][j][k][l][m];

    // Build 5D prefix sums dimension by dimension
    // Dim 5
    for (int i = 1; i <= n1; ++i)
        for (int j = 1; j <= n2; ++j)
            for (int k = 1; k <= n3; ++k)
                for (int l = 1; l <= n4; ++l)
                    for (int m = 2; m <= n5; ++m)
                        P[i][j][k][l][m] += P[i][j][k][l][m-1];
    // Dim 4
    for (int i = 1; i <= n1; ++i)
        for (int j = 1; j <= n2; ++j)
            for (int k = 1; k <= n3; ++k)
                for (int l = 2; l <= n4; ++l)
                    for (int m = 1; m <= n5; ++m)
                        P[i][j][k][l][m] += P[i][j][k][l-1][m];
    // Dim 3
    for (int i = 1; i <= n1; ++i)
        for (int j = 1; j <= n2; ++j)
            for (int k = 2; k <= n3; ++k)
                for (int l = 1; l <= n4; ++l)
                    for (int m = 1; m <= n5; ++m)
                        P[i][j][k][l][m] += P[i][j][k-1][l][m];
    // Dim 2
    for (int i = 1; i <= n1; ++i)
        for (int j = 2; j <= n2; ++j)
            for (int k = 1; k <= n3; ++k)
                for (int l = 1; l <= n4; ++l)
                    for (int m = 1; m <= n5; ++m)
                        P[i][j][k][l][m] += P[i][j-1][k][l][m];
    // Dim 1
    for (int i = 2; i <= n1; ++i)
        for (int j = 1; j <= n2; ++j)
            for (int k = 1; k <= n3; ++k)
                for (int l = 1; l <= n4; ++l)
                    for (int m = 1; m <= n5; ++m)
                        P[i][j][k][l][m] += P[i-1][j][k][l][m];

    int q;
    std::cin >> q;

    while (q--) {
        int l1, l2, l3, l4, l5, r1, r2, r3, r4, r5;
        std::cin >> l1 >> l2 >> l3 >> l4 >> l5
                 >> r1 >> r2 >> r3 >> r4 >> r5;

        // Inclusion-exclusion over 2^5 = 32 subsets
        // For each subset of dimensions, we subtract the "left boundary - 1"
        // Sign: (-1)^(popcount(mask))
        int64_t ans = 0;
        for (int mask = 0; mask < 32; ++mask) {
            int i = (mask >> 0 & 1) ? l1 - 1 : r1;
            int j = (mask >> 1 & 1) ? l2 - 1 : r2;
            int k = (mask >> 2 & 1) ? l3 - 1 : r3;
            int l = (mask >> 3 & 1) ? l4 - 1 : r4;
            int m = (mask >> 4 & 1) ? l5 - 1 : r5;

            // sign: +1 if even number of bits set, -1 if odd
            int bits = __builtin_popcount(mask);
            int64_t val = (i >= 1 && j >= 1 && k >= 1 && l >= 1 && m >= 1)
                          ? P[i][j][k][l][m] : 0;
            if (bits % 2 == 0)
                ans += val;
            else
                ans -= val;
        }
        std::cout << ans << '\n';
    }

    return 0;
}