# Philosophers
42 Philosophers project

PER CONTROLLARE USA:
valgrind --tool=helgrind

============ TO DO ==========

- ./philo 5 800 200 200 c'e' un ritardo di 1ms che si accumula. Va bene?


- dividi codice in piu' funzioni

=========== BUGS ===========



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


