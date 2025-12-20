# Un makefile è un file che dichiara le procedure necessarie ad avere un file 
# in C compilato ed eseguibile, senza stare a scrivere ogni volta la sintassi
# per compilare.
# È composto di un target "all" e delle istruzioni per gestire questo target.
# all non è speciale, il target di default di make per convenzione è quello 
# ed è il primo target nel file. Potrei anche scrivere pippo e il makefile 
# funzionerebbe comunque.

all: toyforth

# vado a definire cosa deve fare il programma con il mio target toyforth
toyforth: toyforth.c #definisco il file che deve essere trattato
					$(CC) toyforth.c -Wall -W -O2 -o toyforth

# target per pulire il binario precedentemente compilato
clean: 
		rm -rf toyforth
