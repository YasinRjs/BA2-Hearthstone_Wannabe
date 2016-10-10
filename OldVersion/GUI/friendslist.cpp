#include "friendslist.h"
#include "ui_friendslist.h"
#include "mainmenu.h"

FriendsList::FriendsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsList)
{
    ui->setupUi(this);
}

FriendsList::FriendsList(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendsList),
    myClient(myCl)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(msgSignal(QString)),this, SLOT(receiveMsg(QString)));
}


void FriendsList::setFriendsList(){
    ui->OnlineBox->clear();
    myClient->sendMsgToChatManager(const_cast<char*>("1"));
    int userIndex = 0;
    while(strcmp(myClient->getMsgSendChat(),"&")){
        myClient->receiveFromChatManager();
        myClient->sendConfirmation(myClient->getSendChatfd());
        if (strcmp(myClient->getMsgSendChat(),"&")){
            QString qUsername = QString::fromStdString(myClient->getMsgSendChat());
            ui->OnlineBox->addItem(qUsername);

        }
        ++userIndex;
    }
    myClient->resetMsgSendChat();

}

FriendsList::~FriendsList()
{
    delete ui;
}

void FriendsList::on_RefreshButton_clicked()
{
    setFriendsList();
}

void FriendsList::on_lineEdit_returnPressed()
{
    string recipient = ui->OnlineBox->currentText().toStdString();
    string text = ui->lineEdit->text().toStdString();
    ui->lineEdit->clear();
    if (recipient != "" && text != ""){
        myClient->sendMsgToChatManager(const_cast<char*>(recipient.c_str()));
        myClient->receiveFromChatManager();
        if (!strcmp(myClient->getMsgSendChat(), "OK")){
            myClient->sendMsgToChatManager(const_cast<char*>(text.c_str()));
            myClient->receiveFromChatManager();
            string chat = "Vers " + recipient + ": " + text;
            QString qChat = QString::fromStdString(chat);
            ui->chatBrowser->append(qChat);
            }
        else{
            string chat = recipient + " s'est déconnecté...";
            QString qChat = QString::fromStdString(chat);
            ui->chatBrowser->append(qChat);
            setFriendsList();
        }
    }
}

void FriendsList::chatReception(){
    while (strcmp(myClient->getMsgRecvChat(),"")){
        myClient->receiveMsgFromPlayer();
        if (strcmp(myClient->getMsgRecvChat(),"")){
            string username = myClient->getMsgRecvChat();
            myClient->sendConfirmation(myClient->getRecvChatfd());
            myClient->receiveMsgFromPlayer();
            myClient->sendConfirmation(myClient->getRecvChatfd());
            string text = myClient->getMsgRecvChat();
            string chat = "["+username+"]: "+text;
            QString qChat = QString::fromStdString(chat);
            emit msgSignal(qChat);
        }
        else{
            cout << endl<< "\x1B[31m\033[1m";
            cout << "La connexion avec le serveur a été perdue. (Le serveur a été coupé).";
            cout << "\033[0m\x1B[0m" << endl;
        }
    }
}


void FriendsList::receiveMsg(QString qChat){
    ui->chatBrowser->append(qChat);
    show();
}
