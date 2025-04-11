import numpy as np

with open("result.txt") as f:
    rows, cols = [int(x) for x in f.readline().split()]
    result = np.array([
        [int(x) for x in f.readline().split()]
        for _ in range(rows)
    ])

matrix1 = np.loadtxt("matrix1.txt", skiprows=1)
matrix2 = np.loadtxt("matrix2.txt", skiprows=1)

expected_result = np.matmul(matrix1, matrix2)

if np.array_equal(result, expected_result):
    print("Correct")
else:
    print("Incorrect")