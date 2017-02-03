#include "socket.h"

int main()
{
	int socket_client;
	int s = creer_serveur(8080);

	while( 1 ) {

		socket_client = accept( s, NULL, NULL );
		if( socket_client == -1 ) {
			perror("accept");
			return -1;
		}

		const char *message_bienvenue = "Bienvenue sur mon serveur\n";
		write( socket_client, message_bienvenue, strlen(message_bienvenue));

		char *p = malloc(1000);

		while( read(socket_client, p , strlen(p))){

			write( socket_client , p , strlen(p) );
		}
	}
	return 0;
}
