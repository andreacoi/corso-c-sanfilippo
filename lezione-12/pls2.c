#include <stdio.h>
/* Utilizzo di malloc() 
 * malloc() è una funzione per allocare della memoria general purpose.
 * malloc ritorna sempre un puntatore di tipo void
 * I puntatori di tipo void
 * Un puntatore di tipo void è un puntatore che non è legato specificatamente al alcun tipo di dato da allocare al proprio interno.
 * Gli argomenti della funzione malloc
 * L'unico argomento della funzione malloc è una variabile di tipo size_t che specifica lo spazio da allocare all`interno del quale collocare le variabili.
 * La funzione malloc è contenuta all'interno della libreria stdlib.h.
 */
#include <stdlib.h>

/* Questa funzione ritorna un puntatore a char che tiene conto della lunghezza
 * dei byte allocati specificati in len. 
 *
 */   
char *ps_create(char *init, int len) {
	char *s = malloc(1 + len + 1);
	unsigned char *lenptr = (unsigned char *)s; 
	*lenptr = len;
	for (int j = 0; j < len; j++) {
		s[j+1] = init[j];
	}
	s[len+1] = 0;
	return s;
}

void ps_print(char *s) {
	unsigned char *lenptr = (unsigned char *)s;
	for (int j = 0; j < *lenptr; j++) {
		putchar(s[j+1]);
	}
	printf("\n");
}

int main(void) {
	// partendo con le premesse presenti nel file pls.c
	// dobbiamo riscrivere il file utilizzando funzioni più dinamiche
	// Intanto ps_init diventa ps_create e cambia anche signature.
	// ps_create("Hello World", 11);
       	// Come si può vedere non passo più il buffer alla funzione.
	// E il valore di ritorno di questa funzione lo associo a un puntatore.	
	char *mystring = ps_create("Hello World", 11);
	ps_print(mystring);

	return 0; 
}
