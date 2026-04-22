def max_length(s: str, max_rough: int) -> int:
    count_a = 0
    count_b = 0
    curr_rudeness = 0
    left = 0
    max_len = 0
    for right in range(len(s)):
        ch = s[right]
        if ch == 'b':
            curr_rudeness += count_a
            count_b += 1
        elif ch == 'a':
            count_a += 1
        while curr_rudeness > max_rough and left <= right:
            left_ch = s[left]
            if left_ch == 'a':
                count_a -= 1
                curr_rudeness -= count_b
            elif left_ch == 'b':
                count_b -= 1
            left += 1
        max_len = max(max_len, right - left + 1)
    return max_len


def main():
    n, rudeness = map(int, input().split())
    s = input()
    print(max_length(s, rudeness))


if __name__ == '__main__':
    main()
