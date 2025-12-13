#include <stdio.h>
#include <stdarg.h>

/* Le funzioni variadiche
 * Le funzioni variadiche accettano un numero variabile di argomenti.
 * Per esprimerlo in maniera sintattica, si usa l'ELLISSI come ULTIMO argomento
 * Poi però questi (il loro numero e la lunghezza di ciascuno di essi) vanno
 * gestiti con va_list, va_start, va_arg e per chiudere va_end.
 * Queste sono delle MACRO e sono contenute nella libreria stdarg.h.
 */
void foo(char *bar, ...) {
  va_list ap;
  // va_start DEVE AVERE come argomenti:
  // - una variabile di tipo va_list (ap);
  // - l'ultimo argomento della funzione NON variabile (char *bar)
  // in questo modo va_start sa che deve iniziare a elaborare gli argomenti
  // variabili dopo char *bar.
  va_start(ap, bar);
  printf("%s\n", bar);
}

int main(void) {
  printf("Hello World\n");
  char *bar = "gino";
  foo(bar);
  return 0;
}
