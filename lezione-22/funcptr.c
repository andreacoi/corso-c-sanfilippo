#include <stdio.h>

int main(void) {
  // come già anticipato nel README, il nome di una funzione è un puntatore al valore di ritorno di quella funzione.
  printf("%p\n", main);
  // cosa succede se chiamo la main dentro la main()?
  main();
  // si genera un loop infinito
  // questo genera un segmentation fault perché "a furia" di chiamare ricorsivamente la main il programma "esaurisce" lo stack allocato dal sistema operativo per l'esecuzione del programma.
  // Di default, lo stack è di una dimensione molto piccola (2MB, 4MB, 8MB).
  return 0;
}
