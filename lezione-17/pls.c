#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// Programma che riscrive le PLS utilizzando le struct
struct pls {
  uint32_t len;
  uint32_t refcount;
  uint32_t magic;
  char str[];
};

char *ps_create(char *init, int len) {
  struct pls *p = malloc(sizeof(struct pls) + len + 1);
  p->len = len;
  // quando ci sono funzioni che restituiscono un oggetto utilizzando reference counting è buona norma inizializzare il conto delle referenze a 1.
  p->refcount = 1;
  p->magic = 0xDEADBEEF;
  for (int j = 0; j < len; j++) {
    p->str[j] = init[j];
  }
  p->str[len] = 0;
  // ho finito di memorizzare i caratteri della stringa e quindi inserisco il terminatore di linea.
  return p->str;
}

// funzione per stampare la stringa
void ps_print(char *s) {
  struct pls *p =(struct pls*)(s - sizeof(*p));
  for (int j = 0; j < p->len; j++) {
    putchar(p->str[j]);
  }
  printf("\n");
}

void ps_validate(struct pls *p) {
  if (p->magic != 0xDEADBEEF) {
    printf("Invalid string.\n");
    exit(1);
  }
} 

void ps_free(char *s) {
  free(s - sizeof(struct pls));
}
/* APPUNTO SU ps_release, refcount ed esercizi di stile */
// In sostanza quando si lancia ps_release su un refcount == 0 il programma dovrebbe terminarsi.
// Il problema è che se si prova a lanciarlo comunque, si corrompe l'header e il programma scrive numeri strani.
// Quindi per azzerare il refcount realmente facciamo un workaround, aggiungendo il campo magic alla struct.
// Quando la refcount va a 0, il campo magic viene settato a 0; quando normalmente è settato a 0xDEADBEEF.
void ps_release(char *s) {
  struct pls *p =(struct pls*)(s - sizeof(*p));
  ps_validate(p);
  p->refcount--;
  if (p->refcount == 0) {
    p->magic = 0;
    ps_free(s);
  }
}

void ps_retain(char *s) {
  struct pls *p =(struct pls*)(s - sizeof(*p));
  if (p->refcount == 0) {
    printf("Errore. Stringa illegale\n");
    exit(1);
  }
  p->refcount++;
}

uint32_t ps_len(char *s) {
  struct pls *p =(struct pls*)(s - sizeof(*p));
  return p->len;
}

char *global_string;

int main(void) {
  char *mystr = ps_create("HelloWorld", 10);
  global_string = mystr;
  ps_retain(mystr);
  ps_print(mystr);
  ps_print(global_string);
  ps_release(mystr);
  ps_release(mystr);
  ps_release(mystr);
  return 0;
}

