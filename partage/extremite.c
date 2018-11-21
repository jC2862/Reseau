#include "extremite.h"

void ext_in(int soctun0, char * addr){

    char * hote;
    char * port;
    char ip[NI_MAXHOST];
    struct addrinfo *resol;
    int s;

    hote=addr;
    port="123";
    if ( getaddrinfo(hote,port,NULL, &resol) < 0 ){
        perror("rÃ©solution adresse");
        exit(2);
    }

    sprintf(ip,"%s",inet_ntoa(((struct sockaddr_in*)resol->ai_addr)->sin_addr));

    if ((s=socket(resol->ai_family,resol->ai_socktype, resol->ai_protocol))<0){perror("allocation de socket");exit(3);}
    fprintf(stderr,"le num de la socket est : %i\n",s);
    fprintf(stderr,"Essai de connexion Ã  %s (%s) sur le port %s\n\n",
        hote,ip,port);
    if (connect(s,resol->ai_addr,sizeof(struct sockaddr_in))<0){perror("connexion");exit(4);}
    freeaddrinfo(resol);

    copie(soctun0, s);
}

void ext_out(int tun_fd){
    int s,n,len,on;
    struct addrinfo * resol;
    struct addrinfo indic = {AI_PASSIVE,
                            PF_INET,SOCK_STREAM,0,
                            0,NULL,NULL,NULL};
    struct sockaddr_in client;
    int err;

    //Configuration serveur
    char * port="123"; fprintf(stderr,"Ecoute sur le port %s\n",port);
    err = getaddrinfo(NULL,port,&indic,&resol);
    if (err<0){fprintf(stderr,"Resolution: %s\n",gai_strerror(err));exit(2);}
    if ((s=socket(resol->ai_family,resol->ai_socktype,resol->ai_protocol))<0){perror("Allocation de socket");exit(3);}
    fprintf(stderr,"Le num de la socket est : %i\n",s);
    on = 1;
    if (setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0){perror("option socket");exit(4);}
    fprintf(stderr,"Option(s) OK!\n");
    if (bind(s,resol->ai_addr,sizeof(struct sockaddr_in))<0) {perror("bind");exit(5);}
    freeaddrinfo(resol);
    fprintf(stderr,"bind!\n");
    if (listen(s,SOMAXCONN)<0) {perror("listen");exit(6);}

    printf("Attente de connexion \n");

    //Attente de connection
    len=sizeof(struct sockaddr_in);
    if( (n=accept(s,(struct sockaddr *)&client,(socklen_t*)&len)) < 0 ){perror("accept");exit(7);}
    char hotec[NI_MAXHOST];  char portc[NI_MAXSERV];
    err = getnameinfo((struct sockaddr*)&client,len,hotec,NI_MAXHOST,portc,NI_MAXSERV,0);
    printf("ERR: %d\n", err);
    if (err < 0 ){fprintf(stderr,"resolution client (%i): %s\n",n,gai_strerror(err));}
    else{fprintf(stderr,"accept! (%i) ip=%s port=%s\n",n,hotec,portc);}

    copie(n, tun_fd);
}
