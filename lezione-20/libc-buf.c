#include <stdio.h>
#include <unistd.h>
#include <string.h>
/* Primo argomento trattato durante la lezione:
 * Differenze (viste le precendenti lezioni) tra syscall e libc.
 * Qual è la tecnica più veloce tra syscall e libc?
 * Per rispondere a questa domanda è necessario capire il ruolo della libc e quali sono le sue funzioni.
 * Buffering della libc
 * Per comprendere meglio il funzionamento possiamo ricorrere alla chiamata sleep, che ci fa capire benissimo
 * come funziona un sistema multi-tasking (significa che il sistema SCEGLIE a chi "dare" tempo CPU tra i vari processi in attesa di essere eseguiti.
 * Questo tipo di multi-tasking viene definito multi-tasking pre-emptive e garantisce che tutti i processi continuino ad essere eseguiti.
 * Lo scheduler stabilisce a chi dare il tempo CPU tra tutti i processi che in quel momento vogliono essere eseguiti.
 * Perché abbiamo bisogno di sleep() per capire come funziona la libc?
 */
int main(void) {
  /* se scriviamo la printf senza terminatore di linea le chiamate printf e sleep si invertono...
   * quindi, prima aspettiamo 5 secondi e poi il programma mi stampa "Hello World".
   * Il motivo per cui il programma funziona così è IL BUFFERING DELLA LIBC.
   * Commentiamo la printf e proviamo a riscrivere il programma utilizzando un puntatore a char.
   */
  
  //printf("Hello World");
  char *mystr = "Hello World";
  size_t len = strlen(mystr);
  // IMPORTANTE! Fix al volo - ricorda sempre di rispettare la corrispondenza di tipo:
  // In una versione precedente di questo programma avevi scritto int j, in realtà j deve essere inizializzato come size_t!
  for (size_t j = 0; j < len; j++) {
    //
    // printf("%c", mystr[j]);
    // invece di utilizzare la printf uso putchar per stampare un solo carattere per volta...
    // dopo aver verificato che anche con putchar il comportamento è il medesimo commentiamo anche questa funzione e utilizziamo la syscall write.
    // 
    // putchar(mystr[j]);
    // 
    // write(STDOUT_FILENO, mystr+j, 1);
    // 
    // cosa significa questa write?
    // Il primo argomento è STDOUT_FILENO: non ho bisogno di un file descriptor, devo scrivere sullo standard output del terminale
    // Il secondo argomento punta all'indirizzo di memoria e ad ogni ciclo "avanza di un indirizzo",
    // 1 alloco un byte.
    // A questo punto utilizzando la write il programma scriverà prima la stringa e poi avvierà lo sleep.
    /* 
     * ****************************************** *
     * NOTA BENE                                  *
     * Anche se il funzionamento del programma    *
     * procede come si deve, sono costretto a     *
     * chiamare write n volte, quante sono quelle *
     * del ciclo.                                 *
     * ****************************************** *
    */
    // Le syscall sono molto impegnative e lente come chiamate.
    // Per cui la libc ogni volta che viene chiamata putchar, utilizza un buffer.
    // Quando il buffer si riempie oppure c'è una \n, il sistema scrive subito la stringa e libera il buffer.
    // Il carattere di terminazione di linea, serve come TRIGGER per liberare il buffer.
    putchar(mystr[j]);
    usleep(100000);
    fflush(stdout);
    // così simulo un effetto carino - stile typewriter.
  }
  // per simulare il comportamento del terminatore di linea esiste una funzione che consente di svuotare il buffer.
  fflush(stdout);
  sleep(5);
  return 0;
}

