#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>

const char* digits[10][4] = {
  {" _ ", "| |", "|_|", " "}, // 0
  {"   ", "  |", "  |", " "}, // 1
  {" _ ", " _|", "|_ ", " "}, // 2
  {" _ ", " _|", " _|", " "}, // 3
  {"   ", "|_|", "  |", " "}, // 4
  {" _ ", "|_ ", " _|", " "}, // 5
  {" _ ", "|_ ", "|_|", " "}, // 6
  {" _ ", "  |", "  |", " "}, // 7
  {" _ ", "|_|", "|_|", " "}, // 8
  {" _ ", "|_|", " _|", " "}, // 9
};

const char* colon[4] = { "   ", " . ", " . ", "   "};

void displayTime(int hour, int min, int sec) 
{
  int timeDigits[6] = { hour / 10, hour % 10, min / 10, min % 10, sec / 10, sec % 10 };

  std::cout << "┌─────────────────────────────────┐\n";
  for (int line = 0; line < 4; ++line) {
    std::cout << "│ ";
    for (int i = 0; i < 6; ++i) {
      if (i == 2 || i == 4)
        std::cout << colon[line] << " ";

      std::cout << digits[timeDigits[i]][line] << " ";
    }
    if(line == 3)
      std::cout << "\t\t  ";
    std::cout << "│ " << std::endl;
  }
  std::cout << "├─────────────────────────────────┤\n";
};

int main() 
{
  while (true) {
    time_t tempo_valor;
    time(&tempo_valor);
    struct tm *tm_ptr = gmtime(&tempo_valor);

    // std::cout << "\033[2J\033[1;1H"; // ANSI escape to clear the screen and move the cursor to the beginning
    system("clear");

    displayTime(tm_ptr->tm_hour, tm_ptr->tm_min, tm_ptr->tm_sec);
    std::cout << "│ \t   "<< tm_ptr->tm_mday << "/" 
        << tm_ptr->tm_mon + 1 << "/" 
        << tm_ptr->tm_year + 1900 << " BR \t  │\n";
    std::cout << "└─────────────────────────────────┘\n";

    std::cout << "\nPress Ctrl+C to exit..\n";

    sleep(1);
  }
  return 0;
};