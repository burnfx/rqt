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
    static char* qstringtoChar(QString qstr);

    void closeGUI();
    void sendToServer(char *str);
    void selectVideoTrack(int blockNum, int seqNum);
    //void playPauseTrack(int run_flag);
    //void stopTrack();
    void debugHandle();
    void setRedGreen(int arg1);
    void setTime(char *time);
    void setFile(char *file);
    void setMode(char *mode);
    void setControl(char *param);
    void setReduction(char *str);
    void setUpdateInterval(char *str);
    void setcDecay(char *str);
    void setViewport_Offset(int value);
    void setTranslateBack_Offset(char *str);

private:
    // int *client;
};

#endif // APPLICATIONHANDLER_H
