#include "applicationhandler.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define MAX_BUF 50

static char* stringtoChar(std::string stdstr) {
    char *str;
    str = new char[stdstr.length() + 1];
    strcpy(str,stdstr.c_str());
    return str;
}

static char* qstringtoChar(QString qstr) {
    char *str;
    std::string stdstr = qstr.toUtf8().constData();
    str = new char[stdstr.length() + 1];
    strcpy(str,stdstr.c_str());
    return str;
}

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
    std::string stdstr = recordFiles[recordIDs[blockNum-1][seqNum][1]][recordIDs[blockNum-1][seqNum][2]];
    stdstr = "-file " + stdstr;
    char *str = &stdstr[0];
    sendToServer(str);
}

void applicationHandler::sendToServer(char *str) {
    sendR(&str);
}


void applicationHandler::setControl(char *param)
{
    char *str;
    if (strcmp(param, "stop") == 0) {
        qDebug() << "applicationHandler says: current track stopped";
        str = "-control stop";
    }
    else if (strcmp(param, "play") == 0) {
        qDebug() << "applicationHandler says: play";
        str = "-control play";
    }
    else if (strcmp(param, "pause") == 0) {
        qDebug() << "applicationHandler says: current track paused";
        str = "-control pause";
    }
    else if (strcmp(param, "next") == 0) {
        qDebug() << "applicationHandler says: next track";
        str = "-control next";
    }
    else if (strcmp(param, "previous") == 0) {
        qDebug() << "applicationHandler says: next previous";
        str = "-control previous";
    }
    sendToServer(str);
}

void applicationHandler::setRedGreen(int rgb) {
    if (rgb == 2)
    {
        qDebug() << "applicationHandler says: setRedGreen = on";
        char* str = "-redgreen on";
        sendToServer(str);
    }
    else
    {
        qDebug() << "applicationHandler says: setRedGreen = off";
        char* str = "-redgreen off";
        sendToServer(str);
    }
}

void applicationHandler::setFile(char *file)
{
    qDebug() << "applicationHandler says: setFile = " << file;
    char buf[MAX_BUF];
    strcpy(buf, "-file ");
    strcat(buf, file);
    char* str = buf;
    sendToServer(str);
}

void applicationHandler::setTime(char *time)
{
    qDebug() << "applicationHandler says: setTime = " << time;
    char buf[MAX_BUF];
    strcpy(buf, "-time ");
    strcat(buf, time);
    char *str = buf;
    sendToServer(str);
}

void applicationHandler::setReduction(char *reduction)
{
    qDebug() << "applicationHandler says: setReduction = " << reduction;
    char buf[MAX_BUF];
    strcpy(buf, "-reduction ");
    strcat(buf, reduction);
    char *str = buf;
    sendToServer(str);
}

void applicationHandler::setUpdateInterval(char *updateInterval)
{
    qDebug() << "applicationHandler says: setUpdateIntervaln = " << updateInterval;

    char buf[MAX_BUF];
    strcpy(buf, "-updateInterval ");
    strcat(buf, updateInterval);
    char *str = buf;
    sendToServer(str);
}

void applicationHandler::setcDecay(char *cDecay)
{
    qDebug() << "applicationHandler says: setcDecay = " << cDecay;
    char buf[MAX_BUF];
    strcpy(buf, "-cDecay ");
    strcat(buf, cDecay);
    char *str = buf;
    sendToServer(str);
}

void applicationHandler::setViewport_Offset(int value)
{
    qDebug() << "applicationHandler says: setViewport_Offset = " << value ;
    char offset[MAX_BUF];
    sprintf(offset, "%d",value);
    qDebug() << offset;
    char buf[MAX_BUF];
    strcpy(buf, "-viewport_Offset ");
    strcat(buf, offset);
    char *str = buf;
    sendToServer(str);
}

void applicationHandler::setTranslateBack_Offset(char *offset)
{
    qDebug() << "applicationHandler says: setTranslateBack_Offset = " << offset ;
    char buf[MAX_BUF];
    strcpy(buf, "-translateBack_Offset ");
    strcat(buf, offset);
    char *str = buf;
    sendToServer(str);
}
