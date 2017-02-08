#include "socket.h"

void initialiser_signaux();

int main()
{
	int socket_client;
	int s = creer_serveur(8080);

	initialiser_signaux();

	while( 1 ) {

		socket_client = accept( s, NULL, NULL );
		if( socket_client == -1 ) {
			perror("accept");
			return -1;
		}
		sleep(1);
		const char *message_bienvenue = "Bienvenue sur mon serveur\n";
		write( socket_client, message_bienvenue, strlen(message_bienvenue));

		char p[1000];

		while(1){

			int r = read(socket_client, p, 1000);

			if(r != 0) printf("%d\n",r);

			int w = write(socket_client, p, r);

			if(w != 0) printf("%d\n",w);
		}
	}
	return 0;
}

void initialiser_signaux()
{
	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
	}
}
