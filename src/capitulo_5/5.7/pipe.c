#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* Escribe COUNT copias de MESSAGE a STREAM, pausando 1 segundo entre cada. */
void writer (const char* message, int count, FILE* stream) {
	
	for (; count > 0; --count) {
		
		/* Escribir un mensaje al canal, y enviarlo inmediatamente.*/
		fprintf (stream, "%s\n", message);
		fflush (stream);
		
		/* Duerme un rato. */
		sleep (1);
	}
}

/* Leer cadenas aleatorias desde el canal tanto como sea posible. */
void reader (FILE* stream) {
	
	char buffer[1024];
	
	/* Leer hasta que lleguemos al final del canal. fgets lee hasta una línea nueva o final de archivo. */
	while (!feof (stream)
		
		&& !ferror (stream)
		&& fgets (buffer, sizeof (buffer), stream) != NULL)
	fputs (buffer, stdout);
}

int main () {
	
	int fds[2];
	pid_t pid;
	
	/* Crea un conducto. Descriptores de archivo para ambos extremos del conducto son asignados en fds. */
	pipe (fds);
	
	/* Bifurca un proceso hijo. */
	pid = fork ();
	if (pid == (pid_t) 0) {
		
		FILE* stream;
		
		/* Este es el proceso hijo. Cierra nuestra copia de fin de escritura del descriptor de archivo. */
		close (fds[1]);
		
		/* Convierte el descriptor de leer archivo a un objeto FILE, y lee al mismo. */
		stream = fdopen (fds[0], "r");
		reader (stream);
		close (fds[0]);
	} else {
		
		/* Este es el proceso padre. */
		FILE* stream;
		
		/* Cierra nuestra copia de fin de leectura del descriptor de archivo. */
		close (fds[0]);
		
		/* Convierte el descriptor de escribir archivo a un objeto FILE, y escribe en el mismo. */
		stream = fdopen (fds[1], "w");
		writer ("Hello, world.", 5, stream);
		close (fds[1]);
	}
	
	return 0;
}
