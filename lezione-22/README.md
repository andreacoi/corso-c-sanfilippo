# Lezione 22 - I puntatori a funzione 
Video di riferimento: https://www.youtube.com/watch?v=OIseV5lcx8w

## Cos'è un puntatore a funzione
Il nome della funzione è in realtà l'**indirizzo di memoria di partenza del codice che esegue il compito della funzione**. I puntatori a funzioni possono essere passati alle funzioni, restituiti dalle funzioni, memorizzati negli array, assegnati ad altri puntatori a funzioni e confrontati per uguaglianza e diseguaglianza tra loro. (D&D pag. 302).

## Perché un puntatore a funzione
Un puntatore a funzione in C serve per trattare una funzione come se fosse un dato, cioè come qualcosa che puoi passare, salvare o cambiare a runtime, invece di scrivere direttamente il nome della funzione nel codice.

Ecco i motivi principali, spiegati in modo semplice:

🎛️ Flessibilità — Ti permette di scegliere quale funzione eseguire mentre il programma sta girando, invece di decidere tutto in anticipo. È utile quando hai più funzioni simili e vuoi selezionare quella giusta in base a una condizione.

🧩 Modularità — Ti aiuta a separare la logica del “cosa fare” dal “come farlo”. Ad esempio, un algoritmo può ricevere una funzione come “comportamento” da applicare, senza sapere in anticipo quale.

🔁 Generalizzazione — Puoi scrivere funzioni generiche che lavorano con funzioni diverse. Per esempio, un ciclo che elabora dati può usare un puntatore a funzione per sapere come elaborarli, senza dover riscrivere tutto ogni volta.

⚙️ Callback — Ti consente di impostare funzioni di richiamo: cioè dire al programma “quando succede X, esegui questa funzione”. È una base per concetti come gli eventi o le interfacce.

In breve:
👉 Un puntatore a funzione serve a rendere il codice più flessibile e riutilizzabile, permettendo di scegliere dinamicamente quale funzione eseguire. (ChatGPT).
