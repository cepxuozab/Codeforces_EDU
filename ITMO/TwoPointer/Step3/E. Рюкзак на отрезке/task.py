def backpack_in_segment(weights: list[int], costs: list[int], max_weight: int) -> int:
    max_cost, curr_cost, curr_weight = 0, 0, 0
    left = 0
    for right in range(len(weights)):
        curr_weight += weights[right]
        curr_cost += costs[right]
        while curr_weight > max_weight:
            curr_weight -= weights[left]
            curr_cost -= costs[left]
            left += 1
        if curr_cost > max_cost:
            max_cost = curr_cost
    return max_cost


def main():
    _, max_weight = map(int, input().split())
    weights = list(map(int, input().split()))
    costs = list(map(int, input().split()))
    print(backpack_in_segment(weights, costs, max_weight))


if __name__ == "__main__":
    main()
