def count_substrings(s: str, cards: str) -> int:
    card_frequencies = [0] * 26
    for card in cards:
        card_frequencies[ord(card) - ord('a')] += 1
    window_frequencies = [0] * 26
    total_substrings = 0
    right = 0
    for left in range(len(s)):
        while right < len(s):
            idx = ord(s[right]) - ord('a')
            if window_frequencies[idx] + 1 <= card_frequencies[idx]:
                window_frequencies[idx] += 1
                right += 1
            else:
                break

        total_substrings += (right - left)
        window_frequencies[ord(s[left]) - ord('a')] -= 1

    return total_substrings


def main():
    n, m = map(int, input().split())
    s = input()
    cards = input()
    print(count_substrings(s, cards))


if __name__ == "__main__":
    main()
