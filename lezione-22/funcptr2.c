#include <stdio.h>

void hello(void) {
  printf("hello!\n");
};

void baubau(void) {
  printf("baubau!\n");
}

int main(void) {
  // avendo dichiarato le due funzioni hello e baubau
  void (*x)(void); // <-- puntatore a funzione
  x = hello; // <-- qui x punta a hello
  x(); // <-- hello!
  x = baubau; // <-- qui x punta a baubau
  x(); // <-- baubau!
 return 0;
}
