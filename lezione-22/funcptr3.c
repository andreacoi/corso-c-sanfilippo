#include <stdio.h>

void hello(void) {
  printf("hello!\n");
};

void baubau(void) {
  printf("baubau!\n");
}
// questa funzione è una funzione ricorsiva e con pochissime righe di codice è possibile implementarla
void call_n_times(int n,void (*x)(void)) {
  while(n--) {
    x();
  }
} 

int main(void) {
  void (*x)(void); // <-- puntatore a funzione
  call_n_times(10, hello); // <-- qui scrive 10 volte hello
  call_n_times(10, baubau); // <-- qui scrive 10 volte baubau
  // questo è possibile perché l'impronta delle due funzioni hello e baubau è identica, quindi è possibile passare a call_n_times le due funzioni in maniera del tutto indifferente.
 return 0;
}
