#include <cstdint>
#include <iostream>
#include <vector>

class RandomGenerator {
public:
    RandomGenerator(unsigned int a, unsigned int b)
        : a_(a), b_(b) {}

    auto nextRand() -> unsigned int {
        cur_ = cur_ * a_ + b_;
        return cur_ >> 8;
    }

private:
    unsigned int a_;
    unsigned int b_;
    unsigned int cur_{0};
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int m, q;
    std::cin >> m >> q;

    unsigned int a, b;
    std::cin >> a >> b;

    constexpr unsigned int N = 1u << 24;

    RandomGenerator rng(a, b);

    std::vector<unsigned int> diff(N + 1, 0);

    for (unsigned int i = 0; i < m; ++i) {
        unsigned int add = rng.nextRand();
        unsigned int l = rng.nextRand();
        unsigned int r = rng.nextRand();

        if (l > r) {
            unsigned int tmp = l;
            l = r;
            r = tmp;
        }

        diff[l] += add;

        if (r + 1 < N) {
            diff[r + 1] -= add;
        }
    }

    std::vector<unsigned int> pref(N + 1, 0);

    unsigned int current = 0;

    for (unsigned int i = 0; i < N; ++i) {
        current += diff[i];
        pref[i + 1] = pref[i] + current;
    }

    unsigned int answer = 0;

    for (unsigned int i = 0; i < q; ++i) {
        unsigned int l = rng.nextRand();
        unsigned int r = rng.nextRand();

        if (l > r) {
            unsigned int tmp = l;
            l = r;
            r = tmp;
        }

        answer += pref[r + 1] - pref[l];
    }

    std::cout << answer << '\n';

    return 0;
}