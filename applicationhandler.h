#ifndef APPLICATIONHANDLER_H
#define APPLICATIONHANDLER_H

#include <QDebug>
#include "client.h"

class applicationHandler
{
public:
    applicationHandler();

    void closeGUI();
    void selectVideoTrack(int blockNum, int seqNum);
    void playPauseTrack(int run_flag);
    void stopTrack();
    void debugHandle();
    void setRedGreen(int arg1);

private:
    // int *client;
};

#endif // APPLICATIONHANDLER_H
