import sys


def solve(items_count, target_sum, values):
    inf = 10 ** 18
    answer = inf

    prev = [inf] * (target_sum + 1)

    for idx in range(items_count):
        curr = [inf] * (target_sum + 1)
        if values[idx] <= target_sum:
            curr[values[idx]] = 1
        curr[0] = 0

        if idx > 0:
            for current_sum in range(target_sum + 1):
                if prev[current_sum] != inf:
                    curr[current_sum] = min(curr[current_sum], prev[current_sum] + 1)

                    new_sum = current_sum + values[idx]
                    if new_sum <= target_sum:
                        curr[new_sum] = min(curr[new_sum], prev[current_sum] + 1)

        answer = min(answer, curr[target_sum])
        prev = curr

    return -1 if answer == inf else answer


def main():
    data = sys.stdin.read().split()
    ptr = 0
    n = int(data[ptr])
    ptr += 1
    s = int(data[ptr])
    ptr += 1

    a = [int(data[ptr + i]) for i in range(n)]

    print(solve(n, s, a))


if __name__ == '__main__':
    main()