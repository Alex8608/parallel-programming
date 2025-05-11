import matplotlib.pyplot as plt

with open('stats_1.txt', 'r') as file:
    data = {}
    for line in file:
        size, time = line.strip().split(': ')
        data[int(size)] = float(time)

with open('stats_2.txt', 'r') as file:
    data_omp = {}
    for line in file:
        size, time = line.strip().split(': ')
        data_omp[int(size)] = float(time)

# sizes = sorted(set(data.keys()))
sizes = sorted(set(data.keys()) | set(data_omp.keys()))
times = [data[size] for size in sizes]
times_omp = [data_omp[size] for size in sizes]

plt.figure(figsize=(10, 6))
plt.plot(sizes, times, color="blue", label="Время без OpenMP")
plt.plot(sizes, times_omp, color="red", label="Время с OpenMP")
plt.xlabel('Размер')
plt.ylabel('Время, мс')
plt.title('Зависимость времени от размера')
plt.grid(True)
plt.legend()
plt.savefig('./data/graphic_2.png')