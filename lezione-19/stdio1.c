#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>

#define HEXDUMP_CHARS_PER_LINE 16
// funzione per eseguire il corrispettivo di hexdump
void hexdump(void *p, size_t len) {
  // all'interno di p posso allocare qualsiasi cosa perché
  // si tratta di un void *p.
  unsigned char *byte = p; 
  // variabile dedicata al printed offset.
  size_t po = 0;
  // se per po uso size_t e per len uso size_t, lo utilizzerò anche per j -> tipo COERENTE ALLA LUNGHEZZA -> tipo COERENTE ALLA LUNGHEZZA (len).
  for (size_t j = 0; j < len; j++) {
    // a questo punto rendo più leggibile la mia hexdump
    printf("%02X ", byte[j]);
    // TODO: IMPOSTARE COSTANTI PER NUMERO DI BYTE DA VISUALIZZARE e controllare offset diversi da 8.
    // questo ciclo if serve ad andare a capo prima della 9^riga. In questo modo possiamo avere dei blocchetti di 8.
    // ovviamente verifico con j == len - 1 di essere all'ultimo ciclo for, quindi stampo un solo \n.
    // dopo aver concluso la stampa degli hex, voglio stampare anche il contenuto.
    // per cui, rivediamo questo if:
    if ((j + 1) % HEXDUMP_CHARS_PER_LINE == 0 || j == len - 1) {
    // questo ciclo if gestisce il padding per arrivare alla fine linea e fare un "quadratino vero" utilizzando la tilde.
      if (j == len -1) {
        int pad = HEXDUMP_CHARS_PER_LINE - (len % HEXDUMP_CHARS_PER_LINE);
        pad %= HEXDUMP_CHARS_PER_LINE;
        for (int i = 0; i < pad; i++) printf("~~ ");
      }
      printf("\t");
      // dopo aver stampato la tabulazione stampiamo il contenuto di str, con un ciclo for.
      for (size_t i = po; i <= j; i++) {
        // a questo punto non è detto che tutti i caratteri siano pieni, cioè stampabili a video.
        // Quindi ho bisogno di una funzione che verifica se ciò sia possibile.
        // Questa funzione si chiama isprint
        // Per avere una funzione più compatta utilizziamo l'operatore ternario ?
        // Quindi verifica: se il byte[i] è stampabile c = byte[i], altrimenti c == '.'
        int c = isprint(byte[i]) ? byte[i] : '-';
        printf("%c", c);
      }
      printf("\n");
      po = j+1;
    } 
  }
 // con questa printf ho sempre "un a capo in più".
 // questo però tuttavia è un caso speciale che posso inserire all'interno del ciclo for.
 // if (len % 8 != 0)  printf("\n");
}


int main(void) {
  // questa è una syscall per aprire un file in modalità SOLA LETTURA.
  int fd = open("stdio1.c", O_RDONLY);
  // Diversamente dal file pointer alla struct FILE, questa syscall in
  // caso di fallimento ritorna -1 (conforme allo std POSIX in caso di errore.
  // provo a stampare il numero intero dell'errore
  if (fd == -1) {
   // invece di usare la printf classica, possiamo usare perror 
   perror("Impossibile aprire il file");
   // perror riesce a sapere qual è il tipo di errore perché esiste errno.h
   // che fornisce una variabile globale con il numero dell'errore.
   return 1;
  }
  // buffer dove immagazzinare i byte
  char buf[32];
  // inizializzo un size_t per capire di quanti byte ho bisogno
  ssize_t nread;
  while (1) {
    nread = read(fd, buf, sizeof(buf)); 
    // quando finiscono i byte a disposizione la lettura è terminata quindi break.
    if (nread == 0) break;
    // hex dump accetta buf come argomento, il che significa che "il contenuto" del file
    // identificato da fd (file descriptor) viene letto da read e inserito all'inizio del buffer.
    // cfr. manpages - man read
    hexdump(buf, nread);
  }

  // syscall corrispettiva a fclose per chiudere il file.
  // anche se si può pensare che close sia fcntl.h, in realtà è su unistd.h
  // Questo perché si tratta di una chiamata di sistema PROFONDAMENTE GENERALE.
  // Non si usa solo per i file.
  close(fd);
  return 0;
}

