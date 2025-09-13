#include <stdio.h>

void incr(int *p) {
	// funzione che incrementa il valore di p accedendo a p per riferimento (o tramite il suo indirizzo di memoria
	*p = *p + 1;
	// questa espressione può anche essere scritta come p[0] = p[0] + 1.
	// queste operazioni sono definite come DEFERENZIAZIONE di p.
	// La deferenziazione è definita quindi come "L'accesso al valore di una variabile attraverso il suo indirizzo di memoria".
	// L'operazione è valida sia in LETTURA che in SCRITTURA.

}

int main(void) {
	int x = 5;
	printf("x è %d\n", x);
	incr(&x);
	printf("x adesso è %d\n", x);
	return 0;

}
