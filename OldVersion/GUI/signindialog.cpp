#include "signindialog.h"
#include "ui_signindialog.h"

signInDialog::signInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signInDialog)
{
    ui->setupUi(this);
}

signInDialog::signInDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signInDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    QFile stylesheet(":/style/style/style.css");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
    setStyleSheet(style);
}

signInDialog::~signInDialog()
{
    delete ui;
}

void signInDialog::on_trySignIn_clicked()
{
    myClient->sendStringToServer("SignIn");
    QString txt = ui->usernameText->text();
    string txtString = txt.toStdString();
    myClient->setUsername(txtString);
    myClient->sendStringToServer(txtString);
    myClient->receiveFromServer();
    txt = ui->passwordText->text();
    txtString = txt.toStdString();
    myClient->setPassword(txtString);
    myClient->sendStringToServer(txtString);
    myClient->receiveFromServer();
    //-------------------------------------
    myClient->sendStringToServer("OK");
    forceClose = 0;
    close();
}

void signInDialog::closeEvent(QCloseEvent *bar){
    if (forceClose){
        myClient->setMsg("connectionMenu");
    }
    forceClose = 1;
}
