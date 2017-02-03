#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int creer_serveur(int port);

#endif