// per comprendere meglio l'utilizzo di typedef proviamo ad analizzare la libreria stdio.h.
// In particolare, il concetto di typedef è CENTRALE nella stdio.

#include <stdio.h>

int main(void) {
  // typedef è importante perché anche dichiarando FILE, lo stesso tipo FILE non è altro che un typedef a un struct
  // r è la modalità di apertura del file
  FILE *fp = fopen("stdio1.c", "r");
  // se il file non esiste, fopen ritorna un puntatore speciale (il puntatore a 0).
  if (fp == NULL) {
    printf("Impossibile aprire il file.\n");
    // se è impossibile aprire il file ritorna 1 (normalmente, un codice di errore per la macchina.
    return 1;
  }
  // una volta che il file è aperto, ci devo fare qualcosa per dare un senso al programma.
  // una delle cose che posso fare è leggere il contenuto del file utilizzando fread.
  // fread, da manuale, si aspetta come argomento un puntatore di tipo void, una dimensione (quanti byte leggere), e il numero di file.
  // Salvatore definisce l'API di fread un ANTIPATTERN, in quanto, secondo il suo parere hanno sbagliato a progettarla.
  // ad ogni fopen ricorda sempre di far corrispondere un fclose in modo da evitare un memory leak.
  char buf[32];
  size_t nread = fread(buf, 1, sizeof(buf), fp);
  // dopo la lettura Salvatore si va a recuperare la funzione hexdump, la include in questo file e va ad utilizzarla per leggere il contenuto del file e verificare che
  // l'output sia proprio il contenuto di questo sorgente. Io non lo faccio, in quanto non ci sono spunti di apprendimento a riguardo.
  // È però interessante notare come Salvatore abbia incluso una funzione scritta in precedenza in questo programma in maniera abbastanza brutale, facendoci notare
  // la potenza del C.
  
  // UN ASPETTO IMPORTANTE
  // Le manpages: per ogni cosa che deve scrivere, Salvatore consulta le manpages, perché sono tutto quello di cui abbiamo bisogno per capire come usare le funzioni del C.
  printf("%zd\n", nread);
  fclose(fp);
}
