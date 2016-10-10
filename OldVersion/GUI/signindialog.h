#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>
#include <QFile>
#include "client.h"

namespace Ui {
class signInDialog;
}

class signInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit signInDialog(QWidget *parent = 0);
    explicit signInDialog(Client* myCl, QWidget *parent = 0);
    ~signInDialog();
    void closeEvent(QCloseEvent *bar);

private slots:
    void on_trySignIn_clicked();

private:
    Ui::signInDialog *ui;
    Client* myClient;
    int forceClose = 1;
};

#endif // SIGNINDIALOG_H
