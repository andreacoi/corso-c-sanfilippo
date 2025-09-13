#include <stdio.h>
#include <stdlib.h>

/* Appunto sul programma struct2.c 
 * Per realizzare il programma struct2.c e le sue funzioni abbiamo utilizzato un puntatore e malloc.
 * Avendo una STRUTTURA BEN DEFINITA possiamo riscrivere le funzioni del programma utilizzando la struct.
 * Le strutture (struct) sono *tipi di dati derivati*, essendo costruite usando oggetti di altri tipi.
 * Definizione a pag.424 di Deitel&Deitel
 *
 */

// es. 
struct fract {
	int numeratore;
	int denominatore;
};
// in questo modo ho creato una struct che raccoglie i due tipi primitivi int e li chiama rispettivamente numeratore e denominatore.
// Le etichette della struct devono essere uniche (frac), mentre i suoi membri possono avere anche stessi nomi tra struct diverse.
// N.B. Le STRUCT sono L'UNICO CASO IN CUI IL C ESCE FUORI DALL'IDEA DI MANIPOLARE NUMERI.
//
int main(void) {
  // il sizeof di una struct ti garantisce che ogni membro della struct sia registrato a un indirizzo di memoria che è multiplo della sua dimensione.
  // Cosa implica questo?
  // Questo implica che se dovessi utilizzare un char (es. colore) come membro della struct, non avrei 9 byte, bensì 12. Perché la char è grande sì un byte ma
  // occupa 3 byte di padding a livello di indirizzo di memoria
  /*
   * + ---- + ---- + ---- +
   * | cPPP | num  | den  |
   * + ---- | ---- | ---- |
   * dove P è la rappresentazione del padding nell'allocazione di memoria.
   * N.B. La struttura, anche variando la posizione del char (dichiarandolo, ad esempio, per ultimo nella struct) non cambia di dimensione, anche potendo gestire gli
   * offset dei due int. La sua dimensione sarà sempre e comunque 12.
   * Questo perché la struct "impila" le variabili conferendo alla variabile "più piccola" la stessa ampiezza della variabile più grande presente nella struct (in questo caso int).
   */
  // per utilizzare una struct la si dichiara così:
  struct fract a;
  // dove struct è il tipo, fract è il nome della struct a cui si intende fare riferimento e a è il nome che che gli diamo nel programma.
  // e per accedere agli elementi si fa così:
  a.numeratore = 1;
  a.denominatore = 2;
  // nel caso in cui si usi un puntatore a una struct si usa la freccia per accedere agli elementi
  struct fract *b = &a;
  b->numeratore = 1;
  b->denominatore = 2;
  /*
   * Perché si usa la freccia e non il punto? Il compilatore non dovrebbe sapere automaticamente che si tratta di una struct?
   * I motivi sono storici e sono altresì dovuti all'esplicitezza del linguaggio C.
   * Infatti, il programmatore vedendo una freccia, capisce automaticamente che si sta parlando di un puntatore a una struct.
   * */
  printf("%d %d\n", a.numeratore, a.denominatore);
  return 0;
}

#if 0
appunto al minuto 16:57 
Questa è un`istruzione inviata al preprocessore e serve per commentare un bel blocco di codice 
# endif
