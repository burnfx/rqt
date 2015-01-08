#include "applicationhandler.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#define MAX_BUF 50

char* applicationHandler::stringtoChar(std::string stdstr) {
    char *str;
    str = new char[stdstr.length() + 1];
    strcpy(str,stdstr.c_str());
    return str;
}

char* applicationHandler::QStringtoChar(QString qstr) {
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

void applicationHandler::selectVideoTrack(int blockNum, int userGroup, int seqNum)
{
    qDebug() << "applicationHandler says: blockNum = " << blockNum << ", userGroup = " << userGroup << ", seqNum = " << seqNum;
    std::string stdstr;
    stdstr = "-file " + recordFiles[userGroup-1][blockNum-1][seqNum];
    char *str = &stdstr[0];
    sendToServer(str);
}

void applicationHandler::selectVideoTrack()
{
    qDebug() << "applicationHandler says: load eye slider demo file";

    std::string stdstr = "-file e1d30l1m1r1h111";
    char *str = &stdstr[0];
    sendToServer(str);
}

void applicationHandler::sendToServer(QString qstr) {
    qDebug() << qstr;
    char *str = QStringtoChar(qstr);
    sendR(&str);
    usleep(100);
}


void applicationHandler::setControl(QString param)
{
    QString str = "-control ";
    if (param.compare(param, "stop") == 0) {
        str.append(param);
        qDebug() << "applicationHandler says: " << str;
    }
    else if (param.compare(param, "play") == 0) {
        str.append(param);
        qDebug() << "applicationHandler says: " << str;
    }
    else if (param.compare(param, "pause") == 0) {
        str.append(param);
        qDebug() << "applicationHandler says: " << str;
    }
    else if (param.compare(param, "next") == 0) {
        str.append(param);
        qDebug() << "applicationHandler says: " << str;
    }
    else if (param.compare(param, "previous") == 0) {
        str.append(param);
        qDebug() << "applicationHandler says: " << str;
    }
    sendToServer(str);
}

void applicationHandler::setRedGreen(QString param) {
    QString str = "-redgreen ";
    if (param.compare(param, "2") == 0)
    {
        str.append("on");
        qDebug() << "applicationHandler says: " << str;
    }
    else
    {
        str.append("off");
        qDebug() << "applicationHandler says: " << str;

    }
    sendToServer(str);
}

void applicationHandler::setFile(QString param)
{

    // char buf[MAX_BUF];
    QString str = "-";
    str.append("file ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setMode(QString param)
{
    QString str = "-";
    str.append("mode ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setTime(QString param)
{
    QString str = "-";
    str.append("time ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setReduction(QString param)
{
    QString str = "-";
    str.append("reduction ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setUpdateInterval(QString param)
{
    QString str = "-";
    str.append("updateInterval ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setcDecay(QString param)
{
    QString str = "-";
    str.append("cDecay ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setViewport_Offset(QString param)
{
    QString str = "-";
    str.append("viewport_Offset ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}

void applicationHandler::setTranslateBack_Offset(QString param)
{
    QString str = "-";
    str.append("translateBack_Offset ");
    str.append(param);
    qDebug() << "applicationHandler says: " << str;
    sendToServer(str);
}
