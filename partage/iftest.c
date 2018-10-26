#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "iftun.h"


int main(int narg, char** argv){

  if(narg != 3){printf("Usage::%s tunnel_name address\n", argv[0]); exit(1);}

  int tunfd = createAndSetTun(argv[1], argv[2]);
  system("ip addr");
  copie(tunfd, 1);

  return EXIT_SUCCESS;

}
