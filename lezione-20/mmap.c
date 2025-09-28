/* 
 * Nella stessa lezione 20, Salvatore tratta la mmap.
 * In particolare è possibile immagazzinare il contenuto di un file all'interno di un pezzetto di memoria.
 * Questa tecnica si chiama Memory Mapping. Ed è implementata tramite la chiamata di sistema POSIX mmap.
 * Vedi man mmap!
 * 
*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void) {
  int fd = open("mmap.c", O_RDONLY);
  // il descrittore è sempre 3 perché i primi 3 sono:
  // 0 - STDIN
  // 1 - STDOUT
  // 2 - STDERR
  printf("File: %d\n", fd);
  void *mem = mmap(NULL,100, PROT_READ, MAP_FILE|MAP_SHARED, fd,0);
  // una volta mappato il file in memoria lo posso gestire come se fosse un puntatore
  char *s = mem;
  for (int j = 0; j < 10; j++) {
    printf("s[%d]: %c\n", j, s[j]);
  }
  // n.b. L'utilizzo accorto di mmap consente di scrivere i programmi più veloci possibile con accesso ai file.
  return 0;
}
