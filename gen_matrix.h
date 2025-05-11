#pragma once

#include <vector>
#include <random>
#include <fstream>
#include <sstream>

inline std::vector<std::vector<int>> generate_matrix(const int rows, const int cols, const int min_value = 1, const int max_value = 100) {

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

inline void save_matrix_to_file(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& row : matrix) {
        for (const int value : row) {
            file << value << " ";
        }
        file << "\n";
    }
    file.close();
}

inline std::vector<std::vector<int>> read_matrix_from_file(const std::string& path) {
    std::ifstream in(path);
    std::vector<std::vector<int>> matrix;
    std::string line;
    while (getline(in, line)) {
        std::istringstream stream(line);
        std::vector<int> row;
        int value;
        while (stream >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    return matrix;
}

inline std::vector<std::vector<int>> matrix_multiplication(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    const size_t size = matrix1.size();
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

inline std::vector<std::vector<int>> matrix_multiplication_omp(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    const size_t size = matrix1.size();
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}