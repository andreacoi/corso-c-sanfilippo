#include <stdio.h>

typedef int errorcode;
/* typedef è una definizione di un tipo "sovrascrivendo il tipo stesso". 
*/
// se ho una funzione che si occupa di ritornare dei codici di errore:
// posso sostituire a int la parola errorcode che indica, tramite typedef, che si tratta di un tipo intero che esprime un codice errore:
// errorcode error(void) {
//  return -20;
// }

errorcode error(void) {
  return -20;
}

// questo tipo di proprietà del linguaggio è valida a maggior ragione con le struct che sono tipi di dato complessi, mentre secondo Salvatore ha poco senso con le int.
// puntualizzando ancora di più la definizione questa struct è come se "smettesse" di essere una STRUCT IN CHIARO e diventasse una variabile di tipo fract. Si dice che fract "rende opaca la struct.
// Da Deitel&Deitel pag. 429
// La parola chiave typedef consente di creare SINONIMI o ALIAS per tipi di dati PRECEDENTEMENTE DEFINITI.
// Utilizzo: viene comunemente utilizzata per creare NOMI PIÙ CORTI per i tipi di strutture e per semplificare le dichiarazioni di tipi quali i puntatori a funzioni. Per convenzione i SINONIMI e GLI ALIAS si scrivono con la lettera MAIUSCOLA.
// IMPORTANTE! Creare un nome nuovo con typedef NON CREA UN NUOVO TIPO; typedef CREA UN NUOVO NOME DI TIPO, che può essere usato come ALIAS per un nome di tipo esistente.
// vedi anche pagg. 146-147 manuale K&R.
typedef struct {
  int a;
  int b;
} fract;

// un altro modo di utilizzare type def è dichiarando un puntatore
typedef fract *fractptr;

int main(void) {
  fract f;
  fractptr fp = &f;
  // attenzione! qui non metto l'asterisco perché l'ho già dichiarato come puntatore nella typedef. Se lo mettessi anche qui, è come se facessi un puntatore di puntatore.
  f.a = 10;
  f.b = 20;
  printf("%d/%d. f is stored at %p\n",f.a, f.b, fp);
}
