def common_length(arr: list[int], max_sum: int) -> int:
    curr_sum, total, left = 0, 0, 0
    for right in range(len(arr)):
        curr_sum += arr[right]
        while curr_sum > max_sum:
            curr_sum -= arr[left]
            left += 1
        k = right - left + 1
        total += (k * (k+1))//2
    return total


def main():
    _, max_sum = map(int, input().split())
    arr = list(map(int, input().split()))
    print(common_length(arr, max_sum))


if __name__ == "__main__":
    main()

