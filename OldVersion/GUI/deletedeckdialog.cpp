#include "deletedeckdialog.h"
#include "ui_deletedeckdialog.h"

DeleteDeckDialog::DeleteDeckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDeckDialog)
{
    ui->setupUi(this);
}

DeleteDeckDialog::DeleteDeckDialog(Client *myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDeckDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    disableButtonDeckEmpty();
}

DeleteDeckDialog::~DeleteDeckDialog()
{
    delete ui;
}

void DeleteDeckDialog::disableButtonDeckEmpty() {
    if(myClient->getDeck(0).isEmpty()) {
        ui->deck1Button->setEnabled(false);
    }
    if(myClient->getDeck(1).isEmpty()) {
        ui->deck2Button->setEnabled(false);
    }
    if(myClient->getDeck(2).isEmpty()) {
        ui->deck3Button->setEnabled(false);
    }
    if(myClient->getDeck(3).isEmpty()) {
        ui->deck4Button->setEnabled(false);
    }
    if(myClient->getDeck(4).isEmpty()) {
        ui->deck5Button->setEnabled(false);
    }
}

void DeleteDeckDialog::on_deck1Button_clicked() {
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("5");
    myClient->removeDeckatIndex(0);
    close();
}

void DeleteDeckDialog::on_deck2Button_clicked() {
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("5");
    myClient->removeDeckatIndex(1);
    close();
}

void DeleteDeckDialog::on_deck3Button_clicked() {
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("5");
    myClient->removeDeckatIndex(2);
    close();
}

void DeleteDeckDialog::on_deck4Button_clicked() {
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("5");
    myClient->removeDeckatIndex(3);
    close();
}

void DeleteDeckDialog::on_deck5Button_clicked() {
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("5");
    myClient->removeDeckatIndex(4);
    close();
}

void DeleteDeckDialog::closeEvent(QCloseEvent *bar){
    emit closeDeleteDeckSignal();
}

void DeleteDeckDialog::on_exitButton_clicked() {
    close();
}
