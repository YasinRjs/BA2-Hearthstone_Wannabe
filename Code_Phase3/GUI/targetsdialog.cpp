#include "targetsdialog.h"
#include "ui_targetsdialog.h"

TargetsDialog::TargetsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetsDialog)
{
    ui->setupUi(this);
}

TargetsDialog::TargetsDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetsDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    showTargets();
}

TargetsDialog::~TargetsDialog()
{
    delete ui;
}

void TargetsDialog::showTargets(){
    if ( ui->ennemyBoard->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->ennemyBoard->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
    ui->ennemyBoard->addWidget(new GraphicalCard(this,"Ennemi;0;0;0"));

    string ennemyBoardString = myClient->getMsgServer();
    string token;
    string delimiter = "_";
    size_t pos = 0;
    GraphicalCard* card;
    while ((pos = ennemyBoardString.find(delimiter)) != std::string::npos) {
        token = ennemyBoardString.substr(0, pos);
        ennemyBoardString.erase(0, pos + delimiter.length());
        card = new GraphicalCard(this,token);
        ui->ennemyBoard->addWidget(card);
    }
    if (ennemyBoardString.size() > 4){
        pos = ennemyBoardString.find(delimiter);
        ennemyBoardString.erase(0,pos+delimiter.length());
        ui->ennemyBoard->addWidget(new GraphicalCard(this,token));
    }
}

void TargetsDialog::on_retourButton_clicked()
{
    close();
}

void TargetsDialog::closeEvent(QCloseEvent *bar){
    if (forceClose){
        myClient->sendStringToServer("mainMenu");
    }
}

void TargetsDialog::on_attaquerButton_clicked()
{
    string chosenCard = (ui->chosenTarget->text()).toStdString();
    if (stoi(chosenCard)>=0 && stoi(chosenCard)-1 < myClient->getTargetSize()){
        myClient->sendStringToServer(chosenCard);
        forceClose = 0;
        close();
    }
    else{
        QMessageBox::information(this,tr("Attention"),
        tr("Cette carte n'existe pas !"));
    }
}
