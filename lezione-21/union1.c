#include <stdio.h>
#include <string.h>
#include <limits.h>
/* Una union è un tipo di dati aggregato che condivide lo stesso spazio di memoria di quelle che sono le sue componenti. */
/* Esempio di Salvatore:
 *
 *  visualizzazione grafica della struct foo in memoria
 *  IIIICCCC
 *  o meglio:
 *  IIII0123 - per ogni elemento dell'array a[0], a[1], a[2]...
 *
 * */

struct foo {
  union {
    int i;
    unsigned char a[4];
  };
};

int main(void) {
  // assegno i valori durante la dichiarazione - spiegazione nel commento successivo - poco utilizzata, non ha senso assegnare dei valori al momento dell'init. Non viene mai fatto.
  //struct foo f = {10, {1,2,3,4}};
  struct foo f;
  /* il codice che segue rappresenta un errore perché questo tipo di inizializzazione si può fare SOLO durante la dichiarazione.
  f.i = 10;
  f.a = {1,2,3,4};
  */
  // chiunque utilizzerebbe memcpy per fare una roba del genere, infatti...
  f.i = INT_MAX;
  printf("%d [%d %d %d %d]\n", f.i, f.a[0], f.a[1], f.a[2], f.a[3]);
  // !IMPORTANTE! - f.a è il puntatore all'inizio dell'array a (ancora una volta parallelismo tra array e puntatori).
  return 0;
}

