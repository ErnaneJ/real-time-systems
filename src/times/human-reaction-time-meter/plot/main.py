import pandas as pd
import matplotlib.pyplot as plt

FILE_PATH = '/Users/ernane/me/real-time-systems/src/human-reaction-time-meter/assets/game_results.txt'

def time_to_milliseconds(time_str):
  time_str = time_str.replace('h', '').replace('min', '').replace('ms', '').replace('s', '').strip()
  h, m, s, ms = map(int, time_str.split())
  return ((h * 3600) + (m * 60) + s) * 1000 + ms

if __name__ == '__main__':
  colunas = ['Attempt at', 'Total', 'Average', 'Correct answers']
  df = pd.read_csv(FILE_PATH, sep="|", skiprows=1, names=colunas)

  df = df.drop(0)
  df['Attempt at'] = pd.to_datetime(df['Attempt at'], format="%d/%m/%Y às %H:%M:%S ")

  df['Total'] = df['Total'].apply(time_to_milliseconds)
  df['Average'] = df['Average'].apply(time_to_milliseconds)
  df['Questions'] = df['Correct answers'].apply(lambda x: int(x.replace('/', ' ').split()[1]))
  df['Correct answers'] = df['Correct answers'].apply(lambda x: int(x.replace('/', ' ').split()[0]))

  titles = ['Total Time per Attempt', 'Average Time per Attempt', 'Correct Answers per Attempt']
  columns = ['Total', 'Average', 'Correct answers']
  colors = ['tab:red', 'tab:orange', 'tab:blue']

  for i in range(len(columns)):
    plt.figure(figsize=(8, 6), num=titles[i])  
    plt.plot(df['Attempt at'], df[columns[i]], color=colors[i], marker='o')  
    plt.title(titles[i])  
    plt.xlabel('Attempt Date and Time')  
    plt.ylabel(columns[i])  
    plt.xticks(df['Attempt at'], df['Attempt at'].dt.strftime('%d/%m/%Y %H:%M:%S'), rotation=45, ha="right")  
    plt.tight_layout()  
    plt.show()  