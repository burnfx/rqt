#ifndef testWindow_H
#define testWindow_H

#include <QMainWindow>
#include "usermanagement.h"
#include "testexecution.h"
#include "applicationhandler.h"

namespace Ui {
class testWindow;
}

class testWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit testWindow(applicationHandler *appHND, QWidget *parent = 0);
    ~testWindow();
    QStringList getUserList();
    void updateUserList(QString userName, int addNewIfOne);
    void setCurrentUser(QString userName);
    std::string getDBentry(QString userName);
    const char *userDBFileName;

private slots:
    void on_closeCMDB_clicked();
    void on_applyCMDB_clicked();
    void on_defaultCMDB_clicked();
    void on_userCMDB_clicked();
    void on_userCBX_currentTextChanged(const QString &arg1);
    void on_testCMDB_1_clicked();
    void on_testCMDB_2_clicked();
    void on_testCMDB_3_clicked();
    void on_testCMDB_7_clicked();
    void on_testCMDB_4_clicked();
    void on_testCMDB_5_clicked();
    void on_testCMDB_6_clicked();
    void on_testCMDB_8_clicked();
    void on_testCMDB_9_clicked();

    void on_check_1_stateChanged(int arg1);

    void on_recordCMDB_clicked();

    void on_stopCMDB_clicked();

    void on_setFileCMDB_clicked();

    void on_setModeCMDB_clicked();

private:
    Ui::testWindow *ui;
    userManagement *um;
    TestExecution *te;
    applicationHandler *appHND;
    QStringList userList;
};

#endif // testWindow_H
