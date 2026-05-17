#include <iostream>
#include <vector>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int> d(n);
    for (auto& it : d) std::cin >> it;
    std::vector<std::pair<long long, std::pair<long long, long long>>> prq;

    for (int i = 0; i < m; i++)
    {
        int fr, to, val;
        std::cin >> fr >> to >> val;
        prq.push_back({val, {--fr, to}});
    }

    std::vector<long long> frq_wh(m + 1);

    for (int i = 0, x, y; i < q && std::cin >> x >> y; i++)frq_wh[--x]++, frq_wh[y]--;

    for (int i = 1; i <= m; i++) frq_wh[i] += frq_wh[i - 1];

    std::vector<long long> sum(n + 7);

    for (int i = 0; i < m; i++)
    {
        sum[prq[i].second.first] += prq[i].first * frq_wh[i];
        sum[prq[i].second.second] -= prq[i].first * frq_wh[i];
    }

    for (int i = 1; i < n; i++) sum[i] += sum[i - 1];

    for (int i = 0; i < n; i++) std::cout << d[i] + sum[i] << " ";
}
