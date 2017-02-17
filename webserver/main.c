#include "socket.h"

void initialiser_signaux();
void traitement_signal(int sig);

int main()
{
	int socket_client;
	int s = creer_serveur(8080);

	initialiser_signaux();

	while(1) {

		socket_client = accept( s, NULL, NULL );
		if( socket_client == -1 ) {
			perror("accept");
			return -1;
		}

		int pid = fork();

		if(pid == -1)
		{
			close(socket_client);
			continue;
		}
		else if(pid > 0)
		{
			continue;
		}
		else if(pid == 0)
		{
			printf("fils ; %d\n",getpid());
			printf("mon pere ; %d\n",getppid());
			
			sleep(1);
			const char *message_bienvenue = "Bienvenue sur mon serveur\n";
			write( socket_client, message_bienvenue, strlen(message_bienvenue));

			char p[1000];
			FILE *file;
			file = fdopen( socket_client , "w+");
	
			while(1){

				if(fgets( p, sizeof(p), file ) != NULL)
				{
					fprintf(file , "<GomuGomu> %s", p );
				}

			}

			fclose(file);
			printf("probleme\n");
			
		}
	}
	return 0;
}

void traitement_signal(int sig)
{
	printf("Signal %d reçu\n", sig);
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void initialiser_signaux()
{
	struct sigaction sa;

	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction(SIGCHLD)");
	}
	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
	}
}
