#include <stdio.h>

int main(void) {
	// in questo programma esamineremo dettagliatamente i costrutti per ciclare nel codice. for e while sono essenzialmente identici.
	int i = 0;
	// ciclo while
	while (i < 10) {
		printf("%d\n", i);
		i++;
	}
	// ciclo for 
	for (i = 0; i < 10; i++) {
		printf("%d\n", i);
	}
	return 0;
}
