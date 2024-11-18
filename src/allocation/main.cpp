// UFRN-CT-DCA
// Disciplina: Sistemas de Tempo Real
// Programa: alocar_cpu.cpp


#include  <time.h>
#include <iostream> // para: cout
#include <stdio.h>
#include <unistd.h>  // para: sleep()
#include <stdlib.h>
#include <math.h>

#include <sys/resource.h>

#define _GNU_SOURCE
#include <sched.h>   // para alocar CPU

//using std::cout;
using namespace std;



int main( ){

    // ---- Alocação de CPU  ---------
    cpu_set_t  mask;  // máscara para habilitação de CPUs
    CPU_ZERO(&mask);
    
    CPU_SET(0, &mask);    // alocar na CPU 0
    //CPU_SET(1, &mask);    // alocar na CPU 1
    //CPU_SET(2, &mask);    // alocar na CPU 2
    //CPU_SET(3, &mask);    // ...
    
    
    int result = sched_setaffinity(0, sizeof(mask), &mask);
    // O primeiro parâmetro é o PID do processo a ser alocar CPU
    // 0 --> Quando for o próprio processo.
    
    while(1); // loop infinito - uso intensivo de CPU
    
    exit(1);

}

