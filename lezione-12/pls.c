/* In C a differenza di altri linguaggi, come il PASCAL le stringhe non hanno una lunghezza prefissata.
 * A determinare la "lunghezza di una stringa" in C vi è il terminatore di riga che si occupa, appunto 
 * di terminare la riga e porre fine all'allocazione di memoria della stringa stessa.
 * Il PASCAL ad esempio, se deve scrivere una stringa la esprime così:
 * LHello World
 * laddove "L" è la lunghezza della stringa "Hello World", prefissata.
 * In questo programma, proveremo a scrivere un sistema del genere (PASCAL Style) per la gestione delle stringhe a
 * lunghezza prefissata (PLS).
 * Questo argomento sarà affrontato in due modi: quello errato e quello corretto (utilizzando malloc), per renderci conto di
 * quanto sia centrale malloc all'interno del linguaggio C.
 *
 */

#include <stdio.h>

// argomenti della funzione:
// - char *s, puntatore che serve a immagazzinare la stringa init,
// - char *init, la nostra stringa
// - int len (che dovrebbe essere però size_t, per correttezza), la lunghezza della nostra stringa 
// Questa funzione inizializza una stringa di lunghezza prefissata passata in 'init' di lunghezza 'len'.
// Attenzione, questa funzione potrebbe avere un comportamento imprevisto perché non esegue il check dell'overflow del buffer.
void ps_init(char *s, char *init, int len)  {
	// registro il primo byte come unsigned, per utilizzare uno spazio di memoria che va da 0 a 255, anziché da -128 a 127.	
	unsigned char *lenptr = s; // <-- essenzialmente questo è un cast di s, quindi lenptr è sempre l'indirizzo di memoria a cui punta s.
	// associo lenptr a len
	*lenptr = len;
	// faccio un ciclo for saltando il primo slot, che è destinato all'allocazione della memoria.
	for (int j = 0; j < len; j++) {
		s[j+1] = init[j];
	}

}

void ps_print(char *s)  {
	unsigned char *lenptr = (unsigned char *) s;
	for (int j = 0; j < *lenptr; j++) {
		putchar(s[j+1]);
	}
	printf("\n");
}
// Quindi, in cosa consiste in breve il programma?
// Dichiaro un buffer (in questo caso da 256) e alloco 11 di questi byte per scrivere hello world.
// Tramite putchar, ciclando con j+1, scrivo lettera per lettera il contenuto di buf.
// I vari char contenuti in init li immagazzino con s[j+1], rispetto alla memorizzazione del carattere precedente
// perché:
// FFFFFFFFF <-- memoria
// Lxxxxxxxx <-- primo byte utilizzato per la memoria
// LHello World <-- esempio completo
//
// Resta inteso che essendo 256 un valore hardcoded, non è fattibile andare ogni volta ad allocare manualmente la memoria per scrivere una stringa.
// Da qui andiamo al programma scritto correttamente: pls2.c
//
int main(void) {
	char buf[256];
	ps_init(buf, "Hello World", 11);
	ps_print(buf);
	ps_print(buf);
	ps_print(buf);
	return 0;
}
