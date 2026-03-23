#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

struct GameState {
    std::vector<char> pattern;
    std::vector<char> text;
    std::vector<long long> removalOrder;
    std::vector<long long> removedFlag;
    long long checkCounter;

    GameState(const char* p, const char* t, const std::vector<long long>& nums)
        : pattern(p, p + strlen(p))
        , text(t, t + strlen(t))
        , removalOrder(nums)
        , removedFlag(pattern.size(), 0)
        , checkCounter(0) { }

    bool check(long long x) {
        checkCounter++;
        for (long long i = 0; i < x; i++) {
            removedFlag[removalOrder[i] - 1] = checkCounter;
        }

        size_t textIndex = 0;
        for (size_t patternIndex = 0;
              patternIndex < pattern.size() && textIndex < text.size(); patternIndex++) {
            if (removedFlag[patternIndex] == checkCounter)
                continue;
            if (pattern[patternIndex] == text[textIndex]) {
                textIndex++;
            }
        }
        return textIndex == text.size();
    }

    long long search() {
        long long left = 0;
        long long right = pattern.size();

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
    const int MAX_N = 200000 + 2;
    char pattern[MAX_N];
    char text[MAX_N];

    if (scanf("%s%s", pattern, text) != 2) {
        return 1;
    }

    int patternLength = strlen(pattern);
    std::vector<long long> removalOrder(patternLength);

    for (int i = 0; i < patternLength; i++) {
        if (scanf("%lld", &removalOrder[i]) != 1) {
            return 1;
        }
    }

    GameState gameState(pattern, text, removalOrder);
    long long result = gameState.search();
    printf("%I64d\n", result);

    return 0;
}