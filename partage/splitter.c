#include <stdio.h>
#include "extremite.h"


int main(){

  int tunfd = createAndSetTun("tun0", "172.16.2.1/28");

  printf("Appuyez sur entree lorsque vous avez finis d'utiliser tun0 \n");
  getc(stdin);

}
