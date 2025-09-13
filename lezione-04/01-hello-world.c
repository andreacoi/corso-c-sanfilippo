#include <limits.h>
#include <stdio.h>

int main(void) {
  // lo studio dei tipi
  int x = 5;
  // c non specifica quanto deve essere grande lo "spazio" della variabile di
  // tipo int
  // Quello che vale per tutte le versioni del C è che se la variabile di tipo
  // int NON è preceduta dalla keyword UNSIGNED è da considerarsi CON IL SEGNO,
  // cioè capace di rappresentare sia numeri positivi, sia negativi.
  // Per conoscere la dimensione (a memoria) di un tipo, ci viene in soccorso
  // sizeof.
  // La funzione sizeof ritorna come valore un LONG UNSIGNED, quindi il
  // programma va in warning. Se invece di %d specifichiamo nella printf %lu,
  // rimuoviamo il warning.
  // Se vogliamo però sapere quali sono i valori massimi e minimi che possiamo
  // rappresentare in una determinata variabile possiamo utilizzare l'header
  // limits.h
  printf("int min: %d\nint max: %d\n", INT_MIN, INT_MAX);
  // qui le due costanti sono definite all'interno del file header come INT_MIN
  // e INT_MAX
  return 0;
}
