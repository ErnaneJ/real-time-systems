import os
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv(os.path.join(os.path.dirname(__file__), '../results.csv'), sep=',', header=0)

data.columns = data.columns.str.strip()

data['bufferSize'] = data['bufferSize'].astype(float)
data['time_us'] = data['time_us'].astype(float) / 10000000000.0

n_plots = 6  
rows, cols = 2, 3  
fig, axs = plt.subplots(rows, cols, figsize=(15, 8), constrained_layout=True)

index_ranges = [
  (0, 10), (10, 20),
  (20, 30), (30, 40),
  (40, 50), (50, len(data))
]

for ax, (start, end) in zip(axs.ravel(), index_ranges):
  ax.plot(data[start:end]['bufferSize'], data[start:end]['time_us'], marker='o')
  ax.set_title(f'Gráfico {start}-{end}', fontsize=12)
  ax.set_xlabel('Tamanho do Buffer (bytes)', fontsize=10)
  ax.set_ylabel('Tempo (us)', fontsize=10)
  ax.grid()

for ax in axs.flat:
  ax.label_outer()  

plt.suptitle('Relação entre Tamanho do Buffer e Tempo de Resposta', fontsize=16)

plt.show()