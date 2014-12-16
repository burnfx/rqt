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
    //void playPauseTrack(int run_flag);
    //void stopTrack();
    void debugHandle();
    void setRedGreen(int arg1);
    void setFile(char *file);
    void setControl(char *param);
    void setReduction(char *str);
    void setUpdateInterval(char *str);
    void setcDecay(char *str);
    void setViewport_Offset(char *str);
    void setTranslateBack_Offset(char *str);

private:
    // int *client;
};

#endif // APPLICATIONHANDLER_H
