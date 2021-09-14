#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

/* Imprime los contenidos de la página de inicio del socket del servidor. Retorna un indicador de éxito. */
void get_home_page (int socket_fd) {
	
	char buffer[10000];
	ssize_t number_characters_read;
	
	/* Envía el comando HTTP GET para la página de inicio. */
	sprintf (buffer, "GET /\n");
	write (socket_fd, buffer, strlen (buffer));
	
	/* Lee del socket. La llamada para leer puede no retornar todos los datos de una vez, por eso seguir intentando hasta que se acabe. */
	while (1) {
		
		number_characters_read = read (socket_fd, buffer, 10000);
		if (number_characters_read == 0)
			
			return;
	
		/* Escribe los datos en la salida estándar. */
		fwrite (buffer, sizeof (char), number_characters_read, stdout);
	}
}

int main (int argc, char* const argv[]) {
	
	int socket_fd;
	struct sockaddr_in name;
	struct hostent* hostinfo;
	
	/* Crear el socket. */
	socket_fd = socket (PF_INET, SOCK_STREAM, 0);
	
	/* Guarda el nombre del servidor en la dirección del socket. */
	name.sin_family = AF_INET;
	
	/* Convierte las cadenas a números. */
	hostinfo = gethostbyname (argv[1]);
	if (hostinfo == NULL)
		
		return 1;
	else
		name.sin_addr = *((struct in_addr *) hostinfo->h_addr);
		
		/* Servidores web usan el puerto 80. */
		name.sin_port = htons (80);
		
	/* Conecta al servidor web. */
	if (connect (socket_fd, &name, sizeof (struct sockaddr_in)) == -1) {
		
		perror ("connect");
		return 1;
	}
	
	/* Recupera la página de inicio del servidor. */
	get_home_page (socket_fd);
	
	return 0;
}
