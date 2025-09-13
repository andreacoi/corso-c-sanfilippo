#include <stdio.h>

int main(void) {
  // gli array in C, si indicano come:
  int a[5] = {1,2,3,4,5};
  // a[5] è il numero di valori presenti nell'array.
  printf("%d\n", a[0]);
  // in C le stringhe sono viste come array di char. Es. 
  char str[6] = {'h', 'e', 'l', 'l','o', 0 };
  // stampando str, passando a printf %s ottengo, infatti, la stringa completa "hello". Lo 0 vale come terminatore di riga nul.
  // Oltre ai benefici derivanti dall'inserimento del terminatore di linea, è anche salvifico inserirlo perché i comportamenti dovuti al mancato inserimento potrebbero essere "strani".
  printf("%s\n", str);
  
  // test personale che esula dal video 
  char nome[] = "Andrea";
  printf("%c\n", nome[2]);
  // in questo esempio ho provato a dichiarare una stringa (espressa come un array di char) e ad accedere alle lettere di quella stringa tramite una printf con %c, passando come argomento l'indice dell'array alla lettera che volevo stampare.
  // In questo specifico caso la 'd'.
  // !! IMPORTANTE !!  Nonostante tutto questo, non bisogna dimenticare mai che le stringhe in C sono SEMPRE array di numeri! !! IMPORTANTE !!
  return 0;
}
