#include "iftun.h"

int tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(-1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

void copie(int src, int dst){
  for(;;){
		char buf[2048];
		int r = read(src, buf, 2048);
		if(r<0){perror("Erreur lecture");exit(1);}
		if(r == 0){return;}

		int w = write(dst, buf, 2048);
		if(w<0){perror("Erreur ecriture");exit(1);}
	}
}

int createAndSetTun(char * tun_name, char * address){
  int tunfd = tun_alloc(tun_name);
  if(tunfd<0){
    perror("Unable to create a tunnel");
    exit(1);
  }
  //Configuration du tunnel
  char tun_conf[2048];
  sprintf(tun_conf, "ip addr add %s dev %s", address, tun_name);
  system(tun_conf);

  return tunfd;
}
/*
int main(int narg, char** argv){

  if(narg != 3){printf("Usage::%s tunnel_name address\n", argv[0]); exit(1);}

  int tunfd = createAndSetTun(argv[1], argv[2]);
  system("ip addr");
  copie(tunfd, 1);

  return EXIT_SUCCESS;

}
*/
/*
int main (int argc, char** argv){

  int tunfd;
  printf("CrÃ©ation de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  //printf("Faire la configuration de %s...\n",argv[1]);
  //printf("Appuyez sur une touche pour continuer\n");
  //getchar();
  //printf("Interface %s ConfigurÃ©e:\n",argv[1]);
  system("ip addr");
  printf("\n\n");
  char cmd[2048];
  sprintf(cmd, "/mnt/partage/configure-tun.sh %s", "172.16.2.1/28");
  printf("$: %s\n", cmd);

  printf("\n\n");
  system(cmd);
  system("ip addr");
  //copie(tunfd, 1);
  printf("Appuyez sur une touche pour terminer\n");
  getchar();

  return 0;
}*/
