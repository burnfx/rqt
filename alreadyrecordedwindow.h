#ifndef ALREADYRECORDEDWINDOW_H
#define ALREADYRECORDEDWINDOW_H

#include <QDialog>

namespace Ui {
class alreadyRecordedWindow;
}

class alreadyRecordedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit alreadyRecordedWindow(QWidget *parent = 0);
    ~alreadyRecordedWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::alreadyRecordedWindow *ui;
};

#endif // ALREADYRECORDEDWINDOW_H
