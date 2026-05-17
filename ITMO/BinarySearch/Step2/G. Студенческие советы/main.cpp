#include <algorithm>
#include <cstdio>
#include <vector>

struct StudentCouncils {
    long long k;
    std::vector<long long> votes;
    long long totalVotes;

    StudentCouncils(long long kVal, const std::vector<long long>& votesData)
        : k(kVal)
        , votes(votesData)
        , totalVotes(0) {
        for (auto v : votes) {
            totalVotes += v;
        }
    }

    bool check(long long x) const {
        long long num = 0;
        for (auto v : votes) {
            num += std::min(v, x);
        }
        return num >= k * x;
    }

    long long search() {
        long long left = 0;
        long long right = totalVotes;

        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (check(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return right - 1;
    }
};

int main() {
    long long k, n;
    if (scanf("%lld%lld", &k, &n) != 2) {
        return 1;
    }

    std::vector<long long> nums(n);
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &nums[i]) != 1) {
            return 1;
        }
    }

    StudentCouncils solver(k, nums);
    long long result = solver.search();
    printf("%lld\n", result);

    return 0;
}