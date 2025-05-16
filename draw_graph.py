import matplotlib.pyplot as plt

# with open('stats_1.txt', 'r') as file:
#     data = {}
#     for line in file:
#         size, time = line.strip().split(': ')
#         data[int(size)] = float(time)

with open('stats_2.txt', 'r') as file:
    data_omp = {}
    for line in file:
        size, time = line.strip().split(': ')
        data_omp[int(size)] = float(time)

with open('stats_3(4).txt', 'r') as file:
    data_mpi_4 = {}
    for line in file:
        size, time = line.strip().split(': ')
        data_mpi_4[int(size)] = float(time)

with open('stats_3(8).txt', 'r') as file:
    data_mpi_8 = {}
    for line in file:
        size, time = line.strip().split(': ')
        data_mpi_8[int(size)] = float(time)

with open('stats_3(10).txt', 'r') as file:
    data_mpi_10 = {}
    for line in file:
        size, time = line.strip().split(': ')
        data_mpi_10[int(size)] = float(time)

with open('stats_3(12).txt', 'r') as file:
    data_mpi_12 = {}
    for line in file:
        size, time = line.strip().split(': ')
        data_mpi_12[int(size)] = float(time)

# sizes = sorted(set(data.keys()))
# sizes = sorted(set(data.keys()) | set(data_omp.keys()))
sizes = sorted(set(data_omp.keys()) | set(data_mpi_4.keys()) | set(data_mpi_8.keys()) | set(data_mpi_10.keys())
               | set(data_mpi_12.keys()))
#times = [data[size] for size in sizes]
times_omp = [data_omp[size] for size in sizes]
times_mpi_4 = [data_mpi_4[size] for size in sizes]
times_mpi_8 = [data_mpi_8[size] for size in sizes]
times_mpi_10 = [data_mpi_10[size] for size in sizes]
times_mpi_12 = [data_mpi_12[size] for size in sizes]

plt.figure(figsize=(10, 6))
plt.plot(sizes, times_omp, color="red", label="Время с OpenMP")
plt.plot(sizes, times_mpi_4, color="blue", label="Время c MPI (4 потока)")
plt.plot(sizes, times_mpi_8, color="green", label="Время c MPI (8 потоков)")
plt.plot(sizes, times_mpi_10, color="brown", label="Время c MPI (10 потоков)")
plt.plot(sizes, times_mpi_12, color="cyan", label="Время c MPI (12 потоков)")
plt.xlabel('Размер')
plt.ylabel('Время, мс')
plt.title('Зависимость времени от размера')
plt.grid(True)
plt.legend()
plt.savefig('./data/graphic_3.png')