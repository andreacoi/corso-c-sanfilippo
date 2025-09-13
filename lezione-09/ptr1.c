#include <stdio.h>

int main(void) {
	int x = 5;
	// un puntatore si dichiara con l'asterisco messo prima del nome della variabile
	int *y = 0; // attenzione! questa associazione si riferisce all'indirizzo di memoria che in questo caso è speciale, infatti lo 0 indica un puntatore nullo (infatti l'indirizzo è: 0x0)
	// questo tipo di dichiarazione significa che y È UN INDIRIZZO DI MEMORIA che PUNTA ad un intero. 
	printf("%d\n", x);
	// per stampare un puntatore utilizzando printf occorre utilizzare %p.
	// in maniera similare posso sapere a quale indirizzo risiede int x.
	y = &x;
	// esiste una correlazione forte tra array e puntatori. Infatti possiamo "variare" il valore di x utizzando questa espressione:
	*y = 10;
	// o alternativamente questa:
	y[0] = 10;
	// perché all'indirizzo di memoria al quale punta y è presente solo un intero.
	printf("x è memorizzato presso: %p\n", y);
	return 0;
}
