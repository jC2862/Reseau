#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iftun.h"
#include "extremite.h"
/*
# interface tun
tun=tun0
# adresse locale
inip=
inport=
options=
# adresse distante
outip=
outport=
*/
char name[10];
char inip[10], inport[10], options[10];
char outip[10], outport[10];

void confUsage(){
  printf("%s\n",
  "# interface tun \n \
  tun=tun0 \n \
  # adresse locale \n \
  inip= \n \
  inport= \n \
  options= \n \
  # adresse distante \n \
  outip= \n \
  outport="
);
}

int switchConf(char * fst, char * snd){
       if(strcmp(    "tun",fst)==0){strcpy(   name, snd);return 1;}
  else if(strcmp(   "inip",fst)==0){strcpy(   inip, snd);return 1;}
  else if(strcmp( "inport",fst)==0){strcpy( inport, snd);return 1;}
  else if(strcmp("options",fst)==0){strcpy(options, snd);return 1;}
  else if(strcmp(  "outip",fst)==0){strcpy(  outip, snd);return 1;}
  else if(strcmp("outport",fst)==0){strcpy(outport, snd);return 1;}
  return 0;
}

void readFile(FILE * file){
  char line[256];
  //Lire le fichier
  for(int i=0; i<6;){
    char fst[64],snd[64];
    if(fgets(line, 256, file)==NULL){confUsage();exit(1);}
    if(line[0] == '#'){continue;}
    sscanf(line, "%[^=]=%s", fst,snd);
    //printf("fst:'%s', snd='%s'\n", fst, snd);
    i+=switchConf(fst, snd);
  }

}

int main(int narg, char ** argv){

  if(narg != 3){printf("Usage::%s configfile setroutefile.sh\n",argv[0]);exit(1);}

  FILE * confFile = fopen(argv[1], "r");
  if(confFile == NULL){perror("Ouverture fichier");exit(1);}
  //Recuperation des variables du fichier de configuration
  readFile(confFile);
  printf("%s %s %s %s %s %s\n", name, inip, inport, options, outport, outip);
  fclose(confFile);
  //Utilisation des variables
  int tunfd = createAndSetTun(name, inip);
  if(system(argv[2])<0){perror("Configuration tun"); exit(12);}
  pid_t f = fork();
  if(f < 0){perror("Fork");exit(1);}
  if(f == 0){
    ext_outv2(tunfd, inport, options);
    exit(0);
  }else{
    ext_in(tunfd, outip, outport);
  }
}
