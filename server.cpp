#include "server.h"

server::server()
{
}

void server::cleanup(int i)
{
    char* quit = "-quit 1";
    sendR(&quit);
    return;
}

void server::sendR(char** cmd)
{
    qDebug() << "Server: sendR: " << QString::fromUtf8(*cmd);
    return;
}

/*#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

*/
