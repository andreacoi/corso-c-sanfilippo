#include <stdio.h>
#include <stdlib.h>

// in questa versione del programma scrivo una variante dell'allocazione con malloc.
// Invece di allocare malloc() nella main, lo vado a chiamare direttamente nella funzione di creazione della frazione.

// funzione per creare una frazione utilizzando malloc.
// se malloc fallisce ritorna un puntatore NULL altrimenti ritorna la frazione stessa.
int *create_fraction(int num, int den) {
	int *f = malloc(sizeof(int)*2);
	// conviene sempre, ad ogni invocazione della malloc, controllare se la memoria è stata allocata correttamente
	if (f == NULL) return NULL; // se la malloc fallisce ci troviamo davanti a un errore di allocazione.
	f[0] = num;
	f[1] = den;
	return f;
}

// funzione che, dato un puntatore, stampa la frazione contenuta nel puntatore:
// - numeratore contenuto nella "prima parte" del puntatore
// - denominatore contenuto nella "seconda parte" del puntatore
void print_fraction(int *f) {
	printf("%d/%d\n", f[0], f[1]);
}
// funzione per eseguire la semplificazione di una data funzione passata negli argomenti.
void simplify_fraction(int *f) {
// il concetto chiave della semplificazione di un numero è l'iterazione delle divisioni che portino a resto 0.
	for (int d = 2; d <= f[0] && d <= f[1]; d++) {
		while (f[0] % d == 0  && f[1] % d == 0) {
			f[0] /= d;
			f[1] /= d;
		}
	}
}

int main(void) {
	int *f1 = create_fraction(10,20);	
	// a questo punto voglio chiamare la funzione per semplificare una funzione
	simplify_fraction(f1);
	print_fraction(f1);
	return 0;
}
