#include <algorithm>
#include <bit>
#include <cstdint>
#include <iostream>
#include <vector>

static constexpr int B   = 32;
static constexpr int TRI = B * (B + 1) / 2;

static constexpr int tri_idx(int i, int j) noexcept {
    return i * B - i * (i - 1) / 2 + j - i;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        int     n, q;
        int64_t p;
        std::cin >> n >> p >> q;

        std::vector<int> a(n);
        for (int& v : a) {
            std::cin >> v;
            v = static_cast<int>(v % p);
        }

        const int nb = (n + B - 1) / B;

        // ── 1. Intra-block triangular table ───────────────────────────────────
        // intra[bl * TRI + tri_idx(i, j)] = product(a[bl*B+i .. bl*B+j]) % p
        std::vector<int64_t> intra(static_cast<std::size_t>(nb) * TRI);
        std::vector<int64_t> block_prod(nb);

        for (int bl = 0; bl < nb; ++bl) {
            const int start = bl * B;
            const int len   = std::min(B, n - start);
            int64_t* base   = intra.data() + static_cast<std::size_t>(bl) * TRI;

            for (int i = 0; i < len; ++i) {
                int64_t run = 1;
                for (int j = i; j < len; ++j) {
                    run              = run * a[start + j] % p;
                    base[tri_idx(i, j)] = run;
                }
            }
            block_prod[bl] = base[tri_idx(0, len - 1)];
        }

        const auto intra_query = [&](int bl, int i, int j) noexcept -> int64_t {
            return intra[static_cast<std::size_t>(bl) * TRI + tri_idx(i, j)];
        };

        // ── 2. Disjoint Sparse Table on block products ────────────────────────
        // Level k covers groups of 2^(k+1) blocks, centre = lo + 2^k - 1.
        //   suf[k][b] = product(block[b .. centre])    for b in [lo .. centre]
        //   pre[k][b] = product(block[centre+1 .. b])  for b in [centre+1 .. hi]
        // Query [lb, rb] (lb != rb):
        //   k = bit_width(lb ^ rb) - 1  →  answer = suf[k][lb] * pre[k][rb]
        //
        // We only need levels where 2^k < nb, so LOG = bit_width(nb-1) suffices.
        // (bit_width(0) is defined as 0 in C++20, handle nb==1 separately.)
        const int LOG = (nb > 1) ? std::bit_width(static_cast<unsigned>(nb - 1)) : 1;

        std::vector<int64_t> suf_flat(static_cast<std::size_t>(LOG) * nb, 1);
        std::vector<int64_t> pre_flat(static_cast<std::size_t>(LOG) * nb, 1);

        for (int k = 0; k < LOG; ++k) {
            const int half = 1 << k;
            const int full = 1 << (k + 1);
            int64_t* suf   = suf_flat.data() + static_cast<std::size_t>(k) * nb;
            int64_t* pre   = pre_flat.data() + static_cast<std::size_t>(k) * nb;

            for (int lo = 0; lo < nb; lo += full) {
                const int mid = lo + half - 1;
                const int hi  = std::min(lo + full - 1, nb - 1);

                // mid is always < nb here because k < LOG = bit_width(nb-1),
                // so 2^k <= nb-1, meaning lo + half - 1 <= nb - 1 when lo == 0.
                // For lo > 0 the group starts later so mid is even smaller.
                int64_t run = 1;
                for (int b = mid; b >= lo; --b) {
                    run    = run * block_prod[b] % p;
                    suf[b] = run;
                }
                run = 1;
                for (int b = mid + 1; b <= hi; ++b) {
                    run    = run * block_prod[b] % p;
                    pre[b] = run;
                }
            }
        }

        const auto block_range = [&](int lb, int rb) noexcept -> int64_t {
            if (lb > rb) return 1;
            if (lb == rb) return block_prod[lb];
            const int      k   = std::bit_width(static_cast<unsigned>(lb ^ rb)) - 1;
            const int64_t* suf = suf_flat.data() + static_cast<std::size_t>(k) * nb;
            const int64_t* pre = pre_flat.data() + static_cast<std::size_t>(k) * nb;
            return suf[lb] * pre[rb] % p;
        };

        // ── 3. Segment product query ──────────────────────────────────────────
        const auto query = [&](int l, int r) noexcept -> int64_t {
            const int lb = l / B;
            const int rb = r / B;
            if (lb == rb) {
                return intra_query(lb, l - lb * B, r - lb * B);
            }
            int64_t res = intra_query(lb, l - lb * B, B - 1);
            res = res * block_range(lb + 1, rb - 1) % p;
            res = res * intra_query(rb, 0, r - rb * B) % p;
            return res;
        };

        // ── 4. Online query processing ────────────────────────────────────────
        const int ns = q / 64 + 2;
        std::vector<int> b(ns);
        for (int& v : b) std::cin >> v;

        int64_t x  = 0;
        int     lp = 0, rp = 0;

        for (int i = 0; i < q; ++i) {
            int l, r;
            if ((i & 63) == 0) {
                l = static_cast<int>((static_cast<int64_t>(b[i >> 6])       + x) % n);
                r = static_cast<int>((static_cast<int64_t>(b[(i >> 6) + 1]) + x) % n);
            } else {
                l = static_cast<int>((static_cast<int64_t>(lp) + x) % n);
                r = static_cast<int>((static_cast<int64_t>(rp) + x) % n);
            }
            if (l > r) std::swap(l, r);

            x = query(l, r) + 1;
            if (x >= p) x -= p;
            lp = l;
            rp = r;
        }

        std::cout << x << '\n';
    }

    return 0;
}
