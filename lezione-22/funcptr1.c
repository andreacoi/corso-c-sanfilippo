#include <stdio.h>

void hello(void) {
  printf("hello!\n");
};

void baubau(void) {
  printf("baubau!\n");
}

int main(void) {
  int main(void); // prototipo della funzione main
  /* I prototipi delle funzioni
   * I prototipi delle funzioni sono una caratteristica presa in prestito dal C++.
   * Consentono di evitare degli errori subdoli in fase di compilazione, dovuti a chiamate di funzioni improprie. 
   * In sostanza, specificano il valore di ritorno e gli argomenti (e il loro tipo) accettati dalla funzione. In questo modo ci costringe al rispetto dei tipi o via casting esplicito
   * o via casting esplicito.
   * È anche importante per dire al nostro programma: "attenzione! che esiste una funzione main in un punto x del programma o (addirittura in un altro file) dichiarata così. 
   */
  // Un puntatore a funzione invece si dichiara così:
  int (*myf)(void); // <-- puntatore a funzione
  // in maniera molto similare a un prototipo di funzione, solo che bisogna racchiudere il nome della funzione tra parentesi, prependendo un asterisco.
  myf = main;
  printf("%p, %p\n", main, myf);
  // la cosa molto interessante è che io posso chiamare myf!
  // myf(); <-- lo commentiamo perché altrimenti andiamo a generare un loop infinito.
  return 0;
}
