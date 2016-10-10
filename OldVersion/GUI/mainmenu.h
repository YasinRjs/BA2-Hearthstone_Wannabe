#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include "client.h"
#include "collectiongui.h"
#include "rankingview.h"
#include "chosedeckdialog.h"
#include "collectionmenudialog.h"
#include "friendslist.h"
#include <pthread.h>
#include <vector>

class choseDeckDialog;

namespace Ui {
class mainMenu;
}

class mainMenu : public QDialog
{
    Q_OBJECT

public:
    friend void* receiveChatGUI(void* arg);
    friend void* adsManagerMainMenu(void* arg);
    explicit mainMenu(QWidget *parent = 0);
    explicit mainMenu(Client* myCl, QWidget *parent = 0);
    ~mainMenu();
   void startReception();
   void startAds();
   void adsManagement();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_duelButton_clicked();

    void on_chatButton_clicked();

    void closeEvent(QCloseEvent *bar);

    void finishGame();

    void closeCollection();

    void closeRanking();

    void changeAd(int);


private:
    pthread_t chatThread = 0;
    pthread_t adsThread = 0;
    Ui::mainMenu *ui;
    vector<QPixmap> adVector;
    Client *myClient;
    FriendsList* friendsList;
    choseDeckDialog* choseDeckDial;
    CollectionMenuDialog* collection;
    RankingView* ranking;
    int menuOpen = 1;

signals:
    void changeAdSignal(int);

};

#endif // MAINMENU_H
