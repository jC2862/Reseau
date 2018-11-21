#ifndef _H_extremite
#define _H_extremite

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "iftun.h"

void ext_in(int soctun0, char * addr, char * por);
void ext_out(int tun_fd);

#endif
