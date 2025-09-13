#include <stdio.h>

int main(void) {
	// supponiamo di voler stampare i valori da 1 a 10. Per fare questo utilizzerò il costrutto goto.
	// qui iniziamo ad utilizzare i loop
	// inizializzo la solita variabile i a 0:
	int i = 0;
	// questa è l'ETICHETTA che consente al costrutto goto di tornare all'istruzione "again" per eseguirla nuovamente come indicato nella struttura di controllo if:
	again:
		printf("%d\n", i);
		i++;
		if (i < 10) {
			goto again;
		}
	return 0;
}
// ovviamente questo programma può essere scritto come un ciclo while. Continuo nel file while.c
	
