# Lezione 23 - scriviamo l'interprete Toyforth
Video di riferimento: https://www.youtube.com/watch?v=vYODKK8TQGE

Toyforth è un interprete "giocattolo", scritto in C, per il linguaggio FORTH.

Riporto un esempio di linguaggio FORTH:

```forth
: FLOOR5 ( n -- n' )   DUP 6 < IF DROP 5 ELSE 1 - THEN ;
```
Questo tipo di progetto permette la prima full immersion nel linguaggio C, sfruttando, di fatto, tutti i concetti appresi finora nel corso C di Salvatore.
