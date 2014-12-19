#ifndef APPLICATIONHANDLER_H
#define APPLICATIONHANDLER_H

#include <QDebug>
#include "client.h"
#include "recordNames.h"
#include <stdlib.h>


class applicationHandler
{
public:
    applicationHandler();

    static char* stringtoChar(std::string str);
    static char* QStringtoChar(QString qstr);

    void closeGUI();
    void sendToServer(QString str);
    void selectVideoTrack(int blockNum, int seqNum);
    //void playPauseTrack(int run_flag);
    //void stopTrack();
    void debugHandle();
    void setRedGreen(QString str);
    void setTime(QString str);
    void setFile(QString str);
    void setMode(QString str);
    void setControl(QString str);
    void setReduction(QString str);
    void setUpdateInterval(QString str);
    void setcDecay(QString str);
    void setViewport_Offset(QString str);
    void setTranslateBack_Offset(QString str);

private:
    // int *client;
};

#endif // APPLICATIONHANDLER_H
