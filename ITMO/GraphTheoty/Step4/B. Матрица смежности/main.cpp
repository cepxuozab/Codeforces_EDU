#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        std::vector<int> degree(n, 0);

        // Чтение матрицы и подсчёт степеней
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> matrix[i][j];
                degree[i] += matrix[i][j];
            }
        }

        bool is_graph = true;

        // Проверка: симметричность + нулевая диагональ
        for (int i = 0; i < n && is_graph; ++i) {
            if (matrix[i][i] != 0) { // проверка диагонали
                is_graph = false;
                break;
            }
            for (int j = i + 1; j < n; ++j) { // достаточно проверить верхний треугольник
                if (matrix[i][j] != matrix[j][i]) {
                    is_graph = false;
                    break;
                }
            }
        }

        if (!is_graph) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
            for (int i = 0; i < n; ++i) {
                if (i > 0)
                    std::cout << ' ';
                std::cout << degree[i];
            }
            std::cout << '\n';
        }
    }

    return 0;
}
