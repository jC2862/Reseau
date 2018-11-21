#include "extremite.h"

int main(int narg, char** argv){

  if(narg != 5){printf("Usage::%s tunnel_name tunnel_address dst_addr dst_port\n", argv[0]); exit(1);}

  int tunfd = createAndSetTun(argv[1], argv[2]);
  pid_t f = fork();
  if(f < 0){perror("Fork");exit(1);}
  if(f == 0){
    ext_out(tunfd);
    exit(0);
  }else{
    ext_in(tunfd, argv[3], argv[4]);
  }


}
