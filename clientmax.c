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
    struct sockaddr_in simpleServer;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    } else {
        fprintf(stderr, "Socket created!\n");
    }

    simplePort = atoi(argv[2]);

    memset(&simpleServer, '\0', sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = inet_addr(argv[1]);
    simpleServer.sin_port = htons(simplePort);

    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));
    if (returnStatus == -1) {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    } else {
        fprintf(stderr, "Connect successful!\n");
    }

    // Riceve il messaggio dal server
    returnStatus = read(simpleSocket, buffer, sizeof(buffer) - 1);
    if (returnStatus > 0) {
        buffer[returnStatus] = '\0';  // Aggiunge il terminatore di stringa
        printf("Message from server: %s", buffer);
    } else {
        fprintf(stderr, "Error receiving message from server\n");
    }

   



    int numToSend;
    int numToReceve;

    do{
    

    printf("inserici un numero positivo per continuare oppure uno negativo per uscire\n");
    scanf("%d",&numToSend);
     if(numToSend<0)
        {
            printf("bey bey");
        }
    write(simpleSocket, &numToSend, sizeof(numToSend));//--------qui
    printf("dato inviato ");

    returnStatus = read(simpleSocket,&numToReceve,sizeof(numToReceve));
    if (returnStatus > 0) {
    printf("il numero ricevuto dal server max è : %d \n",numToReceve);
    }
    else {
        fprintf(stderr, "Connect Error 404 !\n");
    }

    }while(numToSend>0);
    close(simpleSocket);
    return 0;
}
