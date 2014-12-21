#include "applicationhandler.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

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
    //stopClient(1);
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

void applicationHandler::sendToServer(QString qstr) {
    qDebug() << qstr;
//    char *str = QStringtoChar(qstr);
//    sendR(&str);
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
