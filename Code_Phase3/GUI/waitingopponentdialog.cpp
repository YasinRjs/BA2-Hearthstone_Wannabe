#include "waitingopponentdialog.h"
#include "ui_waitingopponentdialog.h"

waitingOpponentDialog::waitingOpponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitingOpponentDialog)
{
    ui->setupUi(this);
}

waitingOpponentDialog::waitingOpponentDialog(Client* myCl, DuelWindow* dw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitingOpponentDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    myClient->setLaunchDuel(0);
    duelWind = dw;
}

waitingOpponentDialog::~waitingOpponentDialog()
{
    delete ui;
    delete duelWind;
}

void waitingOpponentDialog::on_pushButton_clicked()
{
    myClient->sendStringToServer(myClient->getActiveDeck());
    myClient->receiveFromServer();
    close();
    duelWind->startMatch();
    duelWind->show();
}
