#include <stdio.h>

int main(void) {
	int i = 10;
	// il costrutto switch è identico a JS e a PHP, non necessita di particolari approfondimenti...
	switch(i) {
		case 5: printf("È un cinque\n");break;	
		case 7: printf("È un sette\n");break;
		case 10: printf("È un dieci\n");break;	
		default: printf("Qualche altro numero...\n");break;
	}
	return 0;
}
