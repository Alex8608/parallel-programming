#include <iostream>
#include <chrono>
#include "gen_matrix.h"

using namespace std;
using namespace std::chrono;

int main(const int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const vector<int> dimension = {50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000};
    vector<double> times(dimension.size(), 0.0);

    for (size_t i = 0; i < dimension.size(); ++i) {
        auto dim = dimension[i];
        vector<vector<int>> matrix_1;
        vector<vector<int>> matrix_2;

        if (rank == 0) {
            matrix_1 = read_matrix_from_file("./data/matrix1_"+to_string(dim)+".txt");
            matrix_2 = read_matrix_from_file("./data/matrix2_"+to_string(dim)+".txt");
            for (int p = 1; p < size; p++) {
                MPI_Send(&dim, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
            }
            for (int p = 1; p < size; p++) {
                for (const auto& row : matrix_1) {
                    MPI_Send(row.data(), dim, MPI_INT, p, 1, MPI_COMM_WORLD);
                }
                for (const auto& row : matrix_2) {
                    MPI_Send(row.data(), dim, MPI_INT, p, 2, MPI_COMM_WORLD);
                }
            }
        }
        else {
            MPI_Recv(&dim, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            matrix_1.resize(dim, vector<int>(dim));
            matrix_2.resize(dim, vector<int>(dim));
            for (auto& row : matrix_1) {
                MPI_Recv(row.data(), dim, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            for (auto& row : matrix_2) {
                MPI_Recv(row.data(), dim, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
        auto start_time = chrono::steady_clock::now();
        vector<vector<int>> result = matrix_multiplication_mpi(matrix_1, matrix_2, rank, size);
        auto end_time = chrono::steady_clock::now();

        if (rank == 0) {
            save_matrix_to_file(result, "./data/result_mpi_" + to_string(dim) + ".txt");
            times[i] = chrono::duration<double, milli>(end_time - start_time).count();
        }
    }

    if (rank == 0) {
        ofstream out("stats_3(4).txt");
        for (size_t i = 0; i < dimension.size(); ++i) {
            out << dimension[i] << ": " << times[i] << "\n";
        }
    }

    MPI_Finalize();
    return 0;
}