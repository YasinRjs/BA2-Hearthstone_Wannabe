#include "collectiongui.h"
#include "graphicalcard.h"
#include "ui_collectiongui.h"

CollectionGUI::CollectionGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionGUI)
{
    ui->setupUi(this);
}

//Va être utilisé en client server
CollectionGUI::CollectionGUI(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionGUI),
    myClient(myCl)
{
    ui->setupUi(this);
    //testCards();
    test30Cards();
}

CollectionGUI::~CollectionGUI()
{
    delete ui;    
}

void CollectionGUI::testCards(){
    QString test[10] = {"Yasin A.;4;9;9", "Jacky T.;7;7;7", "Youcef B.;4;7;1","Miguel T.;4;5;3", "Sacha M.;2;3;2","Jalal N.;3;3;5","Youssef S.;2;2;1","Keno M.;6;5;6","Jacopo D.;4;6;6","Francois G.;7;4;7"};
    ui->upF->addWidget(new GraphicalCard(this, test[0].toStdString()));
    ui->upF->addWidget(new GraphicalCard(this, test[1].toStdString()));
    ui->upS->addWidget(new GraphicalCard(this, test[2].toStdString()));
    ui->upS->addWidget(new GraphicalCard(this, test[3].toStdString()));
    ui->downF->addWidget(new GraphicalCard(this, test[4].toStdString()));
    ui->downF->addWidget(new GraphicalCard(this, test[5].toStdString()));
    ui->downS->addWidget(new GraphicalCard(this, test[6].toStdString()));
    ui->downS->addWidget(new GraphicalCard(this, test[7].toStdString()));
    ui->upF->addWidget(new GraphicalCard(this, test[8].toStdString()));
    ui->upF->addWidget(new GraphicalCard(this, test[9].toStdString()));
    ui->upS->addWidget(new GraphicalCard(this, test[5].toStdString()));
    ui->upS->addWidget(new GraphicalCard(this, test[4].toStdString()));
    ui->downF->addWidget(new GraphicalCard(this, test[6].toStdString()));
    ui->downF->addWidget(new GraphicalCard(this, test[1].toStdString()));
    ui->downS->addWidget(new GraphicalCard(this, test[2].toStdString()));
    ui->downS->addWidget(new GraphicalCard(this, test[3].toStdString()));
    ui->upF->addWidget(new GraphicalCard(this, test[0].toStdString()));
    ui->upS->addWidget(new GraphicalCard(this, test[2].toStdString()));
    ui->downF->addWidget(new GraphicalCard(this, test[4].toStdString()));
    ui->downS->addWidget(new GraphicalCard(this, test[6].toStdString()));
}

void CollectionGUI::test30Cards(){
    QHBoxLayout* list[20];
    list[0] = ui->upF;
    list[1] = ui->downF;
    list[2] = ui->upS;
    list[3] = ui->downS;
    list[4] = ui->upT;
    list[5] = ui->downT;
    list[6] = ui->upFo;
    list[7] = ui->downFo;
    list[8] = ui->upFi;
    list[9] = ui->downFi;
    list[10] = ui->upSix;
    list[11] = ui->downSix;
    list[12] = ui->upSeven;
    list[13] = ui->downSeven;
    list[14] = ui->upE;
    list[15] = ui->downE;
    list[16] = ui->upN;
    list[17] = ui->downN;
    list[18] = ui->upTen;
    list[19] = ui->downTen;

    int indice;
    int id;
    string parsedCard;
    for(int i=0;i<100;++i){
        indice = 0;
        id = myClient->getCollection().getCard(i);
        myClient->sendStringToServer(to_string(id));
        myClient->receiveFromServer();
        parsedCard = myClient->getMsgServer();
        while(i+1-(5*(indice+1)) > 0){
            indice += 1;
        }
        list[indice]->addWidget(new GraphicalCard(this, parsedCard));
    }
}

void CollectionGUI::closeEvent(QCloseEvent *bar){
    emit closeCollecGuiSignal();
}

void CollectionGUI::on_Retour_clicked()
{
    close();
}
