#include <stdio.h>
// con questo esempio di programmazione funzionale abbiamo visto come sia possibile ciclare qualcosa utilizzando solo una funzione e un ciclo if, senza passare per strutture di looping.
void conta(int start, int end) {
	if (start > end) return;
	printf("%d\n", start);
	conta(start+1, end);
}

int main(void) {
	conta(0, 9);
	return 0;
}

