# Lezione 8 - Implementiamo il Conway's Game of life
Video di riferimento: https://www.youtube.com/watch?v=c5atNuYdKK8&list=PLrEMgOSrS_3cFJpM2gdw8EGFyRBZOyAKY&index=9

In questa lezione si implementa il Gioco della Vita di Conway: https://it.wikipedia.org/wiki/Gioco_della_vita

L'obiettivo formativo di questa lezione è capire come scomporre il problema in sottoproblemi più piccoli e gestibili. In particolare, si apprenderà l'uso di funzioni scritte ad hoc per far compiere al nostro programma i task separati che servono per l'implementazione completa del gioco di Conway.

## Riferimenti
Il gioco di Conway sfrutta i concetti di:
- Turing equivalenza --> https://it.wikipedia.org/wiki/Turing_equivalenza
- Moore neighborhood (vicinanza di Moore) --> https://en.wikipedia.org/wiki/Moore_neighborhood

## "Regole" del gioco
- Qualsiasi cella viva con meno di due celle vive adiacenti muore, come per effetto d'isolamento;
- Qualsiasi cella viva con due o tre celle vive adiacenti sopravvive alla generazione successiva;
- Qualsiasi cella viva con più di tre celle vive adiacenti muore, come per effetto di sovrappopolazione;
- Qualsiasi cella morta con esattamente tre celle vive adiacenti diventa una cella viva, come per effetto di riproduzione.

## Modalità pratiche di implementazione
Trattandosi di un linguaggio "a basso livello", scriveremo delle funzioni per "alzarci" di livello (astrazione) e lavorando con queste funzioni andremo a costruire il nostro programma "a castello". In sostanza, il programma è strutturato "a livelli".

