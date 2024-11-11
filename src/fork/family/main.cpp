#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

void printProcessInfo(const std::string &name, int age)
{
  if(age == 0){
    std::cout << name << " (PID: " << getpid() << ") - nasceu. 🍼" << std::endl;
  }else{
    std::cout << name << " (PID: " << getpid() << ") - fez " << age << " ano(s). 🥳" << std::endl;
  }
}

void netoProcess(const std::string &name, int idadeMorte)
{
  printProcessInfo(name, 0);
  sleep(1);
  for (int idade = 1; idade <= idadeMorte; idade++)
  {
    sleep(1); 
    printProcessInfo(name, idade);
  }
  std::cout << name << " (PID: " << getpid() << ") - morreu aos " << idadeMorte << " anos. 💀" << std::endl;
  exit(0);
}

void filhoProcess(const std::string &name, int idadeMorte, int idadeNetoNasce, int idadeNetoMorre)
{
  pid_t netoPid = -1;

  printProcessInfo(name, 0);
  sleep(1);
  for (int idade = 1; idade <= idadeMorte; idade++)
  {
    sleep(1); 
    printProcessInfo(name, idade);

    if (idade == idadeNetoNasce)
    {
      netoPid = fork();
      if (netoPid == 0)
      {
        netoProcess(" " + name + " [ Neto ]", idadeNetoMorre);
      }
    }
  }

  std::cout << name << " (PID: " << getpid() << ") - morreu aos " << idadeMorte << " anos. 💀" << std::endl;
  
  if (netoPid > 0)
  {
    waitpid(netoPid, nullptr, 0);
  }
  exit(0);
}

int main()
{
  pid_t filho1Pid = -1, filho2Pid = -1;

  printProcessInfo("↪ Pai", 0);
  for (int idade = 1; idade <= 60; idade++)
  { 
    sleep(1);
    printProcessInfo("↪ Pai", idade);
    
    if (idade == 14)
    {
      filho1Pid = fork();
      if (filho1Pid == 0)
      {
        filhoProcess(" ↪ Filho 1", 30, 12, 12); 
      }
    }

    if (idade == 16)
    {
      filho2Pid = fork();
      if (filho2Pid == 0)
      {
        filhoProcess(" ↪ Filho 2", 30, 14, 18); 
      }
    }
  }

  std::cout << "↪ Pai (PID: " << getpid() << ") - morreu aos 60 anos. 💀" << std::endl;
  
  if (filho1Pid > 0)
  {
    waitpid(filho1Pid, nullptr, 0);
  }
  if (filho2Pid > 0)
  {
    waitpid(filho2Pid, nullptr, 0);
  }

  return 0;
}
