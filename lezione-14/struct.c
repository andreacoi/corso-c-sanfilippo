#include <stdio.h>
#include <stdlib.h>

// supponiamo di voler scrivere un programma per gestire delle frazioni.

// scrivo la funzione set_fraction per creare delle funzioni:
void set_fraction(int *f, int num, int den) {
	f[0] = num;
	f[1] = den;
}
// funzione per stampare le frazioni
void print_fraction(int *f) {
	printf("%d/%d\n", f[0], f[1]);
}
int main(void) {
	// utilizzando malloc() (inclusa in stdlib.h) vado ad allocare lo spazio di 8bit per la mia frazione
	int *f = malloc(sizeof(int)*2);
	/* 
	 * Chiarimento ancora sui puntatori
	 * Dichiarando un puntatore a un int *f, il puntatore è formato in questo modo:
	 * |1111|2222|
	 * f[0]  f[1] 
	 * e posso accedervi comportandomi come se si trattasse di un array.
	 * 
	 */
	// a questo punto chiamo una funzione set_fraction per creare una frazione che vale 1/2.
	set_fraction(f, 1,2);
	print_fraction(f);
	return 0; 
}
