#include "gui.h"
#include "ui_gui.h"
#include "signupdialog.h"
#include "mainmenu.h"
#include "signindialog.h"
#include <iostream>
#include "graphicalcard.h"

using namespace std;

Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);


}

Gui::Gui(Client* myCl, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui),
    myClient(myCl)
{
    ui->setupUi(this);
}


Gui::~Gui()
{
    delete ui;
    delete myClient;
}

void Gui::on_signUpButton_clicked()
{
    signUpDialog signUpDia(myClient);
    signUpDia.setModal(true);
    signUpDia.exec();
}

void Gui::on_signInButton_clicked()
{
    signInDialog signInDia(myClient);
    signInDia.setModal(true);
    signInDia.exec();
    //On vérifie la connection
    if (myClient->getMsgServer() == "connectionMenu"){
        //Nothing
    }
    else if (myClient->getMsgServer() == "OK"){
        myClient->receiveFromServer();  //Recois reponse de connection
        if (myClient->getMsgServer() == "OK"){
            myClient->loadCollection();
            myClient->loadDecks();
            QMessageBox::information(this,tr("Connexion"),
            tr("Connexion acceptee"));
            close(); //Cache le menu de connection ( Triche )
            mainmenu = new mainMenu(myClient);
            mainmenu->show();
        }
    }
    else{
        myClient->receiveFromServer();
        QMessageBox::information(this,tr("Connexion"),
        tr("Connexion refusee !"));
    }
}

void Gui::on_quitButton_clicked()
{
    myClient->sendStringToServer("Quitter");
    close();
}
