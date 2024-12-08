# Philosophers
42 Philosophers project

PER CONTROLLARE USA:
valgrind --tool=helgrind

https://nafuka11.github.io/philosophers-visualizer/

per non far morire filosofi, se sono dispari il tempo per morire deve essere maggiore di somma di tempo per mangiare e tempo per dormire.
Se sono pari puo' essere di meno.

============ TO DO ==========

- filosofi pari prendono forchette invertite se totale filosofi pari, altrimenti le prendono tutti allo stesso modo.

- fai test per vedere se codice funziona

- rimuovi commenti

- dividi codice in piu' funzioni

- cambia nome alcune variabili (forchetta destra e sinistra -> prima e seconda forchetta)

=========== BUGS ===========

- cambia controllo limiti input filosofi e forse ache tempi

--------- RISOLTI 

- stampa messaggi dopo morte
	risolto: dovevo mettere piu' controlli sul mutex stop durante le azioni dei filosofi

- errore failed to destroy forks stampato due volte
	risolto: non serviva proprio distruggere i mutex, dato che li ho allocati con malloc

- philo 3 muore e non dovrebbe
	risolto: era la presa forchette diversa per ultimo philo dispari

- programma non si ferma dopo morte
	risolto: causato da mutex rimasti bloccati



02/12/2024
parlando con Bard, ho scoperto che serve mettere un mutex ad ogni variabile a cui accedono piu' thread,
 a prescindere da cosa ci facciano.
Quindi, anche il timestamp di avvio al programma

----------------------
Conversione tempi vari da millisecondi a microsecondi?
	perchè usleep usa i microsecondi, mentre l'input del programa philo 
	è in millisecondi

Guarda tutorial per implementazione

domanda:
- se metto il parametro delle volte in cui i filosofi devono mangiare, la simulazione termina quanto tutti hanno mangiato X volte.
Quindi, quando l'ultimo filosofo che ha iniziato a mangiare ha mangiato l'ultima volta.
Se questo filosofo ha iniziato al tempo 406, e il tempo per mangiare e' 200, e li faccio mangiare una volta ciascuno, la simulazione deve terminare al tempo 406 o al 606?

risposta (Sasha):
- Da quel che ricordo, il tempo dell'ultimo pasto di un filosofo equivale all'inizio dell'ultimo pasto, ma questo si deve segnare come completato (incrementare la variabile di quante volte uno ha mangiato) solo dopo aver aspettato il time to eat perché il filosofo potrebbe morire mentre sta mangiando.


-------------

0 1 is thinking
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 5 is thinking
0 5 has taken a fork
0 5 has taken a fork
0 6 is thinking
0 2 is thinking
0 2 has taken a fork
0 3 is thinking
0 3 has taken a fork
0 6 has taken a fork
0 4 is thinking
0 7 is thinking
1 5 is eating
200 1 is sleeping
200 7 has taken a fork
200 2 has taken a fork
200 2 is eating
201 5 is sleeping
201 4 has taken a fork
201 6 has taken a fork
201 6 is eating
400 1 is thinking
400 2 is sleeping
400 1 has taken a fork
400 3 has taken a fork
400 3 is eating
401 5 is thinking
401 6 is sleeping
401 7 has taken a fork
401 7 is eating
401 5 has taken a fork
600 2 is thinking
600 3 is sleeping
600 2 has taken a fork
600 4 has taken a fork
600 4 is eating
601 6 is thinking
601 7 is sleeping
601 1 has taken a fork
601 1 is eating
601 6 has taken a fork
801 5 died