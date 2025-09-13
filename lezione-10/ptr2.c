#include <stdio.h>

int main(void) {
	int x = 5;
	int *y = &x; 
	// y è l'indirizzo di memoria al quale risiede x.
	printf("x vive in %p e vale %d\n", y, x);
	// Nota importante: le stringhe sono array di char.
	// Pertanto possiamo sfruttare l'analogia tra array e puntatori per operare su una stringa
	// Es. 
	char mystr[] = "Hello World";
	char *p = mystr;
	
	printf("All'indirizzo %p posso vedere %s\n", mystr, mystr);
	// N.B. Alla printf passo due volte mystr:
	// - la prima lo passo come puntatore mystr
	// - la seconda come "contenuto" dell'indirizzo di memoria.
	// Quindi, il NOME STESSO DELL'ARRAY È, PER DEFINIZIONE, IL PUNTATORE A QUELL'ARRAY.
	
	// Possiamo fare anche un esercizio di teoria provando a lavorare con i singoli char
	// Deferenziando p, con p[0], stampo il primo char (la H).
	printf("%c\n", p[0]);	
	// utilizzando la notazione con le parentesi quadre posso accedere ai vari elementi del puntatore chiamandoli con l'indice dell'array.
	// L'espressione *p invece mi riporta solo il PRIMO ELEMENTO.
	printf("%c\n", *p);	
	// Esiste, quindi un modo per accedere ai diversi elementi utilizzando la notazione *p? Certo! Utilizzando l'espressione *(p+1).
	// In questo modo il puntatore punterà ad esattamente il byte successivo.
	return 0;
}
