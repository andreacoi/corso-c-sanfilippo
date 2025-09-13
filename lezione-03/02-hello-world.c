#include <stdio.h>

// dichiaro, come già fatto nel programma hello-world.c la funzione void
// incr(void)

void incr(void) {
  // per dichiarare una variabile static utilizzo la keyword static
  static int x = 0;

  x = x + 1;

  printf("%d\n", x);

  // la parola chiave static (Deitel la definisce "specificatore di classe di
  // memoria") permette di restringere il campo di azione della variabile x solo
  // alla funzione entro la quale viene definita.
  // Questo viene definito COLLEGAMENTO INTERNO. Se invece una variabile viene
  // dichiarata esplicitamente come globale, si parlerà di COLLEGAMENTO ESTERNO.
  // rif. DEITEL pag. 618 par. 5.4.3
  //
  // Salvatore inoltre fornisce una bellissima definizione. La variabile con
  // static è globale dal punto di vista della lifetime, del suo ciclo di vita,
  // ma non lo è dal punto di vista della sua visibilità.
}

int main(void) {
  incr();
  // provando a "chiamare direttamente" x dentro il main questo genererà un
  // errore.
  return 0;
}
