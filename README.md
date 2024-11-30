# Philosophers
42 Philosophers project

CANCELLA FILE PROVA.C

PER CONTROLLARE USA:
valgrind --tool=helgrind

✓✓✓ PARSING



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


