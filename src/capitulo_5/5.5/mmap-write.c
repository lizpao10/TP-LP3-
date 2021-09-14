#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

/* Retorna un número uniformemente aleatorio en el rango [low,high]. */
int random_range (unsigned const low, unsigned const high) {
	
	unsigned const range = high - low + 1;
	
	return low + (int) (((double) range) * rand () / (RAND_MAX + 1.0));
}

int main (int argc, char* const argv[]) {
	
	int fd;
	void* file_memory;
	
	/* Semilla para el generador de número aleatorio.*/
	srand  (time (NULL));
	
	/* Prepara un archivo suficientemente grande para mantener un entero sin signo.*/
	fd = open (argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	lseek (fd, FILE_LENGTH+1, SEEK_SET);
	write (fd, "test", 1);
	lseek (fd, 0, SEEK_SET);
	
	/* Crear el mapeo de memoria. */
	file_memory = mmap (0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);
	close (fd);
	
	/* Escribe un entero aleatorio en un área de memoria mapeada. */
	sprintf((char*) file_memory, "%d\n", random_range (-100, 100));
	
	/* Liberar la memoria (innecesario porque el programa finaliza). */
	munmap (file_memory, FILE_LENGTH);
	
	return 0;
}
