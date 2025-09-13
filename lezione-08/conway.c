#include <stdio.h>
#include <unistd.h>

// non avendo ancora "studiato" le struct e i define utilizzeremo delle variabili globali per definire la griglia
// le variabili saranno scritte in modalità Capitalize

// utilizzo define per definire le costanti sempre valide per il gioco
// #define crea costanti simboliche e macro (definizione a pag. 601 di Harvey/Deitel) che non vengono associate, bensì SOSTITUITE. N.B. non bisogna utilizzare l'operatore di uguale.


// costante per le colonne
#define GRID_COLS 20
// costante per le righe
#define GRID_ROWS 20
// costante calcolata per ottenere il numero di celle
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
// costante per il carattere di MORTO
#define DEAD '.'
// costante per il carattere di VIVO
#define ALIVE '*'

// sarebbe utile avere anche una funzione in grado di tradurre dei valori negativi di x e di y in valori validi della griglia (riferimento a partire da destra, o dal basso nel caso della y)
// es. se x = -1 e y = -1, è come se fosse (prendo per esempio una griglia 3x3) x = 9 e y = 9. Questo tipo di ragionamento si chiama in gergo wrap around.

// funzione per implementare il wrap around
int cell_to_index (int x, int y) {
	// se il numero di colonne supera 25 (in questo caso), utilizza modulo (%) per ottenere la x relativa al numero di volte che la x è contenuta in GRID_COLS.
	if (x >= GRID_COLS) x = x % GRID_COLS;
	// lo stesso ragionamento vale per la y.
	if (y >= GRID_ROWS) y = y % GRID_ROWS;
	// adesso devo gestire il negativo
	if (x < 0) {
		// normalizzo x, facendola diventare positiva, faccio la classica operazione di modulo e poi sottraggo alla nuova x il valore di GRID_COLS. Lo stesso ragionamento vale per la y.
		x = (-x) % GRID_COLS;
		x = GRID_COLS - x;	
	}
	if (y < 0) {
		y = (-y) % GRID_ROWS;
		y = GRID_ROWS - y;	
	}
	return y * GRID_COLS + x;
}

// abbiamo bisogno di una funzione per "accendere" una celletta sulla griglia

// funzione per accendere una determinata celletta x, y, con un determinato stato sulla griglia
// anche se non abbiamo ancora affrontato l'argomento dei puntatori, in questa funzione abbiamo necessariamente bisogno di utilizzarli perché dobbiamo passare grid PER RIFERIMENTO anziché PER VALORE.
// Questo perché dobbiamo mantenere "lo stato" della griglia.
void set_cell(char *grid, int x, int y, int state) {
	// significato di questa espressione
	// moltiplicando y per il totale delle colonne ottengo il punto sulle ordinate dove collocare il punto.
	// SOMMANDO x a questo valore ottengo il valore di offset dove collocare il punto preciso (pensa a una griglia 3x3 e fai questa operazione su una griglia 3x3 per avere un riferimento reale.	
	grid[cell_to_index(x, y)] = state; 
}

// funzione per ottenere lo stato attuale di una determinata cella (inversa di setcell)
char get_cell(char *grid, int x, int y) {
	return grid[cell_to_index(x, y)];
}


// funzione per stampare la griglia a schermo utilizzando il comando VT100 richiesto da terminale.
void print_grid(char *grid) {
	// sequenza di escape per cancellare lo schermo, ottenuta via: clear | hexdump -C
	// ai punti bisogna sostituire 0x1b, dove lo 0 viene indicato con il backslash.
	printf("\x1b[H\x1b[2J\x1b[3J");
	for (int y = 0; y < GRID_ROWS; y++) {
		for (int x = 0; x < GRID_COLS; x++) {
			printf("%c", get_cell(grid, x, y));
		}
		printf("\n");
	}
} 

void set_grid(char *grid, char state) {
	for (int y = 0; y < GRID_ROWS; y++) {
		for (int x = 0; x < GRID_COLS; x++) {
			set_cell(grid, x, y, state);
		}
	}

}

// funzione per contare i vicini vivi
int count_living_neighbors(char *grid, int x, int y) {
	int alive = 0;
	// dovendo inizializzare y e x all'interno dei due cicli for annidati, ed essendo x e y variabili locali della funzione, uso yo (y offset) e xo (x offset) per i due cicli.
	for (int yo = -1; yo<=1; yo++) {
		for (int xo = -1; xo<=1; xo++) {
			// escludo la cella corrente
			if (xo == 0 && yo == 0) continue;
			if (get_cell(grid, x+xo, y+yo) == ALIVE)  alive++;
		}
	}
	return alive;
}

// funzione per il cambio di stato
void compute_new_state(char *old, char *new) {
	for (int y = 0; y < GRID_ROWS; y++) {
		for (int x = 0; x < GRID_COLS; x++) {
			// calcola i vicini vivi
			int n_alive = count_living_neighbors(old, x, y);  
			int new_state = DEAD;
			if (get_cell(old, x, y) == ALIVE) {
				if (n_alive == 2 || n_alive == 3) {
					new_state = ALIVE;
				}
			} else {
				if (n_alive == 3) {
					new_state = ALIVE;
				}
			}
			set_cell(new, x, y, new_state);

		}

	}
}

int main(void) {
	// per iniziare a giocare abbiamo bisogno di una griglia 25*25
	char old_grid[GRID_CELLS];
	char new_grid[GRID_CELLS];
	set_grid(old_grid, DEAD);
	set_cell(old_grid, 10, 10, ALIVE);
	set_cell(old_grid, 9, 10, ALIVE);
	set_cell(old_grid, 11, 10, ALIVE);
	set_cell(old_grid, 11, 9, ALIVE);
	set_cell(old_grid, 10, 8, ALIVE);
	while (1) {
		compute_new_state(old_grid, new_grid);
		print_grid(new_grid);
		usleep(100000);
		compute_new_state(new_grid, old_grid);
		print_grid(old_grid);
		usleep(100000);
	}

}
