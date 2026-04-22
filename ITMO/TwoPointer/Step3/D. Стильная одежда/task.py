import sys


def read_input():
    """Читает входные данные."""
    clothes = []
    for _ in range(4):
        n = int(sys.stdin.readline())
        values = list(map(int, sys.stdin.readline().split()))
        clothes.append(values)
    return clothes


def find_min_range(clothes):
    """
    Находит минимальный диапазон цветов,
    содержащий хотя бы один элемент каждого типа.
    """
    # Собираем все элементы в один список: (цвет, тип)
    all_items = []
    for item_type, values in enumerate(clothes):
        all_items.extend((value, item_type) for value in values)

    # Сортируем по цвету
    all_items.sort(key=lambda x: x[0])

    # Скользящее окно
    count_by_type = [0] * 4
    covered_types = 0

    left = 0
    best_range = float('inf')
    best_window = (0, -1)

    for right, (color, item_type) in enumerate(all_items):
        if count_by_type[item_type] == 0:
            covered_types += 1
        count_by_type[item_type] += 1

        # Пытаемся сузить окно
        while covered_types == 4:
            left_color, left_type = all_items[left]
            current_range = color - left_color

            if current_range < best_range:
                best_range = current_range
                best_window = (left, right)

            # Сдвигаем левую границу
            count_by_type[left_type] -= 1
            if count_by_type[left_type] == 0:
                covered_types -= 1

            left += 1

    return all_items, best_window


def extract_result(all_items, window):
    """Восстанавливает ответ из найденного окна."""
    left, right = window
    result = [-1] * 4

    for i in range(left, right + 1):
        color, item_type = all_items[i]
        if result[item_type] == -1:
            result[item_type] = color

    return result


def main():
    clothes = read_input()
    all_items, best_window = find_min_range(clothes)
    result = extract_result(all_items, best_window)

    print(*result)


if __name__ == "__main__":
    main()
