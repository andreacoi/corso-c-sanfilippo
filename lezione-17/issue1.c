#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* struct {
  int len;
  char str[];
}
*/
// il dubbio sollevato è stato: perché con str abbiamo usato le parentesi quadre anziché char *str?
// Risposta: le due cose sono TOTALMENTE DIVERSE. Iniziamo con il dichiarare la struct con char *str.
// SOLO DOPO aver scritto la hexdump cerchiamo di chiarire qual è la differenza tra *str e [20]
struct pls{
  long len;
  // in questo caso questo è un offset non definito allocato alla FINE DELLA STRUCT, NON VALORIZZABILE. 
  // char str[];
  char str[20];
};


// un altro dubbio è derivante dalla rappresentazione in memoria della struct.
// Al momento abbiamo 4 byte per int len, poi il padding e poi char *str da 8.
// Per azzerare il padding il tipo int lo convertiamo in long.
//
// Per ottenere una rappresentazione più visuale possibile adesso ci scriviamo una funzione 
// hexdump.

void hexdump(void *p, size_t len) {
  // all'interno di p posso allocare qualsiasi cosa perché
  // si tratta di un void *p.
  unsigned char *byte = p; 
  // variabile dedicata al printed offset.
  size_t po = 0;
  // se per po uso size_t e per len uso size_t, lo utilizzerò anche per j -> tipo COERENTE ALLA LUNGHEZZA -> tipo COERENTE ALLA LUNGHEZZA (len).
  for (size_t j = 0; j < len; j++) {
    // a questo punto rendo più leggibile la mia hexdump
    printf("%02X ", byte[j]);
    // TODO: IMPOSTARE COSTANTI PER NUMERO DI BYTE DA VISUALIZZARE e controllare offset diversi da 8.
    // questo ciclo if serve ad andare a capo prima della 9^riga. In questo modo possiamo avere dei blocchetti di 8.
    // ovviamente verifico con j == len - 1 di essere all'ultimo ciclo for, quindi stampo un solo \n.
    // dopo aver concluso la stampa degli hex, voglio stampare anche il contenuto.
    // per cui, rivediamo questo if:
    if ((j + 1) % 8 == 0 || j == len - 1) {
      printf("\t");
      // dopo aver stampato la tabulazione stampiamo il contenuto di str, con un ciclo for.
      for (size_t i = po; i <= j; i++) {
        // a questo punto non è detto che tutti i caratteri siano pieni, cioè stampabili a video.
        // Quindi ho bisogno di una funzione che verifica se ciò sia possibile.
        // Questa funzione si chiama isprint
        // Per avere una funzione più compatta utilizziamo l'operatore ternario ?
        // Quindi verifica: se il byte[i] è stampabile c = byte[i], altrimenti c == '.'
        int c = isprint(byte[i]) ? byte[i] : '.';
        printf("%c", c);
      }
      printf("\n");
      po = j+1;
    } 
  }
 // con questa printf ho sempre "un a capo in più".
 // questo però tuttavia è un caso speciale che posso inserire all'interno del ciclo for.
 // if (len % 8 != 0)  printf("\n");
}


int main(void) {
  // inizializzo la struct 
  struct pls s;
  // associo i valori alle variabili 
  s.len = 10;
  // per questo trattandosi di un puntatore chiamo malloc per riservarmi lo spazio per immagazzinare la stringa.
  // N.B. dopo aver verificato cosa succede con un puntatore, nel caso di un array non posso più utilizzare malloc perché
  // SENZA puntatore non saprei dove allocare la memoria destinata alla stringa.
  // s.str = malloc(s.len + 1);
  // MEMCPY - componente della Libreria Standard del C che accetta tre argomenti:
  // - ptr sorgente
  // - ptr destinazione
  // - int numero di byte da copiare
  memcpy(s.str, "0123456789", 11);
  hexdump(&s, sizeof(s));
  return 0;

}
