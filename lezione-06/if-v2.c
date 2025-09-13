#include <stdio.h>

int main(void) {
	// in questa seconda versione del file vediamo come accedere a variabili che hanno lo stesso nome ma SCOPO LESSICALE diverso. Lo faremo utilizzando i puntatori.
	// per accedere all'indirizzo di memoria presso il quale una variabile è registrata, bisogna utilizzare la & seguita dal nome della variabile. Il placeholder utilizzato nella printf è %p.
	int i = 8;
	{
		int i = 5;
		printf("i (%zu bytes) is stored at: %p\n",sizeof(i), &i); 
	}
	printf("i (%zu bytes) is stored at: %p\n",sizeof(i), &i); 
	return 0;
}
