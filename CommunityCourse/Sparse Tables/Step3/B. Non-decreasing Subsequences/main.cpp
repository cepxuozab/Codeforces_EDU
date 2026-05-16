#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

namespace {

constexpr int MOD = 1'000'000'007;
constexpr int MAX_K = 21;

[[nodiscard]] inline auto addmod(int a) -> int {
    if (a >= MOD) a -= MOD;
    return a;
}

struct State {
    int N{};
    int K{};
    int Q{};

    std::vector<int> A;
    std::vector<int> L;
    std::vector<int> R;
    std::vector<int> qid;
    std::vector<int> ans;

    std::vector<std::array<int, MAX_K>> lans;
    std::vector<std::array<int, MAX_K>> rans;
    std::array<int, MAX_K> cnt{};

    explicit State(int n, int k, int q)
        : N(n), K(k), Q(q),
          A(n), L(q), R(q), qid(q), ans(q),
          lans(n), rans(n) {
        for (auto& arr : lans) arr.fill(0);
        for (auto& arr : rans) arr.fill(0);
        cnt.fill(0);
    }
};

class NonDecSubseqSolver {
public:
    void processCase() {
        int N, K;
        std::cin >> N >> K;

        // Читаем массив A до того, как станет известно Q
        std::vector<int> tempA(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> tempA[i];
        }

        int Q;
        std::cin >> Q;

        // Теперь все параметры известны, создаём состояние
        State state(N, K, Q);
        state.A = std::move(tempA);

        for (int i = 0; i < Q; ++i) {
            std::cin >> state.L[i] >> state.R[i];
            --state.L[i];
            --state.R[i];
            state.qid[i] = i;
        }

        solveRecursive(state, 0, N - 1, 0, Q - 1);

        for (int i = 0; i < Q; ++i) {
            std::cout << addmod(state.ans[i] + 1) << '\n';
        }
    }

private:
    void countLeft(State& state, int l, int r) {
        const int K = state.K;
        auto& A = state.A;
        auto& lans = state.lans;
        auto& cnt = state.cnt;

        for (int i = l; i <= r; ++i) {
            std::fill(lans[i].begin() + 1, lans[i].begin() + K + 1, 0);
        }

        for (int k = K; k >= 1; --k) {
            std::fill(cnt.begin() + k, cnt.begin() + K + 1, 0);

            for (int i = r; i >= l; --i) {
                if (A[i] == k) {
                    cnt[k] = addmod(2 * cnt[k] + 1);
                    for (int j = k + 1; j <= K; ++j) {
                        cnt[j] = addmod(addmod(2 * cnt[j]) + lans[i][j]);
                    }
                }
                for (int j = k; j <= K; ++j) {
                    lans[i][j] = addmod(lans[i][j] + cnt[j]);
                }
            }
        }
    }

    void countRight(State& state, int l, int r) {
        const int K = state.K;
        auto& A = state.A;
        auto& rans = state.rans;
        auto& cnt = state.cnt;

        for (int i = l; i <= r; ++i) {
            std::fill(rans[i].begin() + 1, rans[i].begin() + K + 1, 0);
        }

        for (int k = 1; k <= K; ++k) {
            std::fill(cnt.begin() + 1, cnt.begin() + k + 1, 0);

            for (int i = l; i <= r; ++i) {
                if (A[i] == k) {
                    cnt[k] = addmod(2 * cnt[k] + 1);
                    for (int j = 1; j < k; ++j) {
                        cnt[j] = addmod(addmod(2 * cnt[j]) + rans[i][j]);
                    }
                }
                for (int j = 1; j <= k; ++j) {
                    rans[i][j] = addmod(rans[i][j] + cnt[j]);
                }
            }
        }
    }

    [[nodiscard]] int partitionQueries(State& state, int qa, int qb, int mid) {
        const auto& R = state.R;
        auto& qid = state.qid;

        int i = qa;
        int j = qb;

        while (i < j) {
            if (R[qid[i]] > mid && R[qid[j]] <= mid) {
                std::swap(qid[i], qid[j]);
                ++i;
                --j;
            } else if (R[qid[i]] > mid) {
                --j;
            } else if (R[qid[j]] <= mid) {
                ++i;
            } else {
                ++i;
                --j;
            }
        }

        if (i > j) return j;
        if (R[qid[i]] <= mid) return i;
        return i - 1;
    }

    void solveRecursive(State& state, int l, int r, int qa, int qb) {
        if (l > r || qa > qb) return;

        if (l == r) {
            for (int i = qa; i <= qb; ++i) {
                state.ans[state.qid[i]] = 1;
            }
            return;
        }

        const int mid = (l + r) >> 1;
        auto& lans = state.lans;
        auto& rans = state.rans;

        countLeft(state, l, mid);
        countRight(state, mid + 1, r);

        // Префиксные суммы для rans
        for (int i = mid + 1; i <= r; ++i) {
            for (int k = state.K - 1; k >= 1; --k) {
                rans[i][k] = addmod(rans[i][k] + rans[i][k + 1]);
            }
        }

        int processed = 0;
        for (int i = qa; i <= qb; ++i) {
            const int q = state.qid[i];

            if (state.L[q] <= mid && state.R[q] > mid) {
                int& result = state.ans[q];
                result = 0;

                for (int k = 1; k <= state.K; ++k) {
                    const long long product =
                        static_cast<long long>(lans[state.L[q]][k]) *
                        rans[state.R[q]][k];
                    result = addmod(result + static_cast<int>(product % MOD));
                }

                for (int k = 1; k <= state.K; ++k) {
                    result = addmod(result + lans[state.L[q]][k]);
                }

                result = addmod(result + rans[state.R[q]][1]);

                ++processed;
            } else if (processed > 0) {
                state.qid[i - processed] = state.qid[i];
            }
        }

        qb -= processed;
        const int qm = partitionQueries(state, qa, qb, mid);

        solveRecursive(state, l, mid, qa, qm);
        solveRecursive(state, mid + 1, r, qm + 1, qb);
    }
};

} // anonymous namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int testCases;
    if (!(std::cin >> testCases)) return 0;

    NonDecSubseqSolver solver;
    while (testCases-- > 0) {
        solver.processCase();
    }

    return 0;
}