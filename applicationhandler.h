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
    void selectVideoTrack();
    void selectVideoTrack(int seqNum);
    void selectVideoTrack(int seqNo, int seqQual);
    void playBlackBackground();
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
    unsigned long measureStopTime(int seqNumber);
    static void setStartTime(unsigned long time);

    unsigned long timeForDecision[10][2];
    static unsigned long start_time;

private:
    std::vector<QString> seqNames = {"L0R5","L0R10","L0R20", "L0R40", "L0R80", "L0R5", "L0R10", "L0R20", "L0R40", "L0R80"};
};

#endif // APPLICATIONHANDLER_H
