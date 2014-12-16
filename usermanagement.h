#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

namespace Ui {
class userManagement;
}

class userManagement : public QDialog
{
    Q_OBJECT

public:
    explicit userManagement(const char *dbFile, QStringList userList, QWidget *parent = 0);
    ~userManagement();
    int extractUserId(std::string line);

private slots:
    void on_closeCMDB_clicked();
    void on_okCMDB_clicked();
    void on_delCMDB_clicked();
    void on_userCBX_currentTextChanged(const QString &arg1);

    void on_userNewCB_clicked();

private:
    Ui::userManagement *ui;
    const char *userDBFileName;
    const char *userDBCopyName;
};

#endif // USERMANAGEMENT_H
