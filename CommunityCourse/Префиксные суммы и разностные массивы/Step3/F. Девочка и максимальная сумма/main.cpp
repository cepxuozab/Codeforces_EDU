#include <iostream>
#include <vector>
#include <algorithm>

auto main() -> int //NOLINT
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n), cnt(n + 1);
    for (int i = 0; i < n; i++) std::cin >> a[i];
    std::ranges::sort(a);
    while (q--)
    {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        cnt[l]++;
        cnt[r + 1]--;
    }
    for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
    std::ranges::sort(cnt.data(), cnt.data() + n);
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--)
        ans += 1ll * cnt[i] * a[i];
    std::cout << ans << '\n';
}
