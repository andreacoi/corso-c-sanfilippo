#include <stdio.h>
#include <stdlib.h>

// alla luce dei file precedenti, riscrivo il file per creare le frazioni utilizzando le struct.

struct fract {
  int num;
  int den;
};
// funzione per creare la frazione - ritorna null se malloc fallisce.
// È bene specificare e ricordare che adesso io ritorno un puntatore utilizzando malloc,
// ma potrei benissimamente ritornare direttamente una struct, direttamente.
// È ALTRETTANTO IMPORTANTE SAPERE, TUTTAVIA, CHE RITORNARE LE STRUCT PER VALORE, NON SI FA!!!
// Infatti, in questo modo, il codice crea delle COPIE, e questo in termini di codice È
// PROFONDAMENTE INEFFICIENTE!!! NON SI FA QUASI MAI.

// TEOREMA DI SANFILIPPO
// LE STRUCT VENGONO PASSATE PER PUNTATORE, VENGONO ALLOCATE NELL'HEAP E SONO DEGLI OGGETTI
// DA ALLOCARE E DISTRUGGERE COME SI CREDE CON MALLOC() E FREE()

struct fract *create_fraction(int num, int den) {
  struct fract *f = malloc(sizeof(*f));
  // verifica l'allocazione di memoria
  if (f==NULL) return NULL; // gestione errori
  f->num = num;
  f->den = den;
  return f;
};

// funzione per stampare la frazione
void print_fraction(struct fract *f) {
  printf("%d/%d\n", f->num, f->den);
};

// funzione per semplificare la funzione
void simplify_fraction(struct fract *f) {
  for (int d = 2; d <= f->num && d <= f->den; d++) {
    while(f->num % d == 0 && f->den % d == 0) {
      f->num /= d;
      f->den /= d;
    }
  }
};

int main(void) {
  struct fract *f1 = create_fraction(10,20);
  print_fraction(f1);
  simplify_fraction(f1);
  print_fraction(f1);
  return 0;
}
