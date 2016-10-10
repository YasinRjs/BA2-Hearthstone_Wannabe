#ifndef FRIENDSLIST_H
#define FRIENDSLIST_H

#include <QDialog>
#include "client.h"

namespace Ui {
class FriendsList;
}

class FriendsList : public QDialog
{
    Q_OBJECT


public:
    explicit FriendsList(QWidget *parent = 0);
    explicit FriendsList(Client* myCl, QWidget *parent = 0);
    void setFriendsList();
    void chatReception();

    ~FriendsList();

private slots:
    void on_RefreshButton_clicked();

    void on_lineEdit_returnPressed();

    void receiveMsg(QString);

signals:
    void msgSignal(QString);

private:
    Ui::FriendsList *ui;
    Client* myClient;
};

#endif // FRIENDSLIST_H

