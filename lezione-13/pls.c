/* In questo file andrò a fare il refactoring di ps_create utilizzando l'allocazione con uint_32t.
 * Per utilizzare questo tipo di dato occorre includere stdint.h.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *ps_create(char *init, int len) {
	// iniziamo con l'aumetare il numero di byte dedicati all'allocazione da 1 a 4.
	char *s = malloc(4 + len + 1); // nella versione precedente era: 1 + len + 4
	uint32_t *lenptr = (uint32_t *)s; // nella precendente versione era unsigned char
	*lenptr = len;

	// mi sposto di 4 byte su s, per posizionarmi all'inizio della stringa 
	s += 4;
	for (int j = 0; j < len; j++) {
		s[j] = init[j];
	}
	s[len] = 0;
	// avendo incrementato precedentemente dovrei ritornare s-4. Ma se tornassi s
	// non avrei bisogno di effettuare alcuna conversione di stringa per rendere la stringa compliant con il C.
	return s;
}

void ps_print(char *s) {
	uint32_t *lenptr = (uint32_t *)(s - 4);
	for (int j = 0; j < *lenptr; j++) {
		putchar(s[j]);
	}
	printf("\n");
	
}

// costruisco una funzione custom per liberare la memoria allocata da malloc per la mia stringa
void ps_free(char *s) {
	free(s-4);
}

int main(void) {
	// effettuo le chiamate di funzione
	char *mystr = ps_create("Hello World", 11);
	ps_print(mystr);
	// sarebbe utile scrivere una funzione per gestire il tentativo di eseguire free su un puntatore già svuotato, cosiddetta dangling reference.
	// per fare ciò abbiamo bisogno di un reference counter. Il valore del reference counter potrebbe essere allocato con altri 4 byte, dopo i byte riservati a L.
	// È chiaro che un sistema del genere possa risultare farraginoso. 
	// Principio di funzionamento: quando aumento il numero di numero di puntatori a una determinata variabile il reference counter aumenta, viceversa, diminuisce. Quando arrivo al punto tale che
	// il reference counter è 0, lancio una sola volta il free. 
	// Questo si rende necessario perché lanciare free, su una porzione di memoria non allocata o precedentemente liberata crea un crash a livello di programma.
	// A questo punto, la logica del programma si va a complicare un bel po'. 
	// Per cui viene introdotto il concetto di struct. La struct definisce un nuovo tipo di dato.
	ps_free(mystr);
	return 0;
}
