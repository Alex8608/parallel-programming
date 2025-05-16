#pragma once

#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <C:/Program Files (x86)/Microsoft SDKs/MPI/Include/mpi.h>

inline MPI_Datatype MPI_MATRIX_TYPE;

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

inline std::vector<std::vector<int>> matrix_multiplication_mpi(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2, const int rank, const int size) {
    const int n = matrix1.size();
    std::vector<std::vector<int>> local_result(n, std::vector<int>(n, 0));
    std::vector<int> global_result(n * n, 0);

    const int rows_per_process = n / size;
    const int start_row = rank * rows_per_process;
    const int end_row = (rank == size - 1) ? n : start_row + rows_per_process;

    for (int i = start_row; i < end_row; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                local_result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    std::vector<int> partial_result(n * n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            partial_result[i * n + j] = local_result[i][j];


    MPI_Reduce(partial_result.data(), global_result.data(), n * n,
               MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    std::vector<std::vector<int>> result;
    if (rank == 0) {
        result.resize(n, std::vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result[i][j] = global_result[i * n + j];
    }

    return result;
}