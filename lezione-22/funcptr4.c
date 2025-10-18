#include <stdio.h>
#include <stdlib.h>
// copio dalla manpage di qsort l'impronta della funzione utilizzata per confrontare gli elementi.
int compare_integers(const void *a, const void *b){
  // qsort deve tornare:
  // < 0 se a < b
  // 0 se a = b
  // > 0 se a > b
  const int *ap = a;
  const int *bp = b;
  // qui ho eseguito una conversione di tipo
  // Visto che l'impronta della funzione richiede due argomenti di tipo const (che perciò non devono essere variati)
  // associo ap e bp rispettivamente a due puntatori a intero, dei quali, deferenziandoli potrò ottenere il valore.
  // questo tipo di return è uno shortcuts perché coincide perfettamente con i tipi di valori di ritorno attesi dalla funzione qsort
  // < 0, = 0 e > 0. Tuttavia questa espressione genera comportamenti inattesi in casi particolari (es. un numero vicino o coincidente con INT_MAX o INT_MIN (wrap around).
  // Per avere del codice safe bisognerebbe utilizzare if.
  // return *ap - *bp; // con l'asterisco vado a risalire all'intero. n.b. posso anche scrivere ap[0] e bp[0]
  // codice corretto:
  if (*ap < *bp) return -1;
  else if (*ap > *bp) return 1;
  else return 0;
  // tutti questi concetti ci fanno capire che è possibile anche utilizzare i puntatori a funzioni all'interno delle struct, andando così a ottenere un qualcosa di molto simile ad un oggetto.
};
// per capire effettivamente i vantaggi nell'utilizzo di un puntatore a funzione proviamo a utilizzare qsort, una funzione per l'ordinamento degli elementi che è contenuta nella stdlib.h
int main(void) {
  // creiamo un array di interi
  int a[10];
  for (int j = 0; j < 10; j++) {
    // a[j] = rand(); // --|> questo rand genera numeri troppo grandi, quindi Salvatore li limita utilizzando & (bitwise AND). 
    // Il bitwise & con il 15, tiene "accesi" solo gli ultimi 4 bit del numero.
    // (15 in binario è 1111). È una maschera, quindi 2356 & 15, diventa 4.
    // & prende i bit che sono veri sia da una parte che dall'altra dell'operatore (in binario):
    //     1001 0011 0100   (2356)
    // AND 0000 0000 1111   (15)
    //   -----------------
    //     FFFF FFFF FVFF 
    //     0000 0000 0100 (4)
    //
    //     Laddove 0 & 1 F, 0 & 0 F, 0 & 1 V
    //     Questo tipo di operazione viene definita "maschera" (o masking).
    a[j] = rand() & 15;
  }
  
  // a questo punto devo chiamare qsort
  qsort(a, 10, sizeof(int), compare_integers);
 
  for (int j = 0; j < 10; j++) {
    printf("%d ", a[j]);
  }
  printf("\n");
  return 0;
}
