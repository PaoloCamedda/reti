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
    struct sockaddr_in simpleServer;
    int maxNum=0;
    char buffer[256];
    int result;


    if (2 != argc) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = atoi(argv[1]);

    memset(&simpleServer, '\0', sizeof(simpleServer)); 
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    returnStatus = bind(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));
    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    } else {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

    returnStatus = listen(simpleSocket, 5);
    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simpleSocket);
        exit(1);
    }






    while (1) {
        struct sockaddr_in clientName = { 0 };
        int simpleChildSocket = 0;
        int clientNameLength = sizeof(clientName);

        simpleChildSocket = accept(simpleSocket, (struct sockaddr *)&clientName, &clientNameLength);
        if (simpleChildSocket == -1) {
            fprintf(stderr, "Cannot accept connections!\n");
            close(simpleSocket);
            continue;
        }

        // Costruisci il messaggio con la data e l'ora correnti
        char message[BUFFER_SIZE];
        time_t ticks = time(NULL);
        snprintf(message, sizeof(message), "%s%.24s\r\n", BASE_MESSAGE, ctime(&ticks));

        write(simpleChildSocket, message, strlen(message));
        char world[256];
        int hit;
        //ricevo num iterazioni 
         returnStatus=read(simpleChildSocket,&hit,sizeof(hit));
          if(returnStatus<0){
            printf("Error namber of hit receved\n");
          }

         while(hit>0){

             returnStatus=read(simpleChildSocket,world,sizeof(world));
          if(returnStatus<0){
            printf("Error world receved\n");
          }
          //iniziare con il codice per calcolare l' operazione 



          returnStatus=write(simpleChildSocket, &result, sizeof(result));
          hit--;
         }
     memset(&buffer, '\0', sizeof(buffer));
        returnStatus = read(simpleChildSocket, buffer, sizeof(buffer));
        if(returnStatus > 0 && strcmp(buffer, "bye") == 0)
            write(simpleChildSocket, "ack", strlen("ack"));
        close(simpleChildSocket);
    }

    close(simpleSocket);
    return 0;
}
