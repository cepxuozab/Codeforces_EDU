#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <cstdint>

class SuffixAutomaton {
public:
    struct State {
        int len = 0;
        int cnt = 0;
        char can = -1;
        std::shared_ptr<State> link = nullptr;
        std::array<std::shared_ptr<State>, 10> next{};

        State() {
            next.fill(nullptr);
        }
    };

    SuffixAutomaton(std::size_t max_len)
        : pos(max_len + 1)
    {
        root = std::make_shared<State>();
        last = root;
    }

    void extend(int c) {
        auto cur = std::make_shared<State>();
        cur->len = last->len + 1;
        cur->cnt = 1;
        pos[cur->len].push_back(cur);

        auto p = last;
        while (p && !p->next[c]) {
            p->next[c] = cur;
            p = p->link;
        }

        if (!p) {
            cur->link = root;
        } else {
            auto q = p->next[c];
            if (p->len + 1 == q->len) {
                cur->link = q;
            } else {
                auto clone = std::make_shared<State>();
                clone->len = p->len + 1;
                clone->next = q->next;
                clone->link = q->link;

                pos[clone->len].push_back(clone);

                while (p && p->next[c] == q) {
                    p->next[c] = clone;
                    p = p->link;
                }

                q->link = clone;
                cur->link = clone;
            }
        }

        last = cur;
    }

    [[nodiscard]] auto compute_best() const -> std::pair<std::int64_t, std::shared_ptr<State>> {
        std::int64_t best = 0;
        std::shared_ptr<State> best_ptr = nullptr;

        for (int i = static_cast<int>(pos.size()) - 1; i > 0; --i) {
            for (const auto& x : pos[i]) {
                if (x->link) {
                    x->link->cnt += x->cnt;
                }

                std::int64_t cur = static_cast<std::int64_t>(x->len) * x->cnt;
                if (cur > best) {
                    best = cur;
                    best_ptr = x;
                }
            }
        }

        return {best, best_ptr};
    }

    [[nodiscard]] auto get_root() const -> std::shared_ptr<State> {
        return root;
    }

    static auto can(const std::shared_ptr<State>& v) -> char {
        if (!v) return 0;
        if (v->can != -1) return v->can;
        return v->can = can(v->link);
    }

private:
    std::shared_ptr<State> root;
    std::shared_ptr<State> last;
    std::vector<std::vector<std::shared_ptr<State>>> pos;
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0, m = 0;
    std::cin >> n >> m;

    std::vector<int> a(n);
    SuffixAutomaton sa(static_cast<std::size_t>(n));

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
        sa.extend(a[i]);
    }

    auto [best, bp] = sa.compute_best();
    bp->can = 1;

    std::cout << best << '\n';
    std::cout << bp->len << '\n';

    auto cur = sa.get_root();

    for (int i = 0; i < n; ++i) {
        cur = cur->next[a[i]];
        if (SuffixAutomaton::can(cur)) {
            for (int j = 0; j < bp->len; ++j) {
                if (j) std::cout << ' ';
                std::cout << a[i - bp->len + j + 1] + 1;
            }
            std::cout << '\n';
            return 0;
        }
    }

    return 0;
}