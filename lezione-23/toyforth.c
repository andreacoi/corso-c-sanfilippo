#include <stdio.h>
#include <stdlib.h>
// per scrivere un inteprete bisogna innanzitutto individuare i tipi primitivi:
// int
// str
// bool
// list
#define TFOBJ_TYPE_INT 0
#define TFOBJ_TYPE_STR 1
#define TFOBJ_TYPE_BOOL 2
#define TFOBJ_TYPE_LIST 3
#define TFOBJ_TYPE_SYMBOL 4 // <-- tipo "a parte" perché riguarda i "simboli", che sono tutte quelle parole che non vanno nello stack ma sono FUNZIONI da eseguire.
// dichiariamo una struct per gestire i tipi e gli operatori (symbols)

typedef struct tfobj {
  // reference counting
  int refcount;
  // int per gestire il tipo, essendo int gestisce anche il booleano
  int type; // <-- TFOBJ_TYPE_*
  union {
    // union per i come intero OPPURE str come stringa. La struct viene gestita come stringa utilizzando un puntatore a char e una lunghezza.
    // il fatto di utilizzare una union è chiaro. ogni occorrenza può essere di un solo tipo per volta, quindi:
    // - o è un intero;
    // - o è una stringa (o un simbolo/funzione);
    // - o è una lista
    int i;
    struct {
      char *ptr;
      size_t len;
    } str;
    // per gestire la lista occorre un puntatore in grado di immagazzinare una lista e quindi 
    struct {
      struct tfobj **ele; // <-- questa lista è un array di puntatori a oggetti tfobj, definizione ricorsiva. Il mio array è un puntatore a dei puntatori di tipo tfobj.
      size_t len;
    } list;
  };
} tfobj;

typedef struct tfparser {
  char *prg; // <-- il programma da compilare 
  char *p; // <-- il prossimo token di cui effettuare il parse
} tfparser;

typedef struct tfctx {
  tfobj *stack;
} tfctx;

// dovremmo leggere un programma passato come stringa tramite argomento argc, ma facciamo il programma più semplice possibile.
int main(int argc, char **argv) {
  // controlliamo che il numero di argomenti sia adeguato, se non lo fosse restituiamo errore
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  // qui poi dobbiamo eseguire le funzioni compile ed exec
  // n.b. per eseguire il programma ho bisogno di un contesto di esecuzione del programma.
  printf("%s %d\n", argv[0], argc);
  return 0;
}
