#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main () {

	int segment_id;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
		
	/* Asignar segmento de memoria compartida. */
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,
	IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	
	/* Adjuntar el segmento de memoria compartida. */
	shared_memory = (char*) shmat (segment_id, 0, 0);
	printf ("shared memory attached at address %p\n", shared_memory);
	
	/* Determinar el tamaño del segmento. */
	shmctl (segment_id, IPC_STAT, &shmbuffer);
	segment_size = shmbuffer.shm_segsz;
	printf ("segment size: %d\n", segment_size);
	
	/* Escribir una cadena al segmento de memoria compartida. */
	sprintf (shared_memory, "Hello, world.");
	
	/* Desadjuntar el segmento de memoria compartida. */
	shmdt (shared_memory);
	
	/* Readjuntar el segmento de memoria compartida, en una dirección distinta. */
	shared_memory = (char*) shmat (segment_id, (void*) 0x5000000, 0);
	printf ("shared memory reattached at address %p\n", shared_memory);
	
	/* Imprimir la cadena de la memoria compartida. */
	printf ("%s\n", shared_memory);
	
	/* Desadjuntar el segmento de memoria compartida. */
	shmdt (shared_memory);
	
	/* Desasignar el segmento de memoria compartida.*/
	shmctl (segment_id, IPC_RMID, 0);

	return 0;
}
