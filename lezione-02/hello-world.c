#include <stdio.h>

int sum(int a, int b) {
  int c = a + b;
  return c;
}

int main() {
  printf("Hello, World! %d\n", sum(2, 3));
  return 0;
}

// appunti sulla funzione:
// la keyword int indica che la funzione deve restituire un valore intero.
//
// appunti sulla compilazione:
// Sanfilippo nel video prova a compilare il codice SENZA specificare alcun
// argomento nella funzione main e rimuove anche la keyword void. Per verificare
// se il programma è ancora compilabile lancia cc con i flag -W -Wall
// Un altro avvertimento è quello di scrivere sempre i nomi delle funzioni in
// lingua inglese, ovviamente è una scelta libera ma è una buona pratica.
// piccola nota sulla printf
// printf è una funzione che stampa a schermo ed è l'abbreviazione di "print
// formatted".
// Altro appunto:
// IL C NON ESEGUE INFERENZA DI TIPO. Per cui, bisogna sempre specificare i tipi
// delle funzioni che si vanno a dichiarare.
// Scope delle variabili:
// La variabile c è locale ed è definita solo all'interno della funzione sum.
//
// differenze di dichiarazione tra il K&R e il video di Sanfilippo:
// Nel video Salvatore utilizza la funzione main con un valore di ritorno int,
// mentre il testo la dichiara senza. Salvatore inoltre spiega che è sempre
// buona prassi specificare il tipo di ritorno per far sapere al sistema se
// l'esecuzione è andata a buon fine o meno.
// Nella shell UNIX è possibile mostrare il valore di ritorno della funzione
// main in questo modo:
// ./a.out;echo $?
// Nel caso in cui si esegua una concatenazione di comandi con && il valore di
// ritorno derivante dall'esecuzione del comando precedente influenzerà
// l'esecuzione del comando successivo. Quindi, in soldoni, se il programma
// termina con 0 (codice di successo) il comando successivo verrà eseguito,
// altrimenti no.
// APPENDICE
// lo stack
// Descrizione dello stack pointer:
// Lo stack pointer è un registro che punta all'ultima posizione dello stack.
// Nel video appendice Salvatore mostri le variazioni di posizione dello stack
// pointer e come la memoria viene allocata per le variabili locali.
