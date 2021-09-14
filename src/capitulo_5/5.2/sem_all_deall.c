#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <semaphore.h>

/* Nosotros debemos definir union semun. */
union semun {
	
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

/* Obtener ID de un semáforo binario, asignando si es necesario. */
int binary_semaphore_allocation (key_t key, int sem_flags) {
	
	return semget (key, 1, sem_flags);
}

/* Desasignar un semáforo binario. Todos los usuarios deben haber finalizado su uso. Retorna -1 si falla. */
int binary_semaphore_deallocate (int semid) {
	
	union semun ignored_argument;
	
	return semctl (semid, 1, IPC_RMID, ignored_argument);
}

int main() {
	
	key_t key;
	int id = binary_semaphore_allocation(key, 2);
	binary_semaphore_deallocate(id);
}
