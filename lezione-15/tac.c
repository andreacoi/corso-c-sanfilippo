#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Concetti chiave: apertura di file e argomenti della funzione main:
// - argc
// - argv
//
// creo la struct che mi servirà per implementare la linked list.
// Una struct per implementare la linked list ha sicuramente almeno due membri:
// - un valore
// - il puntatore alla "prossima" struct che la struttura della struct stessa:

struct line {
  char *s;
  struct line *next; 
};

int main(int argc, char **argv) {
  // abbiamo necessariamente bisogno di due argomenti:
  // 1 è il nome del programma che viene eseguito
  // 2 è il nome del file che dobbiamo passare al programma
  // se manca il secondo argomento devo ritornare un errore perché manca il nome del file da leggere.
  if (argc != 2) {
    printf("Manca l'argomento nomefile.\n");
    return 1;
  }
  // un file si apre in questo modo:
  FILE *fp = fopen(argv[1], "r");
  
  // il primo argomento è un puntatore a caratteri (una stringa che indica il path, il secondo, anch'esso un puntatore a caratteri
  // indica invece la modalità di accesso al file. Nel nostro caso il path è il primo argv passato al programma.
  // In questo specifico caso il file viene aperto in sola-lettura "r".
  // Dopo aver terminato le operazioni devo chiamare fclose per chiudere il file.
  
  // verifico che il file esista e se non esiste ritorno 1 come indicazione dell'errore.
  if (fp == NULL) {
    printf("Il file non esiste.\n");
    return 1;
  }
  // per leggere il contenuto di un file si usa la chiamata di libreria C fgets()
  // fgets accetta come argomenti:
  // - un array di caratteri di dimensione prefissata;
  // - un int che specifica la dimensione dell'array
  // - un puntatore a FILE
  // cfr. man fgets
  char buf[1024];
  // creo una struct appositamente per la testa del file
  struct line *head = NULL;
  int size = sizeof(buf);
  while (fgets(buf, size, fp) != NULL) {
    // alloco memoria facendola puntare al puntatore l.
    struct line *l = malloc(sizeof(struct line)); 
    // uso la freccia perché si tratta di un puntatore a una struct
    // uso nuovamente malloc per allocare la memoria necessaria a buf, non potendo "conoscerla prima", uso strlen per calcolarla.
    // aggiungo +1 perché è presente il terminatore a NULL.
    size_t linelen = strlen(buf); 
    l->s = malloc(linelen + 1);
    // inizio il ciclo for per "copiare" ciascuna riga del file all'interno di buf.
    for (size_t j = 0; j <= linelen; j++) {
      // con questa espressione ho eseguito una copia senza utilizzare memcpy.
      l->s[j] = buf[j];
    }
    l->next = head;
    head = l;
    }
    fclose(fp);
    // adesso devo stampare le linee immagazzinate al contrario:
    while(head != NULL) {
      // a QUELL'INDIRIZZO DI MEMORIA, VAMMI A PRENDERE IL CONTENUTO, RISALENDO TRA GLI INDIRIZZI DI MEMORIA.
      printf("%s", head->s);
      // dopo l'esecuzione punta al prossimo indirizzo di memoria:
      head = head->next;
    }
    // printf("%s", buf);
    // a questo punto abbiamo scritto un rudimentale cat però dobbiamo invertire l'output per ottenere tac.
    // Per fare ciò abbiamo bisogno di implementare quella che si chiama una linked list.
    // DIFFERENZA TRA ARRAY E LINKED LIST
    // Con gli array hai una fila fissa di sedie: non puoi aggiungerne facilmente nel mezzo.
    // Con la linked list puoi infilare una persona nuova in mezzo, basta “cambiare i puntatori” (il dito che indica il prossimo).
    // 👉 Quindi l’astrazione mentale è:
    // Ogni struct è un contenitore che sa due cose: il suo dato e dove trovare il prossimo contenitore. Tutti collegati, formano una catena dinamica.
}
