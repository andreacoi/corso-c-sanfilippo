#include <stdio.h>

// Per comprendere bene l'utilizzo delle struct, riscriviamo il comando tac (inverso del comando cat)
// Concetti chiave: apertura di file e argomenti della funzione main:
// - argc
// - argv

int main(int argc, char **argv) {
  // Perché argv è un puntatore a puntatore di char?
  // Perché una stringa è un PUNTATORE AD UN ARRAY DI CARATTERI
  // Quindi:
  // **argv rappresenta l'indirizzo di memoria al quale sono memorizzati gli indirizzi
  // di memoria e CIASCUNO DI QUESTI INDIRIZZI DI MEMORIA è l'indirizzo di memoria nel
  // quale è memorizzato un array di char che è la mia stringa (argomento).
  //
  // RAPPRESENTAZIONE:
  // dove 1000, 2000 e 3000 sono indirizzi di memoria a caso:
  // 1000: foo
  // 2000: bar
  // 3000: [1000, 2000]
  // quindi 1000 è char *, così come 2000.
  // 3000 è char ** perché PUNTA a un array di indirizzi di memoria.
  for (int i = 0; i < argc; i++) {
    printf("%d: %s\n", i, argv[i]);
  }
}
