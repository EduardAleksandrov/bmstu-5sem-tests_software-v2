import matplotlib.pyplot as plt
import pandas as pd

# Чтение данных из CSV файла
data_two = pd.read_csv('../execution_times_two.csv')

# Построение графика
plt.figure(figsize=(10, 6))
plt.plot(data_two['Number'], data_two['Time'], label='Время выполнения', color='blue')
plt.title('Зависимость времени выполнения от проверяемого числа')

plt.xlabel('Проверяемое число')
plt.ylabel('Время выполнения (микросекунды)')
plt.grid()
plt.legend()
plt.tight_layout()

# Сохранение графика в файл
plt.savefig('execution_time_graph_two.png')

# Отображение графика
plt.show()