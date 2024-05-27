#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in  destAddr, senderAddr;
    socklen_t destSize, senderSize;


    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {

        fprintf(stderr, "Socket created!\n");
    }

    destSize = sizeof(destAddr);
    simplePort = atoi(argv[2]);

 
   



    int hit;
    char  world [256];
    char worldReceved [256];

    printf("inserici un numero positivo di hit per continuare oppure uno negativo per uscire\n");
    scanf("%d",&hit);
     if(hit<=0)
        {
            printf("bey bey");
            close(simpleSocket);
        }
    //--------qui
    returnStatus =sendto(simpleSocket, &hit, sizeof(hit), 0, (struct sockaddr*)&destAddr, destSize);
    if(returnStatus>0) printf("\t \a dato hit inviato\n ");
    else fprintf(stderr, "Connect Error 404 namber of hit!\n");

    while(hit>0){

        printf("immetere la sringa da inserire \n non inserire spazi nella compilazione della stringa \n");
        scanf("%s",world);

        //fprintf(stdout, "\nType here your message: ");
        //fgets(world, sizeof(world), stdin);


         //returnStatus = write(simpleSocket, world, sizeof(world));
         returnStatus =sendto(simpleSocket, world, strlen(world), 0, (struct sockaddr*)&destAddr, destSize);
         if(returnStatus>0) printf("\t \a dato world inviato\n ");
         else fprintf(stderr, "Connect Error 404 namber of word!\n");

             //returnStatus = read(simpleSocket,worldReceved,sizeof(worldReceved));
             returnStatus =recvfrom(simpleSocket, worldReceved, sizeof(worldReceved), 0, (struct sockaddr*)&senderAddr, &senderSize);
        if (returnStatus > 0) {
        printf("\t \a la stringa ricevuta è : [ %s ] \n",worldReceved);
        }
        else {
            fprintf(stderr, "Connect Error 404 word receved !\n");
        }
        hit --;
    }
    
  /* write(simpleSocket, "bye", strlen("bye"));
        memset(&buffer, '\0', sizeof(buffer));
        returnStatus = read(simpleSocket, buffer, sizeof(buffer));
        
        if(returnStatus > 0 && strcmp(buffer, "ack") == 0){
            fprintf(stdout, "\nAck received. Connection with server closed\n");
        }
    
    else
        fprintf(stderr, "Failed connection! (RS: %d)\n", returnStatus);
    */
    close(simpleSocket);
    return 0;
}
