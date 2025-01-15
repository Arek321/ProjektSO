#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>                         
#include <stdio.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <time.h>

int main(){




    //tutaj jakieś essential rzeczy które dziekan musi zrobić i potem:

    //generalnie można zrobić coś takiego i zapętlić ten program


    // Dziekan sprawdza, czy ogłosić ewakuację
    //while (1) {
        // Losowanie, czy ogłosić ewakuację (1% szansy)
   //     if (rand() % PROBABILITY_THRESHOLD == 0) {
    //        oglos_ewakuacje();  // Ogłasza ewakuację
   //     }
        
        // Dziekan czeka losową ilość czasu przed kolejną próbą
    //    sleep(rand() % 5 + 5);  // Czas oczekiwania od 5 do 10 sekund
  //  }
    // i w tym jeszcze np. jakiś sygnał który coś tam robi

    //spytac się Dr. Wojtasa czy może to być np. jeden wątek który robi tą pętle z ewakuacją 

    return 0;
}