#include <stdio.h>
#include <stdarg.h>

/* Le funzioni variadiche
 * Le funzioni variadiche accettano un numero variabile di argomenti.
 * Per esprimerlo in maniera sintattica, si usa l'ELLISSI come ULTIMO argomento
 * Poi però questi (il loro numero e la lunghezza di ciascuno di essi) vanno
 * gestiti con va_list, va_start, va_arg e per chiudere va_end.
 * Queste sono delle MACRO e sono contenute nella libreria stdarg.h.
 * UTILIZZO:
 * va_start DEVE AVERE come argomenti:
 *  - una variabile di tipo va_list (ap);
 *  - l'ultimo argomento della funzione NON variabile (char *fmt)
 * in questo modo va_start sa che deve iniziare a elaborare gli argomenti
 * variabili dopo char *fmt.
 */
void foo(char *fmt, ...) {
  // dichiaro il mio oggetto ap, che conterrà gli oggetti da estrarre
  va_list ap;
  va_start(ap, fmt);
  char *p = fmt;
  while (*p) {
    switch (*p) {
      case 'i':
        printf("%d\n", va_arg(ap, int));
        break;
      case 's':
        printf("%s\n", va_arg(ap, char*));
        break;
      default:
        printf("Wrong specifier.\n");
        // in questo specifico caso conviene usare goto, evitiamo il return
        // da così: 
        // va_end(ap);
        // return;
        // diventa:
        goto cleanup;
    }
    p++;
  }
cleanup:
  va_end(ap);
}

int main(void) {
  printf("Hello World\n");
  foo("isii", 5, "ciao ciao", 10, 20);
  return 0;
}
