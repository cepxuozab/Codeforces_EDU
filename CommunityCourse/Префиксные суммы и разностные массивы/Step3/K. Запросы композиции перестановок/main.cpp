#include <algorithm>
#include <cmath>
#include <iostream>
#include <ranges>
#include <span>
#include <unordered_map>
#include <vector>
#include <numeric>

// z[i] = y[x[i] - 1]
static void compose(std::span<const int> x, std::span<const int> y, std::span<int> z)
{
    for (int i = 0; i < static_cast<int>(x.size()); ++i)
    {
        z[i] = y[x[i] - 1];
    }
}

// out[p[i] - 1] = i + 1
static void invert(std::span<const int> p, std::span<int> out)
{
    for (int i = 0; i < static_cast<int>(p.size()); ++i)
    {
        out[p[i] - 1] = i + 1;
    }
}

static auto dot(std::span<const int> p) -> long long
{
    long long result = 0;
    for (int i = 0; i < static_cast<int>(p.size()); ++i)
    {
        result += static_cast<long long>(i + 1) * p[i];
    }
    return result;
}

// Плоский 2D-массив: строки как span-ы без лишних аллокаций
struct FlatArray
{
    std::vector<int> data;
    int cols;

    FlatArray(int rows, int cols_, bool fill_identity = false)
        : data(static_cast<std::size_t>(rows) * cols_)
          , cols(cols_)
    {
        if (fill_identity)
        {
            for (int r = 0; r < rows; ++r)
                std::ranges::iota(row(r), 1);
        }
    }

    auto row(int r) -> std::span<int>
    {
        return std::span<int>(data).subspan(static_cast<std::size_t>(r) * cols, cols);
    }

    [[nodiscard]] auto row(int r) const -> std::span<const int>
    {
        return std::span<const int>(data).subspan(static_cast<std::size_t>(r) * cols, cols);
    }
};

auto main() -> int//NOLINT
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--)
    {
        int n;
        int m;
        std::cin >> n >> m;

        FlatArray a(n, m);
        for (int i = 0; i < n * m; ++i)
            std::cin >> a.data[i];

        const int threshold = std::max(1, static_cast<int>(std::sqrt(static_cast<double>(n * m))));

        int q;
        std::cin >> q;

        if (n <= threshold)
        {
            // n маленькое: prefix-композиция + мемоизация по (l, r)
            FlatArray prefix(n + 1, m);
            std::ranges::iota(prefix.row(0), 1); // identity

            for (int i = 0; i < n; ++i)
                compose(prefix.row(i), a.row(i), prefix.row(i + 1));

            FlatArray inv_prefix(n + 1, m);
            for (int i = 0; i <= n; ++i)
                invert(prefix.row(i), inv_prefix.row(i));

            std::unordered_map<int, long long> memo;
            memo.reserve(1 << 17);
            std::vector<int> current(m);

            while (q--)
            {
                int l, r;
                std::cin >> l >> r;
                --l; // query(l,r) = inv_prefix[l] * prefix[r]

                const int key = l * (n + 1) + r;
                const auto it = memo.find(key);
                if (it != memo.end())
                {
                    std::cout << it->second << '\n';
                    continue;
                }

                compose(inv_prefix.row(l), prefix.row(r), current);
                const long long answer = dot(current);
                memo[key] = answer;
                std::cout << answer << '\n';
            }
        }
        else
        {
            // m маленькое: sqrt-декомпозиция по блокам
            const int block_size = std::max(1, static_cast<int>(std::sqrt(static_cast<double>(n))));
            const int block_count = (n + block_size - 1) / block_size;

            FlatArray block_perm(block_count, m, /*fill_identity=*/true);
            std::vector<int> temp(m);

            for (int block = 0; block < block_count; ++block)
            {
                const int lo = block * block_size;
                const int hi = std::min(n, lo + block_size);
                for (int i = lo; i < hi; ++i)
                {
                    compose(block_perm.row(block), a.row(i), temp);
                    std::ranges::copy(temp, block_perm.row(block).begin());
                }
            }

            std::vector<int> current(m);

            while (q--)
            {
                int l, r;
                std::cin >> l >> r;
                --l;
                --r;

                std::ranges::iota(current, 1); // identity

                const int bl = l / block_size;
                const int br = r / block_size;

                auto apply = [&](int i)
                -> void {
                    compose(current, a.row(i), temp);
                    std::ranges::copy(temp, current.begin());
                };

                auto apply_block = [&](int b)
                -> void {
                    compose(current, block_perm.row(b), temp);
                    std::ranges::copy(temp, current.begin());
                };

                if (bl == br)
                {
                    for (int i = l; i <= r; ++i) apply(i);
                }
                else
                {
                    for (int i = l, end = (bl + 1) * block_size; i < end; ++i) apply(i);
                    for (int b = bl + 1; b < br; ++b) apply_block(b);
                    for (int i = br * block_size; i <= r; ++i) apply(i);
                }

                std::cout << dot(current) << '\n';
            }
        }
    }

    return 0;
}
