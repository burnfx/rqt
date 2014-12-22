#include "testWindow.h"
#include <QApplication>
#include "applicationhandler.h"
#include "client.h"
#include "guistartup.h"

int main(int argc, char *argv[])
{
    /* Unmake comments in the following files / functions:
     * void applicationHandler::closeGUI()
     * void applicationHandler::sendToServer(QString qstr)
     * client.h
     * client.cpp
     * and beneath this one here. */
    //startClient();
    QApplication a(argc, argv);
    applicationHandler appHND;
    guiStartup g(&appHND);
    g.setModal(true);
    // if test mode was not selected close GUI
    if (g.exec()!=QDialog::Accepted)
    {
        appHND.closeGUI();
        return a.exec();
    }

    testWindow w(&appHND);
    w.show();
    return a.exec();
}
