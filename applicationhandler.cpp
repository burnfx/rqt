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
}

void applicationHandler::playPauseTrack(int run_flag)
{
    qDebug() << "applicationHandler says: run_flag = " << run_flag;
    if (run_flag)
    {
        char* str = "-control play";
        sendR(&str);
    }
    else
    {
        char* str = "-control pause";
        sendR(&str);
    }

}

void applicationHandler::stopTrack()
{
    qDebug() << "applicationHandler says: current track stopped";
    char* str = "-control stop";
    sendR(&str);
}

void applicationHandler::setRedGreen(int arg1)
{
    if (arg1 == 2)
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
