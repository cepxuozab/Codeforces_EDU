def number_to_choose(distances: list[int], max_distance: int) -> int:
    size = len(distances)
    j, answer = 0, 0
    for i in range(size):
        while j < size and distances[j] - distances[i] <= max_distance:
            j += 1
        answer += size - j
    return answer


def main():
    _, max_distance = map(int, input().split())
    distances = list(map(int, input().split()))
    print(number_to_choose(distances=distances, max_distance=max_distance))


if __name__ == "__main__":
    main()
