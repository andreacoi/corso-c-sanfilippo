#include <stdio.h>

int main(void) { 
  char c = 10;
  printf("Prova %d\n", c);
  // in questo specifico caso la printf "promuove" il char a int, attivando un cast implicito.
  
  // il char d invece può anch'esso essere trasformato in un int, convertendo il carattere che si trova in APICI SINGOLE, nel corrispettivo ASCII dettato dall'archiettura.
  char d = 'a';
  printf("%d\n", d);
  // questo ci fa capire come il C, in fondo, gestisca solo numeri.
  
  // la stringa "Hello World" è un tipo primitivo chiamato stringa. È possibile passarlo alla printf come argomento cambiando la lettera dopo la percentuale (in questo caso %s).
  printf("%s\n", "Hello World");
  
  // la lezione continua nel file array.c
  return 0;
}

