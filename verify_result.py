import numpy as np
list_of_trues = []
dimension = [50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000]
for dim in dimension:
    matrix1 = np.loadtxt(f"./data/matrix1_{dim}.txt")
    matrix2 = np.loadtxt(f"./data/matrix2_{dim}.txt")
    result = np.loadtxt(f"./data/result_{dim}.txt")
    list_of_trues.append(np.array_equal(result, np.dot(matrix1, matrix2)))
if all(list_of_trues):
    print("All matrices equal")
else:
    print("Some matrix not equal")