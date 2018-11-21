#include <stdio.h>
#include "extremite.h"

int main(int narg, char ** argv){

  if(narg != 5){printf("Usage::%s tunnel_name address_of_tun address_of_destination port_destination\n", argv[0]); exit(1);}
  //if(narg!=2){printf("Usage::%s destination_address\n", argv[0]); exit(1);}

  int tunfd = createAndSetTun(argv[1], argv[2]);
  ext_in(tunfd, argv[3], argv[4]);

}
