#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
  // questa è una syscall per aprire un file in modalità SOLA LETTURA.
  int fd = open("stdio2.c", O_RDONLY);
  // Diversamente dal file pointer alla struct FILE, questa syscall in
  // caso di fallimento ritorna -1 (conforme allo std POSIX in caso di errore.
  // provo a stampare il numero intero dell'errore
  printf("errore no. %d\n", errno);
  if (fd == -1) {
   // invece di usare la printf classica, possiamo usare perror 
   perror("Impossibile aprire il file");
   // perror riesce a sapere qual è il tipo di errore perché esiste errno.h
   // che fornisce una variabile globale con il numero dell'errore.
   return 1;
  }
  // syscall corrispettiva a fclose per chiudere il file.
  // anche se si può pensare che close sia fcntl.h, in realtà è su unistd.h
  // Questo perché si tratta di una chiamata di sistema PROFONDAMENTE GENERALE.
  // Non si usa solo per i file.
  close(fd);
  // TODO: IMPLEMENTARE LA QUESTIONE HEXDUMP, in congiunzione con le syscall.
  return 0;
}

