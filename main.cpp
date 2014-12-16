#include "testWindow.h"
#include <QApplication>
#include "applicationhandler.h"
#include "client.h"

int main(int argc, char *argv[])
{
    startClient();
    QApplication a(argc, argv);
    applicationHandler appHND;
    testWindow w(&appHND);
    w.show();

    return a.exec();
}
