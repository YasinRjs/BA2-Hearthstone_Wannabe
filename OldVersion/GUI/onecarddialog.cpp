#include "onecarddialog.h"
#include "ui_onecarddialog.h"

OneCardDialog::OneCardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OneCardDialog)
{
    ui->setupUi(this);
}

OneCardDialog::OneCardDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OneCardDialog),
    myClient(myCl)
{
    ui->setupUi(this);
}

OneCardDialog::~OneCardDialog()
{
    delete ui;
}

void OneCardDialog::on_validerButton_clicked()
{
    QString id = ui->cardID->text();
    string idStr = id.toStdString();
    if (stoi(idStr) < 0 || stoi(idStr) > 99){
        QMessageBox::information(this,tr("Voir une carte"),
        tr("Vous ne possedez pas cette carte dans votre collection !"));
    }
    else{
        myClient->sendStringToServer("2");
        myClient->receiveFromServer();
        myClient->sendStringToServer("3");
        if (myRound){
            removeMyWidg();
            setMyRound();
        }
        myClient->sendStringToServer(idStr);
        myClient->receiveFromServer();
        myClient->sendStringToServer("Continue");
        string parsedCard = myClient->getMsgServer();
        QWidget* myWidg = new GraphicalCard(this,parsedCard);
        ui->upF->addWidget(myWidg);
        addMyWidg(myWidg);
    }
}

void OneCardDialog::on_quitterButton_clicked()
{
    close();
}

void OneCardDialog::removeMyWidg(){
    ui->upF->removeWidget(myWidg);
}

void OneCardDialog::addMyWidg(QWidget* widg){
    myRound = 1;
    myWidg = widg;
}

void OneCardDialog::setMyRound(){
    myRound = 0;
}

void OneCardDialog::closeEvent(QCloseEvent *bar){
    emit closeOneCardSignal();
}
