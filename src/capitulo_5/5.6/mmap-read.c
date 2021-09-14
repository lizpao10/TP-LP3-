#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

int main (int argc, char* const argv[]) {
	
	int fd;
	void* file_memory;
	int integer;
	
	/* Abre el archivo. */
	fd = open (argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	
	/* Crear el mapeo de memoria. */
	file_memory = mmap (0, FILE_LENGTH, PROT_READ | PROT_WRITE,
	MAP_SHARED, fd, 0);
	close (fd);
	
	/* Leer el entero, imprimirlo y doblarlo. */
	scanf (file_memory, "%d", &integer);
	printf ("value: %d\n", integer);
	sprintf ((char*) file_memory, "%d\n", 2 * integer);
	
	/* Liberar la memoria (innecesario porque el programa finaliza).*/
	munmap (file_memory, FILE_LENGTH);
	
	return 0;
}
