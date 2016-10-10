#include "signupdialog.h"
#include "ui_signupdialog.h"

signUpDialog::signUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUpDialog)
{
    ui->setupUi(this);
}

signUpDialog::signUpDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUpDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    ui->setupUi(this);
    QFile stylesheet(":/style/style/style.css");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
    setStyleSheet(style);
}

signUpDialog::~signUpDialog()
{
    delete ui;
}

void signUpDialog::on_trySignUp_clicked()
{
    myClient->sendStringToServer("SignUp");
    //Essayer de se connecter.
    //Vérifier les inputs avec la base de donnée.
    QString txt = ui->passwordText->text();
    if(txt.size() < 4) {
        QMessageBox::information(this,tr("Inscription"),
        tr("Votre mot de passe doit avoir une longeur minimal de 4!"));
    }
    else {
        txt = ui->usernameText->text();
        myClient->sendStringToServer(txt.toStdString());
        myClient->receiveFromServer();
        if (myClient->getMsgServer() == "OK"){
            txt = ui->passwordText->text();
            myClient->sendStringToServer(txt.toStdString());
            QMessageBox::information(this,tr("Inscription"),
            tr("Votre compte a ete cree avec succes !"));
        }
        else{
            QMessageBox::information(this,tr("Inscription"),
            tr("Nom d'utilisateur deja existant !"));
        }
    }
    close();
}
