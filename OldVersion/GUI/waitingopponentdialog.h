#ifndef WAITINGOPPONENTDIALOG_H
#define WAITINGOPPONENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <client.h>
#include "duelwindow.h"

namespace Ui {
class waitingOpponentDialog;
}

class DuelWindow;

class waitingOpponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit waitingOpponentDialog(QWidget *parent = 0);
    explicit waitingOpponentDialog(Client* myCl,DuelWindow* dw, QWidget *parent = 0);
    ~waitingOpponentDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::waitingOpponentDialog *ui;
    Client* myClient;
    DuelWindow* duelWind;
};

#endif // WAITINGOPPONENTDIALOG_H
