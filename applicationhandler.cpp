#include "applicationhandler.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <chrono>
#include <ctime>
using namespace std;
#define MAX_BUF 50

unsigned long applicationHandler::start_time = 0;


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
    for (int i = 0; i<10; i++){
        for(int k = 0; k<2; k++){
            timeForDecision[i][k] = 0;
        }
    }
}

void applicationHandler::closeGUI()
{
    stopClient(1);
    qDebug() << "applicationHandler says: GUI closed";
}

void applicationHandler::selectVideoTrack(int seqNum)
{
    qDebug() << "applicationHandler says: seqNum = " << seqNum;
    std::string stdstr;
    //std::string test;
    //test = recordFiles[seqNum];
    stdstr = "-file " + recordFiles[seqNum];
    char *str = &stdstr[0];
    sendToServer(str);
}

void applicationHandler::selectVideoTrack()
{
    qDebug() << "applicationHandler says: load eye slider demo file";

    std::string stdstr = "-file e1d60l1m1r1h111";
    char *str = &stdstr[0];
    sendToServer(str);
}

void applicationHandler::playBlackBackground()
{
    qDebug() << "applicationHandler says: load black background";

    std::string stdstr = "-file black";
    char *str = &stdstr[0];
    sendToServer(str);
}

void applicationHandler::sendToServer(QString qstr) {
    // qDebug() << qstr;
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

unsigned long applicationHandler::measureStopTime(int seqNumber)
{
    unsigned long stop_time = std::chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    unsigned long time_difference = stop_time - applicationHandler::start_time;
    /*
    if(timeForDecision[seqNumber][0] == 0)
    {
        timeForDecision[seqNumber][0] = time_difference;
        timeForDecision[seqNumber][1] = time_difference;
    }else
    {
        timeForDecision[seqNumber][1] = time_difference;
    }
    */
    // qDebug() << "applicationHandler says: start time = " << applicationHandler::start_time << "stop time = " << stop_time << "time diff = " << time_difference;
    return time_difference;
}
void applicationHandler::setStartTime(unsigned long time)
{
    start_time = time;
}
