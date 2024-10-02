#include <iostream>
#include <ctime>

struct Birthday
{
  int day; int month; int year;
};

int main()
{
  Birthday userBirthday;

  std::cout << "Please enter the day of your birthday: ";
  std::cin >> userBirthday.day;
  std::cout << "Please enter the month of your birthday: ";
  std::cin >> userBirthday.month;
  std::cout << "Please enter the year of your birthday: ";
  std::cin >> userBirthday.year;

  std::cout << std::endl << "Your birthday is: " 
        << userBirthday.day << "/" 
        << userBirthday.month << "/" 
        << userBirthday.year << "\n";

  time_t currentTime;
  time(&currentTime);

  struct tm birthdayTime = {0};
  birthdayTime.tm_mday = userBirthday.day;
  birthdayTime.tm_mon = userBirthday.month - 1; 
  birthdayTime.tm_year = userBirthday.year - 1900; 
  birthdayTime.tm_hour = 0;
  birthdayTime.tm_min = 0;
  birthdayTime.tm_sec = 0;

  time_t birthdayTimestamp = mktime(&birthdayTime);
  
  if (birthdayTimestamp == -1) {
    std::cout << "Error calculating the birth date.\n";
    return 1;
  }
  
  double secondsDiff = difftime(currentTime, birthdayTimestamp);
  
  std::cout << std::endl << "You have lived approximately " 
        << secondsDiff << " seconds since your birth.\n";
  std::cout << "That is equivalent to approximately " 
        << secondsDiff / 60 / 60 / 24 / 365 << " years.\n";

  return 0;
};