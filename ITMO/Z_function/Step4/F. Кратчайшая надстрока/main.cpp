#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

// Универсальная Z-функция для "виртуальной строки"
template <class CharAt>
auto compute_z(std::size_t n, CharAt char_at) -> std::vector<std::size_t>
{
    std::vector<std::size_t> z(n);

    for (std::size_t i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
        {
            z[i] = std::min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && char_at(z[i]) == char_at(i + z[i]))
        {
            ++z[i];
        }

        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

auto is_substring(std::string_view pattern, std::string_view text) -> bool
{
    if (pattern.empty()) return true;
    if (pattern.size() > text.size()) return false;

    const std::size_t n = pattern.size() + 1 + text.size();

    auto char_at = [&](std::size_t i)
        -> char
    {
        if (i < pattern.size()) return pattern[i];
        if (i == pattern.size()) return '#';
        return text[i - pattern.size() - 1];
    };

    const auto z = compute_z(n, char_at);

    for (std::size_t i = pattern.size() + 1; i < n; ++i)
    {
        if (z[i] == pattern.size())
            return true;
    }

    return false;
}

auto max_overlap(std::string_view s1, std::string_view s2) -> std::size_t
{
    if (s1.empty() || s2.empty())
        return 0;

    const std::size_t n = s2.size() + 1 + s1.size();

    auto char_at = [&](std::size_t i)
        -> char
    {
        if (i < s2.size()) return s2[i];
        if (i == s2.size()) return '#';
        return s1[i - s2.size() - 1];
    };

    const auto z = compute_z(n, char_at);

    std::size_t max_overlap = 0;

    for (std::size_t i = s2.size() + 1; i < n; ++i)
    {
        std::size_t pos = i - (s2.size() + 1);
        std::size_t remaining = s1.size() - pos;

        if (z[i] == remaining && z[i] <= s2.size())
        {
            max_overlap = std::max(max_overlap, z[i]);
        }
    }

    return max_overlap;
}

auto shortest_superstring(std::string_view s, std::string_view t) -> std::string
{
    if (is_substring(t, s))
        return std::string{s};

    if (is_substring(s, t))
        return std::string{t};

    const auto overlap1 = max_overlap(s, t);

    if (auto overlap2 = max_overlap(t, s); overlap1 >= overlap2)
    {
        std::string result{s};
        result.append(t.substr(overlap1));
        return result;
    }
    else
    {
        std::string result{t};
        result.append(s.substr(overlap2));
        return result;
    }
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    while (q--)
    {
        std::string s, t;
        std::cin >> s >> t;

        std::cout << shortest_superstring(s, t) << '\n';
    }
}
