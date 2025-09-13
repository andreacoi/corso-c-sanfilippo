#include <stdio.h>

// la funzione conta vista durante la lezione 6 è diventata conta_vanilla e può essere ottimizzata utilizzando il goto.

void conta_vanilla(int start, int end) {
	if (start > end) return;
	printf("%d\n", start);
	conta_vanilla(start + 1, end);
}

// creo la nuova funzione conta
void conta(int start, int end) {
// inserisco l'etichetta iterate, necessaria per implementare il goto
iterate:
	if (start > end) return;
	printf("%d: %p\n", start, &start);
	start = start + 1;
	goto iterate;
	// questo tipo di costrutto si chiama tail call optimization perché costituisce un ottimizzazione rispetto al chiamare una funzione più volte allocando ogni volta lo stack frame.
	// si vede il vantaggio SOPRATTUTTO stampando gli indirizzi di memoria allocata dalla variabile start. Come si può notare l'indirizzo rimane il medesimo, portando ad un notevole risparmio di memoria.
}

int main(void) {
	conta(0, 9);
	return 0;
}
