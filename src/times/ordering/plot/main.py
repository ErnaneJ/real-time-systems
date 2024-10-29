import pandas as pd
import matplotlib.pyplot as plt

CSV_FILE = '/Users/ernane/me/real-time-systems/src/ordering/plot/data/sorting_times.csv'
if __name__ == '__main__':
  data = pd.read_csv(CSV_FILE)
  
  plt.figure(num='Comparison of Sorting Times (QSort vs BubbleSort)', figsize=(10, 6))
  
  plt.plot(data['Array Size'], data['QSort Time (ms)'], label='QSort Time (ms)', marker='o')
  plt.plot(data['Array Size'], data['Bubble Sort Time (ms)'], label='Bubble Sort Time (ms)', marker='o')
  
  plt.title('Comparison of Sorting Times (QSort vs BubbleSort)')
  plt.xlabel('Array Size')
  plt.ylabel('Time (ms)')
  
  plt.legend()
  
  plt.grid(True)
  plt.show()
