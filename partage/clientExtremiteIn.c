#include <stdio.h>
#include "extremite.h"

int main(int narg, char** argv){

  if(narg != 4){printf("Usage::%s tunnel_name address_of_tun address_of_destination\n", argv[0]); exit(1);}

  int tunfd = createAndSetTun(argv[1], argv[2]);
  ext_in(tunfd, argv[3]);

}
