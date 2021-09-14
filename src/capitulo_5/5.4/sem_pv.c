#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
	
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

/* Esperar en un semáforo binario. Bloquear hasta que el valor del semáforo sea positivo, entonces decrementarlo en 1. */
int binary_semaphore_wait (int semid) {
	
	struct sembuf operations[1];
	
	/* Usa el primer (y único) semáforo.*/
	operations[0].sem_num = 0;
	
	/* Decrementa en 1. */
	operations[0].sem_op = -1;
	
	/* Permite deshacer. */
	operations[0].sem_flg = SEM_UNDO;
	
	return semop (semid, operations, 1);
}

/* Enviar a un semáforo binario: incrementar su valor en 1. Esto retorna de inmediato. */
int binary_semaphore_post (int semid) {
	
	struct sembuf operations[1];
	
	/* Usa el primer (y único) semáforo.*/
	operations[0].sem_num = 0;
	
	/* Incrementa en 1. */
	operations[0].sem_op = 1;
		
	/* Permite deshacer. */
	operations[0].sem_flg = SEM_UNDO;
	
	return semop (semid, operations, 1);
}

int binary_semaphore_initialize (int semid) {
	
	union semun argument;
	unsigned short values[1];
	values[0] = 1;
	argument.array = values;
	
	return semctl (semid, 0, SETALL, argument);
}

int binary_semaphore_allocation (key_t key, int sem_flags) {
	
	return semget (key, 1, sem_flags);
}

/* Desasignar un semáforo binario. Todos los usuarios deben haber terminado su uso. Retorna -1 si falla. */
int binary_semaphore_deallocate (int semid) {
	
	union semun ignored_argument;
	
	return semctl (semid, 1, IPC_RMID, ignored_argument);
}


int main() {
	
	key_t key;
	int id = binary_semaphore_allocation(key, 2);
	binary_semaphore_initialize(id);
	binary_semaphore_wait(id);
	binary_semaphore_post (id);
	binary_semaphore_deallocate(id);
}
