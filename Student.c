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

#define K 5                 // ilość kierunków na wydziale X
#define MAX_STUDENTOW 800   // maksymalna ilość studentów 2 roku (160*5)

typedef struct {            // struktura reprezentująca każdego studenta
    int id;   
    pid_t pid_studenta;     // identyfikator kazdego studenta
    int Kierunek;
    int powtarza_egzamin;   // flaga, jeśli student powtarza egzamin (1 - tak,0 - nie)
    int zaliczona_praktyka; // flaga, czy czesc praktyczna zostala zaliczona
    float ocena_praktyka;
    float ocena_teoria;
}Student;

float losuj_ocene_pozytywna() {
    int rand_value = rand() % 5;  
    float oceny[] = {3.0, 3.5, 4.0, 4.5, 5.0};  
    float ost = oceny[rand_value];
    return ost; 
}

int losuj_ilosc_studentow() {
    return (rand() % (160 - 80 + 1)) + 80; // losuje liczbe studentów w zakresie 80<=Ni<=160
}

void proces_studenta(int student_id, int kierunek, int powtarzaEgzamin) {
    Student student;
    student.id = student_id;
    student.pid_studenta = getpid();
    student.Kierunek = kierunek;
    student.powtarza_egzamin = powtarzaEgzamin;
    if(powtarzaEgzamin == 1){
        student.zaliczona_praktyka = 1;
        student.ocena_praktyka = losuj_ocene_pozytywna();
    }else{
        student.zaliczona_praktyka = 0;
        student.ocena_praktyka= 0.0;
    }

    student.ocena_teoria =0.0;

    // Symulacja zachowania studenta (np. oczekiwanie w kolejce)
    sleep(rand() % 3 + 1); // Losowy czas działania procesu

    // Student kończy działanie
    printf("Student ID: %d zakończył działanie (PID: %d).\n", student_id, getpid());
    exit(0);
}

int main()
{
    srand(time(NULL));
    int lsKierunek_1 = losuj_ilosc_studentow(); //losuje ilości studentów na poszczególnych kierunkach
    int lsKierunek_2 = losuj_ilosc_studentow();
    int lsKierunek_3 = losuj_ilosc_studentow();
    int lsKierunek_4 = losuj_ilosc_studentow();
    int lsKierunek_5 = losuj_ilosc_studentow();
    int liczba_studentow = lsKierunek_1 + lsKierunek_2 + lsKierunek_3 + lsKierunek_4 + lsKierunek_5;

    if (liczba_studentow > MAX_STUDENTOW)
    {
        printf("Przekroczona maksymalna liczba studentow\n");
        exit(EXIT_FAILURE);
    }

    int student_id = 1;
    for (int kierunek = 1; kierunek <= K; kierunek++) {
        int liczba_na_kierunku = (kierunek == 1) ? lsKierunek_1 :
                                 (kierunek == 2) ? lsKierunek_2 :
                                 (kierunek == 3) ? lsKierunek_3 :
                                 (kierunek == 4) ? lsKierunek_4 : lsKierunek_5;

        for (int i = 0; i < liczba_na_kierunku; i++) {
            int opoznienie = rand() % 6 +5; // studenci pojawiaja sie w losowych momentach czasu(5-10sek)
            sleep(opoznienie);


            int powtarzaEgzamin = rand() % 100 < 5 ? 1 : 0; // 5% studentów powtarza egzamin z zaliczoną praktyką

            pid_t pid = fork();
            if (pid < 0) {
                perror("Blad forka");
                return 1;
            } else if (pid == 0) {
                // Proces potomny (student)
                proces_studenta(student_id, kierunek, powtarzaEgzamin);
            } else {
                // Proces macierzysty
                student_id++;
            }
        }
    }
    



    while (wait(NULL) > 0); // czekam na zakończenie wszystkich procesów potomnych
    return 0;
}
