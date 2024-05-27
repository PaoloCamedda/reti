#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 256

const char BASE_MESSAGE[] = "Hello UPO student! Current time: ";

int main(int argc, char *argv[]) {
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in   destAddr, senderAddr;
    socklen_t destSize, senderSize;
    int hit;
    char world[256];

    int maxNum=0;
    char buffer[256];
    if (2 != argc) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = atoi(argv[1]);
    destSize = sizeof(destAddr);


recvfrom(simpleSocket, hit,sizeof(hit) , 0, (struct sockaddr*)&senderAddr, &senderSize);
printf("ricevuto capo");

         while(hit>0){

             //returnStatus=read(simpleChildSocket,world,sizeof(world));
            returnStatus = recvfrom(simpleSocket, world,strlen(world) , 0, (struct sockaddr*)&senderAddr, &senderSize);

            

          if(returnStatus<0){
            printf("Error world receved\n");
          }

          //returnStatus=write(simpleChildSocket, &world, sizeof(world));
           returnStatus=sendto(simpleSocket, world, strlen(world), 0, (struct sockaddr*)&destAddr, destSize);
          hit--;
         }
    
        
    

    close(simpleSocket);
    return 0;
}
