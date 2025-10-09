#include <stdio.h>
#include <limits.h>
  // i bitfield servono per specificare la dimensione massima di una variabile allocata all'interno di una struct.
  // n.b. non è possibile specificare un bitfield fuori da una struct.
  // Casi d'uso - se ad esempio, all'interno di una struct ho una variabile di tipo booleano, sappiamo che può assumere solo i valori 0 e 1
  // che possono essere tranquillamente contenuti all'interno di un singolo bit.
  // es.

struct foo {
  unsigned char c:4;
  unsigned char d:8;
};

int main(void) {
  struct foo f;
  f.c = 17; // overflow!
  f.d = 2;
  printf("dim: %zu byte --> cb: %zu bit\n", sizeof(f), sizeof(f)*CHAR_BIT);
  printf("%d %d\n", f.c, f.d);
  // 8 + 4 fa 12, ma risultano sempre 2 byte --> 16 bit perché ci sono 4 bit di "padding". C va a riempire lo spazio per avere sempre misure di byte conformi.
  // In C, c'è una regola: incrementare un tipo unsigned oltre la sua dimensione massima avrà come conseguenza il wrapping around (il valore torna a 0 e riparte il conteggio).
  // Se invece il tipo è signed il comportamento è undefined. Salvatore consiglia di prestare massima attenzione agli undefined behavior e definisce questo comportamento una ROGNA
  // ASSURDA.
  // Perché utilizzare i bitfields? Due motivi:
  // - salvare memoria (come le union);
  // - gestire condizionalmente la memoria (poco usato e poco efficace);
  return 0;
}
