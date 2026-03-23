#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct BallManInfo {
    int T; // время надувания одного шарика
    int Z; // кол-во шаров, которые человек надувает без отдыха
    int Y; // время отдыха

    BallManInfo(int t, int z, int y)
        : T(t)
        , Z(z)
        , Y(y) { }
};

bool Check(int t, int m, const std::vector<BallManInfo>& ballManInfoList) {
    long long cnt = 0;

    for (const auto& ballMan : ballManInfoList) {
        // кол-во шаров, которые человек надует за время t с учетом отдыха
        long long cycleTime = 1LL * ballMan.T * ballMan.Z + ballMan.Y;
        long long ballCountWithoutRest = (t / cycleTime) * ballMan.Z;

        // если время t еще осталось, попробуем надуть столько шаров, сколько сможем за
        // это время в лучшем случае, это будет Z
        long long remainingTime = t % cycleTime;
        long long ballCountByTime = std::min(remainingTime / ballMan.T, 1LL * ballMan.Z);

        cnt += ballCountWithoutRest + ballCountByTime;

        // если уже превысили нужное количество, можно досрочно выйти
        if (cnt >= m) {
            return true;
        }
    }

    return cnt >= m;
}

int GetBallCount(int m, const std::vector<BallManInfo>& ballManInfoList) {
    int left = -1;
    int right = 10000000; // увеличиваем правую границу для безопасности

    while (right - left > 1) {
        int t = left + (right - left) / 2;

        if (Check(t, m, ballManInfoList)) {
            right = t;
        } else {
            left = t;
        }
    }

    return right;
}

int main() {
    int m, n;
    std::cin >> m >> n;

    std::vector<BallManInfo> ballManInfoList;
    ballManInfoList.reserve(n);

    for (int i = 0; i < n; ++i) {
        int t, z, y;
        std::cin >> t >> z >> y;
        ballManInfoList.emplace_back(t, z, y);
    }

    if (m == 0) {
        std::cout << 0 << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << 0 << " ";
        }
        std::cout << std::endl;
        return 0;
    }

    int T = GetBallCount(m, ballManInfoList);
    std::cout << T << std::endl;

    // Вычисляем количество шариков для каждого помощника
    int remainingBalls = m;
    for (int i = 0; i < n; ++i) {
        if (remainingBalls == 0) {
            std::cout << 0 << " ";
            continue;
        }

        const auto& ballMan = ballManInfoList[i];
        long long cycleTime = 1LL * ballMan.T * ballMan.Z + ballMan.Y;
        long long fullCycles = T / cycleTime;
        int ballsInFullCycles = fullCycles * ballMan.Z;

        int remainingTime = T % cycleTime;
        int additionalBalls = std::min(remainingTime / ballMan.T, ballMan.Z);

        int totalBallsForCurrent = ballsInFullCycles + additionalBalls;
        int ballsToTake = std::min(totalBallsForCurrent, remainingBalls);

        std::cout << ballsToTake << " ";
        remainingBalls -= ballsToTake;
    }
    std::cout << std::endl;

    return 0;
}