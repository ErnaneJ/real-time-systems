import os
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv(os.path.join(os.path.dirname(__file__), '../results.csv'), sep=',', header=0)

data.columns = data.columns.str.strip()

data['bufferSize'] = data['bufferSize'].astype(float)
data['time_us'] = data['time_us'].astype(float)

print(data[['bufferSize', 'time_us']])

plt.plot(data['bufferSize'], data['time_us'], marker='o')
plt.title(f'Gráfico', fontsize=12)
plt.xlabel('Tamanho do Buffer (bytes)', fontsize=10)
plt.ylabel('Tempo (us)', fontsize=10)
plt.grid()

plt.suptitle('Relação entre Tamanho do Buffer e Tempo de Resposta', fontsize=16)

timestamp = pd.Timestamp.now()
plt.savefig(f'../plot/plot-{timestamp}.png')

plt.show()