#ifndef testWindow_H
#define testWindow_H

#include <QMainWindow>
#include "usermanagement.h"
#include "testexecution.h"
#include "applicationhandler.h"
#include "testexecbutton.h"
#include "alreadyrecordedwindow.h"

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
    void updateExecutedTests();
    void updateUserList(QString userName, int addNewIfOne);
    void setCurrentUser(QString userName);
    std::string getDBentry(QString userName);
    const char *userDBFileName;

private slots:
    void on_closeCMDB_clicked();
    void on_userCMDB_clicked();
    void on_userCBX_currentTextChanged(const QString &arg1);
    void openTestRecordingWindow(int bNum);
    void on_check_1_stateChanged(int arg1);
    void exRecordUpdate();
    void on_recordCMDB_clicked();
    void on_stopCMDB_clicked();
    void on_setFileCMDB_clicked();
    void on_setModeCMDB_clicked();

    void on_start_test_button_clicked();

private:
    Ui::testWindow *ui;
    userManagement *um;
    TestExecution *te;
    applicationHandler *appHND;
    QStringList userList;
    testExecButton *start_test_button;
};

#endif // testWindow_H
