// il ciclo if

#include <stdio.h>

int main(void) {
	int i = 2;
	if (i > 3) {
		// blocco di codice da eseguire se, e solo se, la condizione espressa nelle parentesi tonde subito dopo la kw if è vera
		printf("i > 3\n");
	} else {
		printf("i <= 3\n");
	}
	// c gestisce le ESPRESSIONI, esattamente coem fa RUST. Tutto quello che è racchiuso tra parentesi graffe è un blocco del programma e ciascuna dichiarazione, variabile, struttura di controllo resta valida all'interno dell'espressione (nello SCOPE).
	// In gergo si chiama scopo lessicale. Es.
	{ 
		int k = 5;
		printf("k è uguale a: %d\n", k);
	}
	// provando a stampare k fuori dalle parentesi graffe otterrò un errore e il programma non verrà compilato
	// printf("k è uguale a: %d\n", k); <-- ERRORE! FUORI DALLO SCOPO LESSICALE
	return 0;
}
