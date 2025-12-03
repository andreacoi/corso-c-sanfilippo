#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
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
/* facendo un parallelismo con i linguaggi OOP questo è la rappresentazione in C di un OGGETTO <-- CONCETTO CHIAVE */
typedef struct tfobj {
  // reference counting
  int refcount;
  // int per gestire il tipo, essendo int gestisce anche il booleano
  int type; // <-- TFOBJ_TYPE_*
  // qui all'interno della struct possiamo aggiungere anche la variabile line per farci dire dall'interprete a quale linea è avvenuto l'errore.
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
    /* Nota: per gestire la lista avremmo potuto utilizzare una linked list che, a prima vista, potrebbe sembrare la soluzione ideale. 
     * Infatti la linked list ha una complessità algoritmica O(1), ma ha una cattiva località della cache (credo che Salvatore intendesse "allocazione")
     * e utilizza un bel po' di memoria perché ogni nodo ha un puntatore a next, nel caso di single linked list e due puntatori nel caso in cui si voglia utilizzare anche previous
     * (per muoversi nella lista precedente).
     */
    struct {
      struct tfobj **ele; // <-- questa lista è un array di puntatori a oggetti tfobj, definizione ricorsiva. Il mio array è un puntatore a dei puntatori di tipo tfobj.
      size_t len;
      // size_t alloc_len; // <-- parametro per SOVRAALLOCARE in maniera indipendente dalla dimensione di len. Ma lo faremo dopo.
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

/* Tabella delle funzioni - ciascuno di questi record
 * rappresenta un nome simbolo associato con una implementazione di funzione.
 * */
struct tfctx;
typedef struct FunctionTableEntry {
  // il nome della funzione
  tfobj *name;
  // l'esecuzione della funzione stessa
  void (*callback)(struct tfctx *ctx, tfobj *name);
  // inserisco anche un terzo campo della struct utile per gestire delle funzioni
  // definite dall'utente. Se il campo è null, le funzioni saranno quelle di default del linguaggio.
  tfobj *user_list;
} tffuncentry;

/* struct per memorizzare la lista delle funzioni "valide", conteggiandole. */
struct FunctionTable {
  // doppio puntatore perché è come se fosse un array di array
  // questo mi consente di allocare nell'heap la lista di funzioni comprensiva del numero delle funzioni stesse.
  tffuncentry **func_table;
  size_t func_count;
};

// dichiaro una struct tfctx, che mi è necessaria per avere il contesto all'interno del quale eseguire il mio programma, una volta compilato.
typedef struct tfctx {
  tfobj *stack;
  // oltre allo stack, nel contesto ho bisogno di avere una lista di funzioni da eseguire.
  struct FunctionTable functable;
} tfctx;

/*=============================== Function prototypes ======================================*/

void retain(tfobj *o);
void release(tfobj *o);

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

// così come ho scritto il wrapper per malloc, vale lo stesso per realloc
void *xrealloc(void *oldptr, size_t size) {
  void *ptr = realloc(oldptr, size);
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

/*
 * Nota sulla riscrittura della funzione exec -> printObject
 * La riscrittura coinvolge uno switch all'inizio della funzione per interpretare i casi:
 * Caso TFOBJ_TYPE_INT: stampa l'intero e fa break;
 * Caso TFOBJ_TYPE_LIST: (attenzione!) fa una chiamata ricorsiva alla funzione print_object
 * passando come elemento ele, e fa ripartire la scelta dei casi, stampando di fatto la lista di numeri com'era prima.
 * Postilla sulla exec: il nome è stato cambiato perché non si trattava di una vera e propria esecuzione.
 * TODO: scrivere la funzione exec.
 *
*/
void printObject(tfobj *o) {
  switch(o->type) {
    case TFOBJ_TYPE_INT:
      printf("%d", o->i);
      break;
    case TFOBJ_TYPE_LIST:
      printf("[");
      for (size_t j = 0; j < o->list.len; j++) {
        tfobj *ele = o->list.ele[j];
        // chiamata ricorsiva alla funzione
        printObject(ele);
        if (j != o->list.len - 1) printf(" ");
      }
      printf("]");
      break;
    case TFOBJ_TYPE_STR:
      // è la stessa cosa dello stampare un simbolo, ma lo metto dentro le virgolette.
      printf("\"%s\"", o->str.ptr);
      break;
    case TFOBJ_TYPE_SYMBOL:
      printf("%s", o->str.ptr);
      break;
    default:
      printf("?");
      break;
  }
}

// funzione per gestire la pulizia delle allocazioni degli oggetti.
// N.B. non tutti gli oggetti allocano memeoria.
void freeObject(tfobj *o) {
  switch(o->type) {
    case TFOBJ_TYPE_LIST:
      for (size_t j = 0; j < o->list.len; j++) {
        tfobj *ele = o->list.ele[j];
        // chiamata ricorsiva alla funzione
        // in questo caso è ricorsiva perché release chiama esso stesso freeObject
        release(ele);
      }
      break;
    case TFOBJ_TYPE_SYMBOL:
      break;
    case TFOBJ_TYPE_STR:
      free(o->str.ptr);
      break;
  }
  // pulisco l'oggetto principale, una volta puliti gli oggetti annidati.
  free(o);
}

// funzione per incrementare il refcount di o
void retain(tfobj *o) {
  o->refcount++;
}

// funzione per decrementare il refcount di o
void release(tfobj *o) {
  // prima di fare qualsiasi ci accertiamo che refcount sia > 0.
  assert(o->refcount > 0);
  o->refcount--;
  if (o->refcount == 0) freeObject(o);
}

/*============================== String Object ===============================*/

// alloca e inizializza un oggetto di tipo STRING
tfobj *createStringObject(char *s, size_t len) {
  tfobj *o = createObject(TFOBJ_TYPE_STR);
  // qui non gestisco l'allocazione.
  // fix:
  o->str.ptr = xmalloc(len + 1);
  o->str.len = len;
  memcpy(o->str.ptr, s, len);
  // dopo aver chiamato la memcpy, inserisco il NULL TERM alla posizione LEN.
  o->str.ptr[len] = 0;
  return o;
}

// alloca e inizializza un oggetto di tipo SYMBOL - funzioni e operatori
tfobj *createSymbolObject(char *s, size_t len) {
  tfobj *o = createStringObject(s, len);
  o->type = TFOBJ_TYPE_SYMBOL;
  return o;
}

// funzione per comparare delle stringhe, utilizzando memcpm(), ritorna 0 se
// le stringhe sono uguali, 1 se a>b, -1 se a<b.
int compareStringObject(tfobj *a, tfobj *b) {
  // stabilisco la lunghezza minima della stringa, risultante tra la
  // lunghezza minore tra le due lunghezze stringa (a e b)
  size_t minlen = a->str.len < b.str.len ? a->str.len : b->str.len; // <- operatore ternario
  // attenzione, qui all'utilizzo di memcmp.
  int cmp = memcmp(a->str.len, b->str.len, minlen);
  /* memcmp confronta stringhe della stessa dimensione:
   * questo significa che andiamo a confrontare il numero di caratteri "COMUNE"
   * tra a e b. 
   * Quindi poi a questo punto, una volta appurata l'uguaglianza tra le due parti parziali
   * verifichiamo la lunghezza. Se a è più "lungo" di b, le stringhe sono diverse, ritorno 1,
   * se b è più lungo di a, le stringhe sono diverse, ritorno -1, se a e b hanno la stessa
   * lunghezza sono necessariamente identiche, ritorno 0.
   * Faccio quindi un doppio confronto, prima sulla parte comune e poi sulla lunghezza.
   * Riprendi dal minuto 18.14.
   * */
  return 1;
} 

/*=============================== List Object ================================*/

// alloca e inizializza un oggetto di tipo LIST
tfobj *createListObject(void) {
  tfobj *o = createObject(TFOBJ_TYPE_LIST);
  o->list.ele = NULL; // <-- la lista al momento dell'inizializzazione deve essere vuota.
  o->list.len = 0; // <-- per questo motivo len deve essere = 0.
  return o;
}
// funzione per accodare gli elementi parsati alla lista tfobj
// il refcount dell'oggetto va incrementato dal chiamante, se necessario.
void listPush(tfobj *l, tfobj *ele) {
  /* Panoramica su realloc 
   * realloc prende una precedente allocazione *ptr e rialloca con una dimensione personalizzata.
   * se il puntatore è null, realloc è comodissima perché funziona come se fosse una malloc.
   */
  l->list.ele = xrealloc(l->list.ele, sizeof(tfobj*) * (l->list.len + 1)); 
  l->list.ele[l->list.len] = ele; // <-- l->list.ele[l->list.len] perché l->list.len rappresenta l'ultimo token.
  l->list.len++; // incremento il numero di elementi della lista.
}

/*============================= Convert program in TFOBJ ==================================*/
// funzione per "consumare gli spazi"
void parseSpaces(tfparser *parser) {
// per consumare gli spazi utilizzo la funzione isspace() per verificare che sia uno spazio.
// la funzione ispace è contenuta in ctype.h
// per fare questo utilizzo un ciclo while facendo scorrere parser->p
while (isspace(parser->p[0])) parser->p++; // fino a quando il carattere su cui sono ORA p[0] è uno spazio, 
}

#define MAX_NUM_LEN 128
// prepara prototipo della funzione per gestire gli interi
// Importante! Questa funzione deve gestire anche i numeri con un numero di cifre maggiore di 1.
// Per fare ciò devo creare un walker per "camminare fra i numeri".
tfobj *parseNumber(tfparser *parser) {
  char buf[MAX_NUM_LEN]; // <-- lunghezza max del mio numero
  char *start = parser->p;
  char *end;
  // verifica che il numero inizi per -
  if (parser->p[0] == '-') parser->p++;
  while (parser->p[0] && isdigit(parser->p[0])) parser->p++;
  end = parser->p;
  // quando siamo arrivati all'ultimo carattere numero ciclando con while
  // dobbiamo capire di quanti caratteri è composto il nostro numero (nella struct è numlen)
  int numlen = end - start; // <-- visto che i puntatori sono sempre interi posso effettuare delle operazioni di sottrazione.
  if (numlen >= MAX_NUM_LEN) return NULL;
  memcpy(buf, start, numlen);
  buf[numlen] = 0; // null terminator, all'ennesimo char inserisci il terminatore di riga.
  tfobj *o = createIntObject(atoi(buf));
  return o;
}

// creiamo una funzione di helper che ritorna true se il carattere incontrato è uno tra: char symchars[] = "+-*/%"; 
// come modello possiamo utilizzare una delle funzioni presenti in ctype.h, quindi la funzione ritorna int (0 oppure 1)
// e accetta come unico argomento un char c.
int is_symbol_char(char c) {
  char symchars[] = "+-*/%";
  if (isalpha(c)) {
    return 1;
    // strchr ritorna un puntatore a char se c è presente in symchars e ritorna un puntatore alla posizione del carattere c all'interno di symchars.
    // Se c non esiste all'interno di symchars, ritorna NULL.
  } else if(strchr(symchars,c) != NULL) {
    return 1;
  } else {
    return 0;
  }
}

// funzione per eseguire il parsing dei simboli - per simbolo si intende: PRINT, DUP, +, -, *
tfobj *parseSymbol(tfparser *parser) {
  char *start = parser->p; // primo record, EQUIVALENTE A parser->p[0] TODO: TEST.
  while (parser->p[0] && is_symbol_char(parser->p[0])) parser->p++; 
  int len = parser->p - start;
  return createSymbolObject(start, len);
}

// creo la funzione compile
// la funzione compile inserisce gli argomenti "parsati" all'interno di una ListObject (è sempre una tfobj *).
tfobj *compile(char *prg) {
  tfparser parser;
  parser.prg = prg; // <-- prg, il campo di parser diventa uguale alla variabile locale
  parser.p = prg; // <-- all'inizio della "compilazione" il programma parte sempre all'inizio dello stesso.
  // inizializzo una lista di tipo ListObject in cui inserire i vari dati parsati.
  tfobj *parsed = createListObject();
  while (parser.p) { // <-- ciclo while valido fino a quando il compilatore non incontra il NULL terminator.
    // inizializzo l'oggetto da "riempire" all'inizio del ciclo while.
    tfobj *o;
    // gestione della posizione del cursore per stampare i syntax error.
    char *token_start = parser.p;
    // prima di tutto si consumano gli spazi vuoti - per fare questo si utilizza una funzione.
    parseSpaces(&parser); // <-- passa come argomento della funzione parserSkipSpaces il puntatore al parser con &parser.
    // avendo "eliminato" gli spazi inizia a ciclare gli altri caratteri per gestirne i vari tipi
    if (parser.p[0] == 0) break; // <-- NULL TERMINATOR. Il programma da compilare ha raggiunto la fine.
    // in questa versione precedente c'è un errore, infatti dobbiamo controllare che IMMEDIATAMENTE dopo il - ci sia un numero, altrimenti è un SYMBOL.
    // if (isdigit(parser.p[0]) || parser.p[0] == '-') {
    if (isdigit(parser.p[0]) || (parser.p[0] == '-' && isdigit(parser.p[1]))) {
      // devo avere una variabile di tipo tfobj per immagazzinare gli int
      o = parseNumber(&parser);
    } else if (is_symbol_char(parser.p[0])) {
      o = parseSymbol(&parser);
    } else {
      o = NULL;
    }
    
    // controlla se il parser verifica l'esistenza di un errore di parsing.
    if (o == NULL) {
      release(parsed);
      // FIX ME: parser.p potrebbe puntare un indirizzo di memoria tale da trovarsi in mezzo ad un numero: 
      //printf("Syntax error near %10s.\n", parser.p);
      printf("Syntax error near %10s.\n", token_start);
      /* N.B. L'errore di sintassi così scritto potrebbe portare a comportamenti imprevisti.
       * parser.p, infatti, come cursore potrebbe capitare in mezzo ad un numero.
       */
    } else {
      // immagazzino i "risultati" del parsing in una lista.
      listPush(parsed, o); // <-- parsed è la lista, o è l'oggetto da inserire.
    }
  } 
  return parsed;
}

/*========================= Execution and context ============================*/

/*
 * Il compilatore traduce il codice sorgente (il "progetto") in istruzioni macchina (l'eseguibile).
 * Non può eseguirle "direttamente" perché ha bisogno di un **Contesto di Esecuzione (Runtime)**.
 * Il Runtime fornisce i servizi dinamici essenziali (memoria, I/O, interazione con il SO)
 * che permettono al programma di interagire con il mondo esterno.
 */

// funzione per creare il contesto di esecuzione 
tfctx *createContext(void) {
  // allochiamo della memoria per creare il contesto
  tfctx *ctx = xmalloc(sizeof(*ctx)); // <-- *ctx deferenzia, quindi il sizeof
                                      //fa riferimento alla dimensione della struct!
  // posso scrivere questa xmalloc anche come xmalloc(sizeof(tfobj)), però
  // così è più comodo: *ctx, significa, significa in questo caso:
  // dammi la dimensione (sizeof) della COSA a cui punta ctx, che è un oggetto di
  // tipo tfctx. tfctx è una struct, quindi alloca il sizeof di una struct tfctx.
  
  // inizializza lo stack, creando come stack un oggetto di tipo lista.
  ctx->stack = createListObject();
  // inizializza il numero di funzioni a 0.
  ctx->functable.func_table = NULL;
  ctx->functable.func_count = 0;
  // registerFunction(ctx,"+", basicMathFunctions);
  return ctx;
}

// funzione per eseguire i simboli
// ritorna true (0) se il sistema trova il simbolo abbinato ad una qualche funzione.
// altrimenti ritorna 1.
// 
/* TODO: completare funzione callSymbol 
int callSymbol(tfctx *ctx, tfobj *word) {
  return 0;
}
*/
// la funzione accetta come argomenti:
// - un programma, ovviamente (prg, che non è altro che una lista salvata nello stack;
// - un contesto di esecuzione (tfctx).
void exec(tfctx *ctx, tfobj *prg) {
  // utilizzo la funzione assert per essere sicuro che il programma sia di tipo LIST.
  assert(prg->type == TFOBJ_TYPE_LIST); 
  // funzione per ciclare all'interno della lista tfobj e recuperare le word.
  // una word è un componente sintattico del programma.
  for (size_t j = 0; j < prg->list.len; j++) {
    tfobj *word = prg->list.ele[j];
    switch (word->type) {
      case TFOBJ_TYPE_SYMBOL:
        // nel caso in cui ci sia un simbolo devo avere una funzione in grado di chiamarlo
        // da chiamare solo quando sarà completa --> callSymbol(ctx, word);
        break;
      default:
        listPush(ctx->stack, word);
        retain(word);
    }
  }
}

/*======================================= Main ============================================*/

// dovremmo leggere un programma passato come stringa tramite argomento argc, ma facciamo il programma più semplice possibile.
int main(int argc, char **argv) {
  // controlliamo che il numero di argomenti sia adeguato, se non lo fosse restituiamo errore
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  // per iniziare a compilare dobbiamo prima aprire il file che ci serve e lo facciamo via fopen
  // ovviamente apriamo il file "contenuto" in argv in sola lettura.
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("Opening Toyforth program\n");
    return 1;
  }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    // torno all'inizio dello stream per leggere tutto il contenuto del file
    fseek(fp, 0, SEEK_SET);
    // creo un puntatore a char per contenere lo stream del programma (il testo)
    // vecchio codice: 
    // char *prgtext; // attenzione: errore, avevo dimenticato di allocare utilizzando la nostra funzione xmalloc (wrapper di malloc)
    // QUESTO CREA UNA SEGMENTATION FAULT! RICORDA SEMPRE DI ALLOCARE MEMORIA QUANDO VUOI SCRIVERE IN UN DETERMINATO INDIRIZZO DI MEMORIA!
    char *prgtext = xmalloc(file_size + 1); // alloco anche lo spazio per il bit relativo al NULL TERM.
    fread(prgtext, file_size, 1, fp);
    prgtext[file_size] = 0; // <-- null term
    tfobj *prg = compile(prgtext);
   
    printObject(prg);
    printf("\n");
    
    // creo il contesto di esecuzione del programma
    tfctx *ctx = createContext();
    // eseguo il programma passando gli argomenti ctx e prg.
    exec(ctx, prg);
    printf("Stack content:");
    printObject(ctx->stack);
    printf("\n");
    fclose(fp);

  // n.b. per eseguire il programma ho bisogno di un contesto di esecuzione del programma.
  return 0;
}
