#include <iostream>
#include <chrono>
#include "gen_matrix.h"

using namespace std;
using namespace std::chrono;

int main() {
    int rows1, cols1, rows2, cols2;
    cout << "Enter the dimensions of the first matrix (rows columns): ";
    cin >> rows1 >> cols1;
    cout << "Enter the dimensions of the second matrix (rows columns): ";
    cin >> rows2 >> cols2;

    if (cols1 != rows2) {
        cout << "Error: The number of columns in the first matrix must be equal to the number of rows in the second matrix.\n";
        return 1;
    }

    auto matrix1 = random_matrix::generate_matrix(rows1, cols1);
    auto matrix2 = random_matrix::generate_matrix(rows2, cols2);

    random_matrix::save_matrix_to_file(matrix1, "matrix1.txt");
    random_matrix::save_matrix_to_file(matrix2, "matrix2.txt");

    cout << "Matrices saved to files matrix1.txt and matrix2.txt\n";

    int resultRows = rows1;
    int resultCols = cols2;

    // Умножение матриц
    auto start = high_resolution_clock::now();
    vector<vector<int>> result(resultRows, vector<int>(resultCols, 0));
    for (int i = 0; i < resultRows; i++) {
        for (int j = 0; j < resultCols; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    auto end = high_resolution_clock::now();

    // Запись результата в файл
    ofstream outputFile("result.txt");
    outputFile << resultRows << " " << resultCols << "\n";
    for (int i = 0; i < resultRows; i++) {
        for (int j = 0; j < resultCols; j++) {
            outputFile << result[i][j] << " ";
        }
        outputFile << "\n";
    }
    outputFile.close();

    // Вывод информации
    auto duration = duration_cast<microseconds>(end - start).count();
    int taskSize = rows1 * cols1 + rows2 * cols2 + resultRows * resultCols;
    cout << "Execution time: " << duration << " microseconds\n";
    cout << "Task size: " << taskSize << " elements\n";

    // Верификация результата с помощью Python
    system("python verify_result.py");

    return 0;
}