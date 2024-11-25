#include "philo.h"

#define NUM_THREADS 3  // Numero di thread

void* thread_function(void* arg) {
    int id = *(int*)arg;  // Ottieni l'ID del thread

    // Stampa messaggi per identificare il thread
    printf(YELLOW "Thread %d: Inizio lavoro\n" NO_COLOR, id);
    usleep(100000 * id);  // Simula lavoro con una pausa (tempo variabile per ciascun thread)
    printf(BLUE "Thread %d: Fine lavoro\n" NO_COLOR, id);

    return NULL;  // Termina il thread
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Creazione dei thread
    int i = 0;
    while (i < NUM_THREADS) {
        thread_ids[i] = i;  // Assegna un ID unico a ciascun thread
        printf(GREEN "Main: Creazione del thread %d\n" NO_COLOR, i);
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        i++;
    }

    // Aspetta che tutti i thread terminino
    i = 0;
    while (i < NUM_THREADS) {
        pthread_join(threads[i], NULL);
        printf(RED "Main: Thread %d terminato\n" NO_COLOR, i);
        i++;
    }

    printf(MAGENTA "Main: Tutti i thread hanno terminato\n" NO_COLOR);

    return 0;
}
