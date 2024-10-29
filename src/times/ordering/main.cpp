#include <cstdlib> 
#include <ctime>   
#include <cstdio>  
#include <iostream>
#include <fstream>

int *quickSortArray;
int *bubbleSortArray;
int arraySize;

int compareInts(const void* a, const void* b)
{
  const int* arg1 = static_cast<const int*>(a);
  const int* arg2 = static_cast<const int*>(b);
  return (*arg1 > *arg2) - (*arg1 < *arg2);
}

void bubbleSort(int *array, int size)
{
  int temp;
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1 - i; j++) {
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void createArray(int arraySize, int seed)
{
  srand(seed);
  quickSortArray = new int[arraySize];
  bubbleSortArray = new int[arraySize];
  for (int i = 0; i < arraySize; i++) {
    quickSortArray[i] = rand() % 100000;
    bubbleSortArray[i] = quickSortArray[i];
  }
}

void saveToCSV(const std::string &filename, const std::string &data)
{
  std::ofstream file;
  file.open(filename, std::ios::app);
  file << data << std::endl;
  file.close();
}

void clearFile(const std::string &filename)
{
  std::ofstream file;
  file.open(filename, std::ios::trunc);
  file.close();
}

int main() {
  const int sizes[] = {20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
  const int numSizes = sizeof(sizes) / sizeof(sizes[0]);
  std::string filename = "/Users/ernane/me/real-time-systems/src/ordering/plot/data/sorting_times.csv";

  clearFile(filename);
  saveToCSV(filename, "Array Size,QSort Time (ms),Bubble Sort Time (ms)");

  for (int i = 0; i < numSizes; ++i) {
    int n = sizes[i];
    createArray(n, 23);

    clock_t start = clock();
    qsort(quickSortArray, n, sizeof(int), compareInts);
    clock_t end = clock();
    double qsortTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    start = clock();
    bubbleSort(bubbleSortArray, n);
    end = clock();
    double bubbleSortTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    std::string data = std::to_string(n) + "," + std::to_string(qsortTime) + "," + std::to_string(bubbleSortTime);
    saveToCSV(filename, data);

    delete[] quickSortArray;
    delete[] bubbleSortArray;

    std::cout << "Sorting completed for array size " << n << "." << std::endl;
  }

  std::cout << "Sorting completed and times saved to " << filename << "." << std::endl;

  std::cout << "Plot chart with python" << std::endl;
  system("pwd");
  system("cd $(pwd)/../plot && source venv/bin/activate && pip install -r requirements.txt && python main.py");

  return 0;
}
