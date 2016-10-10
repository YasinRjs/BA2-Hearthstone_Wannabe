#include "graphicalcard.h"
#include "ui_graphicalcard.h"

GraphicalCard::GraphicalCard(QWidget *parent, string base) :
    QWidget(parent),
    ui(new Ui::GraphicalCard)
{
    ui->setupUi(this);
    setStyleSheet("transparent");
    // On aura fait un demande au serveur, et il nous envoie la carte en format string
    // Il serait nteresante de les recevoir toutes au debut partie
    // Du coup client utiliserait ici directement la classe CardGUI
    // Le string recu sous le format "Name;Cost;Attack;HP"
    string delim = ";";
    string baseNOid = base;
    int index = baseNOid.find(delim);
    type.name = baseNOid.substr(0, index);
    string baseNOid_name = baseNOid.substr(index+1, baseNOid.size());
    index = baseNOid_name.find(delim);
    type.energyCost = atoi(baseNOid_name.substr(0, index).c_str());
    string getAttack = baseNOid_name.substr(index+1, baseNOid_name.size());
    index = getAttack.find(delim);
    type.attack = atoi(getAttack.substr(0, index).c_str());
    string getHP = getAttack.substr(index+1, getAttack.size());
    type.hp = atoi(getHP.c_str());

    // Aspect graphique
    ui->attkNum->display(type.attack);
    ui->costNum->display(type.energyCost);
    ui->hpNum->display(type.hp);
    ui->name->setText(QString::fromStdString(type.name));
    checkLegendaryCard();
}

GraphicalCard::~GraphicalCard()
{
    delete ui;
}

void GraphicalCard::changeId(int id){
    ui->id->setText(QString::number(id));
}

void GraphicalCard::checkLegendaryCard(){
    string name = type.name;
    if (name == "Yasin A."){
        ui->art->setStyleSheet("background:url(:/img/img/yasin.jpg)");
    }
    else if (name == "Jacky T."){
        ui->art->setStyleSheet("background:url(:/img/img/jacky.jpg)");
    }
    else if (name == "Youcef B."){
        ui->art->setStyleSheet("background:url(:/img/img/youcef.png)");
    }
    else if (name == "Miguel T."){
        ui->art->setStyleSheet("background:url(:/img/img/miguel.jpg)");
    }
    else if (name == "Keno M."){
        ui->art->setStyleSheet("background:url(:/img/img/keno.jpg)");
    }
    else if (name == "Francois G."){
        ui->art->setStyleSheet("background:url(:/img/img/francois.jpg)");
    }
    else if (name == "Jacopo D."){
        ui->art->setStyleSheet("background:url(:/img/img/jacopo.jpg)");
    }
    else if (name == "Yves R."){
        ui->art->setStyleSheet("background:url(:/img/img/roggeman.jpg)");
    }
    else if (name == "Boris N."){
        ui->art->setStyleSheet("background:url(:/img/img/boris.jpg)");
    }
    else if (name == "Cedric S."){
        ui->art->setStyleSheet("background:url(:/img/img/cedric.jpg)");
    }
    else if (name == "Abde El."){
        ui->art->setStyleSheet("background:url(:/img/img/abdel.jpg)");
    }
    else if (name == "Cheater"){
        ui->art->setStyleSheet("background:url(:/img/img/cheater.jpg)");
    }
}
