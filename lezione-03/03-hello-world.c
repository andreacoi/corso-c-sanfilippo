#include <stdio.h>

int incr(int x) {
  x = x + 1;
  return x;
}

int main(void) {
  int a = 10;
  // questo è l'esempio del passaggio per valore alle funzioni.
  // In C, infatti, gli argomenti vengono passati alle funzioni sempre per
  // valore. in questo caso infatti non associando alcun valore a incr(a) la
  // funzione incr, con il suo valore di ritorno non sa che farsene.
  incr(a);
  // se invece scriviamo così, l'incremento si concretizza effettivamente.
  a = incr(a);
  printf("%d\n", a);
  return 0;
  // Il passaggio per valore consiste nel passare alla funzione una copia
  // dell'elemento originale. Diverso invece è il passaggio per riferimento che
  // consente di far modificare a una funzione DIRETTAMENTE I DATI ORIGINALI.
  // L'unico modo, in C,  per passare un argomento a una funzione per
  // riferimento è quello di utilizzare i puntatori.
}
