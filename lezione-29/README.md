# Lezione 27 - scriviamo l'interprete Toyforth - parte dalla lezione 23 e continua
Video di riferimento pt.1: https://www.youtube.com/watch?v=vYODKK8TQGE
Video di riferimento pt.2: https://www.youtube.com/watch?v=-QxrmHo-V7Y 
Video di riferimento pt.3: https://www.youtube.com/watch?v=-1ZhCgaIPOk
Video di riferimento pt.4: https://www.youtube.com/watch?v=oMj3N6jYIUU
Video di riferimento pt.5: https://www.youtube.com/watch?v=C4AHEK3fSjg
Video di riferimento pt.6: https://www.youtube.com/watch?v=nHzlRqPnlrE

Toyforth è un interprete "giocattolo", scritto in C, per il linguaggio FORTH. Il linguaggio FORTH è un linguaggio di programmazione basato sullo stack.

Riporto un esempio di linguaggio FORTH:

```forth
: FLOOR5 ( n -- n' )   DUP 6 < IF DROP 5 ELSE 1 - THEN ;
```
Questo tipo di progetto permette la prima full immersion nel linguaggio C, sfruttando, di fatto, tutti i concetti appresi finora nel corso C di Salvatore.
