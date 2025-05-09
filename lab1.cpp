#include <iostream>
#include <chrono>
#include "gen_matrix.h"

using namespace std;
using namespace std::chrono;


int main() {
    const vector<int> dimension= {50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000};
    vector<double> time(dimension.size(), 0.0);
    for (int i = 0; i < dimension.size(); i++) {
        const auto dim = dimension[i];

        save_matrix_to_file(generate_matrix(dim,dim), "./data/matrix1_"+to_string(dim)+".txt");
        save_matrix_to_file(generate_matrix(dim,dim), "./data/matrix2_"+to_string(dim)+".txt");

        auto start_time = steady_clock::now();
        vector<vector<int>> matrix_1 = read_matrix_from_file("./data/matrix1_"+to_string(dim)+".txt");
        vector<vector<int>> matrix_2 = read_matrix_from_file("./data/matrix2_"+to_string(dim)+".txt");
        vector<vector<int>> result = matrix_multiplication(matrix_1, matrix_2);
        save_matrix_to_file(result, "./data/result_" + to_string(dim) + ".txt");
        auto end_time = steady_clock::now();

        time[i] = duration<double, milli>(end_time - start_time).count();
    }
    ofstream out("stats_1.txt");
    for (size_t i = 0; i < dimension.size(); i++) {
        out << dimension[i] << ": " << (time[i]) << "\n";
    }

    return 0;
}