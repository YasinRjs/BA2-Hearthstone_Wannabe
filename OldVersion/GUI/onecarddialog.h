#ifndef ONECARDDIALOG_H
#define ONECARDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include "graphicalcard.h"

namespace Ui {
class OneCardDialog;
}

class OneCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneCardDialog(QWidget *parent = 0);
    explicit OneCardDialog(Client* myCl, QWidget *parent = 0);
    ~OneCardDialog();

private slots:
    void on_validerButton_clicked();

    void on_quitterButton_clicked();
    void addMyWidg(QWidget*);
    void removeMyWidg();
    void setMyRound();
    void closeEvent(QCloseEvent *bar);

private:
    Ui::OneCardDialog *ui;
    Client* myClient;
    QWidget* myWidg = nullptr;
    int myRound = 0;

signals:
    void closeOneCardSignal();

};

#endif // ONECARDDIALOG_H
