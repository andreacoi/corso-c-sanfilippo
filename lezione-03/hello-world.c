#include <stdio.h>

// scrivo  una funzione per fare l'incremento di una variabile e ritornare il
// valore int della variabile stessa.

// le funzioni con argomenti void e ritorno void hanno solo effetti
// "COLLATERALI" nei linguaggi imperativi. In questo specifico caso, la funzione
// stampa solo il valore x quando viene chiamata.

// per fare la prova inizializzo una variabile globale per capire cosa succede
// alla mia variabile quando viene chiamata incr()

// variabile globale
int x = 0;

void incr(void) {
  x = x + 1;
  printf("%d\n", x);
}

int main(void) {
  // vado a provare la funzione chiamandola con ()
  incr();
  incr();
  incr();
  incr();
  // è importante chiarire che ad ogni chiamata della funzione incr() la
  // variabile x viene CREATA e DISTRUTTA. Questo perché x è una variabile
  // locale.
  return 0;
}
