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
  ifr.ifr_flags = IFF_TUN ;
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
    printf("%d->\n",src);
		int r = read(src, buf, 2048);
		if(r<0){perror("Erreur lecture");exit(1);}
		if(r == 0){return;}
    printf("%s\n",buf);

    printf(">-%d\n",dst);
		int w = write(dst, buf, 2048);
		if(w<0){perror("Erreur ecriture");exit(1);}
    printf("%s \n", buf);
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
  printf("%s\n", tun_conf);
  system(tun_conf);
  sprintf(tun_conf, "ip link set %s up", tun_name);
  printf("%s\n", tun_conf);
  system(tun_conf);

  return tunfd;
}
