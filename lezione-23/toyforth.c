#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*================================= Data structures =======================================*/
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
    // il fatto di utilizzare una union è chiaro. ogni occorrenza può essere di UN SOLO TIPO (da qui l'utilizzo di una union anonima) per volta, quindi:
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

// dichiaro una struct per immagazzinare i dati da parsare (il programma prg) e il prossimo token* di cui effettuare il parse.
// cfr. definizione ChatGPT --> 
// Il lexer* (o tokenizer) lo suddivide in token come:
/*
  * es. x = 5 + 3;
  * x → identificatore
  * = → operatore di assegnazione
  * 5 → numero
  * + → operatore aritmetico
  * 3 → numero
  * ; → terminatore di istruzione
*/
typedef struct tfparser {
  char *prg; // <-- il programma da compilare 
  char *p; // <-- il prossimo token di cui effettuare il parse
} tfparser;

// dichiaro una struct tfctx, che mi è necessaria per avere il contesto all'interno del quale eseguire il mio programma, una volta compilato.
typedef struct tfctx {
  tfobj *stack;
} tfctx;

/*=============================== Allocation wrappers  =====================================*/

// per scrivere una "variazione" di malloc, inizio con il copiarmi il prototipo dalla manpage
// void *malloc(size_t size); <-- prototipo della malloc

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Out of memory, sto cercando di allocare %zu bytes.\n", size);
    exit(1);
  }
  return ptr;
}

/*============= Funzioni relazionate agli oggetti (object related functions) ===============*/

// alloca e inizializza l'oggetto ToyForth Object - generico, grazie a type è possibile creare tutti gli altri.
tfobj *createObject(int type) {
// qui dovremmo allocare l'oggetto e quittare in caso di out of memory, quindi ci prepariamo
// una versione modificata di malloc, che chiamiamo xmalloc.
  tfobj *o = xmalloc(sizeof(tfobj));
  // indico il tipo di tfobj
  o->type = type;
  // setto refcount a 1 perché in fase di creazione dell'oggetto devo dare almeno 1 come valore alla referenza.
  o->refcount = 1;
  return o;
}

// alloca e inizializza un oggetto di tipo STRING
tfobj *createStringObject(char *s, size_t len) {
  tfobj *o = createObject(TFOBJ_TYPE_STR);
  o->str.ptr = s;
  o->str.len = len;
  return o;
}

// alloca e inizializza un oggetto di tipo SYMBOL - funzioni e operatori
tfobj *createSymbolObject(char *s, size_t len) {
  tfobj *o = createStringObject(s, len);
  o->type = TFOBJ_TYPE_SYMBOL;
  return o;
}

// alloca e inizializza un oggetto di tipo INT
tfobj *createIntObject(int i) {
  tfobj *o = createObject(TFOBJ_TYPE_INT);
  o->i = i;
  return o;
}

// alloca e inizializza un oggetto di tipo BOOL - come un intero
tfobj *createBoolObject(int i) {
  tfobj *o = createObject(TFOBJ_TYPE_BOOL);
  o->i = i;
  return o;
}

// alloca e inizializza un oggetto di tipo LIST
tfobj *createListObject(int i) {
  tfobj *o = createObject(TFOBJ_TYPE_LIST);
  o->list.ele = NULL; // <-- la lista al momento dell'inizializzazione deve essere vuota.
  o->list.len = 0; // <-- per questo motivo len deve essere = 0.
  return o;
}
/*======================================= Main ============================================*/

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
