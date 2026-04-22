import sys


def solve(items_count_a, items_count_b, capacity, weight_a, weight_b, costs_a, costs_b):
    costs_a.sort(reverse=True)
    costs_b.sort(reverse=True)

    prefix_a = [0] * (items_count_a + 1)
    for i in range(items_count_a):
        prefix_a[i + 1] = prefix_a[i] + costs_a[i]

    prefix_b = [0] * (items_count_b + 1)
    for i in range(items_count_b):
        prefix_b[i + 1] = prefix_b[i] + costs_b[i]

    best_value = 0

    for taken_a in range(items_count_a + 1):
        used_capacity = taken_a * weight_a
        if used_capacity > capacity:
            break

        remaining = capacity - used_capacity
        max_taken_b = remaining // weight_b
        taken_b = min(max_taken_b, items_count_b)

        current_value = prefix_a[taken_a] + prefix_b[taken_b]
        if current_value > best_value:
            best_value = current_value

    return best_value


def main():
    data = sys.stdin.read().split()
    ptr = 0
    n = int(data[ptr])
    ptr += 1
    m = int(data[ptr])
    ptr += 1
    s = int(data[ptr])
    ptr += 1
    A = int(data[ptr])
    ptr += 1
    B = int(data[ptr])
    ptr += 1

    a = [int(data[ptr + i]) for i in range(n)]
    ptr += n
    b = [int(data[ptr + i]) for i in range(m)]

    print(solve(n, m, s, A, B, a, b))


if __name__ == '__main__':
    main()
