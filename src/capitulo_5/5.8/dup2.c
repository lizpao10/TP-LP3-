#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
	
	int fds[2];
	pid_t pid;
	
	/* Crea un conducto. Descriptores de archivo para ambos extremos del conducto son asignados en fds. */
	pipe (fds);
	
	/* Bifurca un proceso hijo. */
	pid = fork ();
	if (pid == (pid_t) 0) {
		
		/* Este es el proceso hijo. Cierra nuestra copia de fin de escritura del descriptor de archivo. */
		
		close (fds[1]);
		/* Conecta el fin de lectura del conducto a la entrada estándar. */
		
		dup2 (fds[0], STDIN_FILENO);
		
		/* Reemplaza el proceso hijo con el programa "sort". */
		execlp ("sort", "sort", 0);
	} else {
		
		/* Este es el proceso padre. */
		FILE* stream;
		

		/* Cierra nuestra copia de fin de lectura del descriptor de archivo. */
		close (fds[0]);
		
		/* Convierte el descriptor de escritura de archivo a un objeto FILE, y escribe en él. */
		stream = fdopen (fds[1], "w");
		fprintf (stream, "This is a test.\n");
		fprintf (stream, "Hello, world.\n");
		fprintf (stream, "My dog has fleas.\n");
		fprintf (stream, "This program is great.\n");
		fprintf (stream, "One fish, two fish.\n");
		fflush (stream);
		close (fds[1]);
		
		/* Wait for the child process to finish. */
		waitpid (pid, NULL, 0);
	}
	
	return 0;
}
