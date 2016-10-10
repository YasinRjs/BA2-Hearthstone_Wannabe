#include "playonecarddialog.h"
#include "ui_playonecarddialog.h"

PlayOneCardDialog::PlayOneCardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayOneCardDialog)
{
    ui->setupUi(this);
}

PlayOneCardDialog::PlayOneCardDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayOneCardDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    showHand();
}


PlayOneCardDialog::~PlayOneCardDialog()
{
    delete ui;
}

void PlayOneCardDialog::showHand(){
    if ( ui->hand->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->hand->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
    string hand = myClient->getMsgServer();
    string token;
    string delimiter = "---";
    size_t pos = 0;
    GraphicalCard* card;
    while ((pos = hand.find(delimiter)) != std::string::npos) {
        token = hand.substr(0, pos);
        hand.erase(0, pos + delimiter.length());
        card = new GraphicalCard(this,token);
        ui->hand->addWidget(card);
    }
    if (hand.size() > 4){
        token = hand.substr(0,string::npos);
        card = new GraphicalCard(this,token);
        ui->hand->addWidget(card);
    }
}

void PlayOneCardDialog::on_retourButton_clicked()
{
    close();
}

void PlayOneCardDialog::closeEvent(QCloseEvent *bar) // lorsqu'on ferme la fenêtre
{
    myClient->sendStringToServer("mainMenu");
}

void PlayOneCardDialog::on_pushButton_clicked()
{
    string chosenCard = (ui->chosenCard->text()).toStdString();
    if (chosenCard.size() > 0 && stoi(chosenCard)>=0 && stoi(chosenCard)-1 < myClient->getHandSize()){
        myClient->sendStringToServer(chosenCard);
        myClient->receiveFromServer();
        if (myClient->getMsgServer() == "Invoc OK"){
            QMessageBox::information(this,tr("Invocation"),
            tr("Invocation reussie avec succes !"));
            close();
        }
        else{
            QMessageBox::information(this,tr("Invocation"),
            tr("Vous ne pouvez pas invoquer cette carte !"));
            close();
        }
    }
    else{
        //myClient->sendStringToServer("mainMenu");
        QMessageBox::information(this,tr("Attention"),
        tr("Cette carte n'existe pas !"));
        //close();
    }
}

