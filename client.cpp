#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <QString>
#include <QDebug>
#include "applicationhandler.h"

#define SERVER_ADRESS "localhost"
#define SERVER_PORT 1600
#define MAX_MSG 256
#define MAX_ACK 50

int client;

void sendR(char** cmd) {
    int rc;
    rc = send(client, *cmd, strlen(*cmd) + 1, 0);
    if (rc < 0) {
        perror("cannot send data");
        close(client);
        exit(-1);
    }
    //printf("%s\n", *cmd); fflush(stdout);


    if (strcmp(*cmd, "-control play") == 0) {

        int read_size;
        char line[MAX_MSG];
        char ack[MAX_ACK];
        char param[MAX_MSG];
        // receive answer
        while ( (read_size = recv(client , line , MAX_MSG , 0)) >= 0) {
            if (strncmp(line, "ack", 3) == 0) {
                memset(ack, 0, MAX_ACK);
                memset(param, 0, MAX_MSG);
                if (sscanf(line, "%s %s", ack, param) > 0) {
                    if (strcmp(ack, "ack") == 0)  {
                       qDebug() << QString::fromLocal8Bit(param);
                       if (strcmp(ack, "ack") == 0) {
                       unsigned long start_time = QString::fromLocal8Bit(param).QString::toULong();
                       // qDebug() << "client says: start time = " << start_time;
                       applicationHandler::setStartTime(start_time);
                       }
                    } else{
                        qDebug() << "variable ack != string ack";
                    }
                }
                else {
                    qDebug() << "sscanf line failed or no ack1 oder ack0 received";
                }
                break;
            }
            else {
               qDebug() << "strncmp line failed";
            }
            memset(line,0,MAX_MSG);
        }
    }
    return;
}

// disconnects from server
void stopClient(int signum) {
    char* quit = "-quit 1";
    sendR(&quit);
    close(client);
    return;
}

// starts client connection to retinarift server
void startClient() {
    // set signals for terminate/interrupt
    signal(SIGTERM, stopClient);
    signal(SIGINT, stopClient);

    // client socket
    int rc;
    struct sockaddr_in local_addr, serv_addr;
    struct hostent * host;

    // get host address from server name
    host = gethostbyname(SERVER_ADRESS);

    if (host == NULL) {
        printf("unknown host \n");
        exit(-1);
    }

    // now fill in sockaddr_in for remote address
    serv_addr.sin_family = host->h_addrtype;
    // get first address in host, copy to serv_addr
    memcpy((char *) &serv_addr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
    serv_addr.sin_port = htons(SERVER_PORT);
    memset(serv_addr.sin_zero, 0, 8);

    // create local stream socket
    client = socket(PF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        perror("cannot open socket ");
        exit(-1);
    }
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(0);
    memset(local_addr.sin_zero, 0, 8);

    // bind
    rc = bind(client, (struct sockaddr *) &local_addr, sizeof(local_addr));
    if (rc < 0) {
        printf("cannot bind port TCP %u\n",SERVER_PORT);
        perror("error ");
        exit(1);
    }

    // connect to server
    rc = connect(client, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (rc < 0) {
        perror("cannot connect");
        exit(1);
    }
    printf("connected to retinarift server:%u\n", SERVER_PORT);
}

int clientMain(int argc, char *argv[])
{
        // start client connection to server
        startClient();
        stopClient(1);
}

