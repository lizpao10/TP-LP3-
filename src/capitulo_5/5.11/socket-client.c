#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* Escribe TEXT al socket dado por el descriptor de archivo SOCKET_FD. */
void write_text (int socket_fd, const char* text) {
	
	/* Escribe el número de bytes en la cadena, incluendo terminación NUL. */
	int length = strlen (text) + 1;
	write (socket_fd, &length, sizeof (length));
	
	/* Escribe la cadena. */
	write (socket_fd, text, length);
}

int main (int argc, char* const argv[]) {
	
	const char* const socket_name = argv[1];
	const char* const message = argv[2];
	int socket_fd;
	struct sockaddr_un name;
	
	/* Crear el socket. */
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	
	/* Guardar el nombre del servidor en la dirección del socket. */
	name.sun_family = AF_LOCAL;
	strcpy (name.sun_path, socket_name);
	
	/* Conectar el socket. */
	connect (socket_fd, &name, SUN_LEN (&name));
	
	/* Escribir el texto en la línea de comando al socket. */
	write_text (socket_fd, message);
	close (socket_fd);
	
	return 0;
}
