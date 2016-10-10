#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"


namespace Ui {
class signUpDialog;
}

class signUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit signUpDialog(QWidget *parent = 0);
    explicit signUpDialog(Client* myCl, QWidget *parent =0);
    ~signUpDialog();

private slots:

    void on_trySignUp_clicked();

private:
    Ui::signUpDialog *ui;
    Client* myClient;
};

#endif // SIGNUPDIALOG_H
