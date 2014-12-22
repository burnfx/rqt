#ifndef SAVECLOSEWINDOW_H
#define SAVECLOSEWINDOW_H

#include <QDialog>

namespace Ui {
class saveCloseWindow;
}

class saveCloseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit saveCloseWindow(QWidget *parent = 0);
    ~saveCloseWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::saveCloseWindow *ui;
};

#endif // SAVECLOSEWINDOW_H
