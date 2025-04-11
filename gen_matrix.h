#pragma once

#include <vector>
#include <random>
#include <fstream>

namespace random_matrix {
    std::vector<std::vector<int>> generate_matrix(int rows, int cols, int min_value = 1, int max_value = 100) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min_value, max_value);

        std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = dis(gen);
            }
        }
        return matrix;
    }

    void save_matrix_to_file(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
        std::ofstream file(filename);
        file << matrix.size() << " " << matrix[0].size() << "\n";
        for (const auto& row : matrix) {
            for (int value : row) {
                file << value << " ";
            }
            file << "\n";
        }
        file.close();
    }
}
