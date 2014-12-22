#ifndef CLOSEWINDOW_H
#define CLOSEWINDOW_H

#include <QDialog>

namespace Ui {
class closeWindow;
}

class closeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit closeWindow(QWidget *parent = 0);
    ~closeWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::closeWindow *ui;
};

#endif // CLOSEWINDOW_H
