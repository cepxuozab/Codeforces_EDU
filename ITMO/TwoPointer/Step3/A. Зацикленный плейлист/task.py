def solve(songs: list[int], max_positivity: int) -> tuple[int, int]:
    s = sum(songs)
    cycles = max_positivity//s
    rem = max_positivity % s
    if rem == 0:
        rem = s
        cycles -= 1
    doubled = songs + songs
    best_length = int(1e18)
    best_start = 0
    curr, r = 0, 0
    for l in range(len(songs)):
        while r < l + len(songs) and curr < rem:
            curr += doubled[r]
            r += 1
        if curr >= rem:
            if r - l < best_length:
                best_length = r - l
                best_start = l
        curr -= doubled[l]
    total_songs = cycles * len(songs) + best_length
    return best_start, total_songs


def main():
    n, m = map(int, input().split())
    songs = list(map(int, input().split()))
    start, total_songs = solve(songs, m)
    print(start + 1, total_songs)


if __name__ == "__main__":
    main()
