#include <stdio.h>

int main(void) {
  int a = 10;
  short s = 400;
  float y = 1.234;
  printf("%d %.3f \n", s, y);
  // le funzioni variadiche come la printf (che eseguono il parse degli
  // argomenti a runtime, sulla base di quanti ne sono citati nel codice) non
  // possono implementare diversi modi di mostrare le diverse variabili. Per
  // cui, il C in maniera automatica esegue le cosidette PROMOZIONI DI TIPO.
  // Passando s alla printf, che come primo argomento accetta %d, viene eseguita
  // automaticamente una "promozione" di s da short a int.
  // Per quanto riguarda i float invece, quando sono argomenti di funzioni
  // variadiche, vengono promossi automaticamente a double.
  //
  // questo succede anche in casi particolari tipo:
  char c = 127;
  // anche se si potrebbe essere portati a pensare che la seguente espressione
  // possa generare UGUALMENTE UN WARNING, così non è perché C esegue
  // automaticamente un cast da char a int.
  int i = c + 1;
  printf("%d\n", i);
  // uscendo FUORI dal valore massimo permesso dalla char -il cosiddetto
  // overflow- (-128, 127), il C va ad eseguire quella che si chiama conversione
  // implicita e va a convertire 128 in -128. k
  // Questo tipo di conversione (che è comunque sconsigliata) è possibile solo
  // negli interi con segno. Negli interi senza segno ci troveremmo di fronte ad
  // un UB (undefined behaviour).

  unsigned char uc = 254;
  uc++;
  printf("%d\n", uc);
  uc++;
  printf("%d\n", uc);
  // in questo specifico caso, utilizzando gli unsigned vado a guadagnare uno
  // "spazio" aggiuntivo nei numeri: quindi ho spazio fino a 254. Attenzione
  // però! quando vado a fare un incremento ottengo 0. Sintetizzando: Essendo su
  // 254 e incrementando di 1, supero lo spazio, e il programma mi mostra 0. È
  // come se "ricominciasse" da capo.
  uc++;
  printf("%d\n", uc);

  return 0;
}
