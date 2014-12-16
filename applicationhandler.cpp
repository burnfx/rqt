#include "applicationhandler.h"
#include "client.h"

applicationHandler::applicationHandler()
{

}

void applicationHandler::closeGUI()
{
    stopClient(1);
    qDebug() << "applicationHandler says: GUI closed";
}

void applicationHandler::selectVideoTrack(int blockNum, int seqNum)
{
    qDebug() << "applicationHandler says: blockNum = " << blockNum << ", seqNum = " << seqNum;
    //setFile(&str);

}

void applicationHandler::setControl(char *param)
{
    if (strcmp(param, "stop") == 0) {
        qDebug() << "applicationHandler says: current track stopped";
        char *str = "-control stop";
        sendR(&str);
    }
    else if (strcmp(param, "play") == 0) {
        qDebug() << "applicationHandler says: play";
        char *str = "-control play";
        sendR(&str);
    }
    else if (strcmp(param, "pause") == 0) {
        qDebug() << "applicationHandler says: current track paused";
        char *str = "-control pause";
        sendR(&str);
    }
    else if (strcmp(param, "next") == 0) {
        qDebug() << "applicationHandler says: next track";
        char *str = "-control next";
        sendR(&str);
    }
    else if (strcmp(param, "previous") == 0) {
        qDebug() << "applicationHandler says: next previous";
        char *str = "-control previous";
        sendR(&str);
    }
}

void applicationHandler::setRedGreen(int rgb) {
    if (rgb == 2)
    {
        qDebug() << "applicationHandler says: setRedGreen = on";
        char* str = "-redgreen on";
        sendR(&str);
    }
    else
    {
        qDebug() << "applicationHandler says: setRedGreen = off";
        char* str = "-redgreen off";
        sendR(&str);
    }
}

void applicationHandler::setFile(char *file)
{
    qDebug() << "applicationHandler says: setReduction = " << file;
    char *str;
    strcpy(str, "-file");
    strcat(str, file);
    sendR(&str);
}

void applicationHandler::setReduction(char *reduction)
{
    qDebug() << "applicationHandler says: setReduction = " << reduction;
    char *str;
    strcpy(str, "-reduction");
    strcat(str, reduction);
    sendR(&str);
}

void applicationHandler::setUpdateInterval(char *updateInterval)
{
    qDebug() << "applicationHandler says: setUpdateIntervaln = " << updateInterval;
    char *str;
    strcpy(str, "-updateInterval");
    strcat(str, updateInterval);
    sendR(&str);
}

void applicationHandler::setcDecay(char *cDecay)
{
    qDebug() << "applicationHandler says: setcDecay = " << cDecay;
    char *str;
    strcpy(str, "-cDecay");
    strcat(str, cDecay);
    sendR(&str);
}

void applicationHandler::setViewport_Offset(char *offset)
{
    qDebug() << "applicationHandler says: setViewport_Offset = " << offset ;
    char *str;
    strcpy(str, "-viewport_Offset");
    strcat(str, offset);
    sendR(&str);
}

void applicationHandler::setTranslateBack_Offset(char *offset)
{
    qDebug() << "applicationHandler says: setTranslateBack_Offset = " << offset ;
    char *str;
    strcpy(str, "-translateBack_Offset ");
    strcat(str, offset);
    sendR(&str);
}
