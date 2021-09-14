#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* Lee texto del socket y lo imprime. Continúa hasta que el socket cierre. Retorna no nulo si el cliente envió un mensaje "quit", sino un cero. */

int server (int client_socket) {
	
	while (1) {
		
		int length;
		char* text;
		
		/* Primero, lee la longitud del mensaje de texto del socket. Si retorna cero, el cliente cerró la conexión. */
		if (read (client_socket, &length, sizeof (length)) == 0)
			
			return 0;
		
		/* Asignar un búfer para guardar el texto. */
		text = (char*) malloc (length);
		
		/* Leer el texto en sí, e imprimirlo. */
		read (client_socket, text, length);
		printf ("%s\n", text);
		
		/* Liberar el búfer. */
		free (text);
		
		/* Si el cliente envía el mensaje "quit", terminamos.*/
		if (!strcmp (text, "quit"))
			
			return 1;
	}
}

int main (int argc, char* const argv[]) {

	const char* const socket_name = argv[1];
	int socket_fd;
	struct sockaddr_un name;
	int client_sent_quit_message;
	
	/* Crea el socket. */
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	
	/* Indicar que esto es un servidor. */
	name.sun_family = AF_LOCAL;
	strcpy (name.sun_path, socket_name);
	bind (socket_fd, &name, SUN_LEN (&name));
	
	/* Escuchar conexiones. */
	listen (socket_fd, 5);
	
	/* Repetidamente aceptar conexiones, girando un server() que se encargue de cada cliente. Continua hasta que un cliente envía un mensaje "quit".*/
	do {
		
		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;
		
		/* Acepta una conexión. */
		client_socket_fd = accept (socket_fd, &client_name, &client_name_len);
		
		/* Maneja la conexión. */
		client_sent_quit_message = server (client_socket_fd);
		
		/* Cierra nuestro extremo de la conexión. */
		close (client_socket_fd);
	}
	
	while (!client_sent_quit_message);
	
		/* Remueve el archivo socket. */
		close (socket_fd);
		unlink (socket_name);
		
		return 0;
}
