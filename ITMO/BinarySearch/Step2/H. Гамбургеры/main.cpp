#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

struct Hamburgers {
    std::array<long long, 3> recipe; // B, S, C counts per burger
    std::array<long long, 3> available; // nb, ns, nc
    std::array<long long, 3> prices; // pb, ps, pc
    long long money;

    Hamburgers(const std::string& recipeStr, long long nb, long long ns, long long nc,
          long long pb, long long ps, long long pc, long long r)
        : recipe { 0, 0, 0 }
        , available { nb, ns, nc }
        , prices { pb, ps, pc }
        , money(r) {

        // Parse recipe
        for (char c : recipeStr) {
            switch (c) {
            case 'B':
                recipe[0]++;
                break;
            case 'S':
                recipe[1]++;
                break;
            case 'C':
                recipe[2]++;
                break;
            }
        }
    }

    bool canMake(long long x) const {
        std::array<long long, 3> needed;
        for (int i = 0; i < 3; i++) {
            needed[i] = recipe[i] * x;
        }

        long long totalCost = 0;
        for (int i = 0; i < 3; i++) {
            if (available[i] >= needed[i])
                continue;
            totalCost += (needed[i] - available[i]) * prices[i];
        }

        return totalCost <= money;
    }

    long long search() {
        long long left = 0;
        long long right = money + 300; // Upper bound

        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (canMake(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return right - 1;
    }
};

int main() {
    char recipeStr[111];
    if (scanf("%s", recipeStr) != 1) {
        return 1;
    }

    long long nb, ns, nc;
    long long pb, ps, pc;
    long long r;

    if (scanf("%I64d%I64d%I64d", &nb, &ns, &nc) != 3) {
        return 1;
    }
    if (scanf("%I64d%I64d%I64d", &pb, &ps, &pc) != 3) {
        return 1;
    }
    if (scanf("%I64d", &r) != 1) {
        return 1;
    }

    Hamburgers solver(std::string(recipeStr), nb, ns, nc, pb, ps, pc, r);
    long long result = solver.search();
    printf("%I64d\n", result);

    return 0;
}