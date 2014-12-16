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

void applicationHandler::setFile(char *str)
{
    qDebug() << "applicationHandler says: setReduction = " << str ;
    sendR(&str);
}

void applicationHandler::setReduction(char *str)
{
    qDebug() << "applicationHandler says: setReduction = " << str ;
    sendR(&str);
}

void applicationHandler::setUpdateInterval(char *str)
{
    qDebug() << "applicationHandler says: setUpdateIntervaln = " << str ;
    sendR(&str);
}

void applicationHandler::setcDecay(char *str)
{
    qDebug() << "applicationHandler says: setcDecay = " << str ;
    sendR(&str);
}

void applicationHandler::setViewport_Offset(char *str)
{
    qDebug() << "applicationHandler says: Viewport_Offset = " << str ;
    sendR(&str);
}

void applicationHandler::setTranslateBack_Offset(char *str)
{
    qDebug() << "applicationHandler says: TranslateBack_Offset = " << str ;
    sendR(&str);
}
