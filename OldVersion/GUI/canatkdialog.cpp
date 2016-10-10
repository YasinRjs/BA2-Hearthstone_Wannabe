#include "canatkdialog.h"
#include "ui_canatkdialog.h"

CanAtkDialog::CanAtkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CanAtkDialog)
{
    ui->setupUi(this);
}

CanAtkDialog::CanAtkDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CanAtkDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    showCanAtk();
}

CanAtkDialog::~CanAtkDialog()
{
    delete ui;
}

void CanAtkDialog::showCanAtk(){
    if ( ui->canAtk->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->canAtk->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
    string canAtkString = myClient->getMsgServer();
    string token;
    string delimiter = "_";
    size_t pos = 0;
    GraphicalCard* card;
    while ((pos = canAtkString.find(delimiter)) != std::string::npos) {
        token = canAtkString.substr(0, pos);
        canAtkString.erase(0, pos + delimiter.length());
        card = new GraphicalCard(this,token);
        ui->canAtk->addWidget(card);
    }
    if (canAtkString.size() > 4){
        pos = canAtkString.find(delimiter);
        canAtkString.erase(0,pos+delimiter.length());
        ui->canAtk->addWidget(new GraphicalCard(this,token));
    }
}

void CanAtkDialog::on_choseButton_clicked()
{
    string chosenMinion = (ui->chosenMinion->text()).toStdString();
    int canAtkSize = myClient->getCanAtk();
    if (chosenMinion.size() > 0 && stoi(chosenMinion)>0 && stoi(chosenMinion)-1 < canAtkSize){
        myClient->sendStringToServer(chosenMinion);
        myClient->receiveFromServer();
        myClient->setTargetSize(stoi(myClient->getMsgServer()));
        myClient->sendStringToServer("OK");
        forceClose = 0;
        close();
        myClient->receiveFromServer();
        TargetsDialog targetsDia(myClient);
        targetsDia.setModal(true);
        targetsDia.exec();
    }
    else{
        QMessageBox::information(this,tr("Attention"),
        tr("Cette carte n'existe pas !"));
    }
}

void CanAtkDialog::closeEvent(QCloseEvent *bar) // lorsqu'on ferme la fenêtre
{
    if (forceClose){
        myClient->sendStringToServer("mainMenu");
    }
}

void CanAtkDialog::on_retourButton_clicked()
{
    close();
}
