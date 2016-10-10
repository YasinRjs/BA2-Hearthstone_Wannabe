#ifndef DUELWINDOW_H
#define DUELWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <vector>
#include "client.h"
#include "graphicalcard.h"
#include "friendslist.h"
#include "playonecarddialog.h"
#include "canatkdialog.h"
#include <QCloseEvent>
#include <pthread.h>

namespace Ui {
class DuelWindow;
}

class DuelWindow : public QDialog
{
    Q_OBJECT

public:
    friend void* waitOpponent(void* arg);
    friend void* adsManagerDuelWindow(void* arg);

    explicit DuelWindow(QWidget *parent = 0);
    explicit DuelWindow(Client* myCl, FriendsList* fl, vector<QPixmap> ads, QWidget *parent = 0);
    ~DuelWindow();
    void startTurn();
    void setCanPlay();
    void cantPlay();

    void refreshBoard();
    void refreshHand();
    void refreshOwnStat(string);
    void refreshEnnemyStat(string);
    void refreshEnnemyBoard(string);
    void refreshOwnBoard(string);
    void startMatch();
    void createWaitingThread();
    Client* getMyClient();
    void setRounds();
    void setNewTurn(int);

    void startAds();
    void adsManagement();


private slots:
    void on_finTourButton_clicked();

    void on_chatButton_clicked();
    void closeEvent(QCloseEvent *bar);

    void startTurnTest();
    void boxEndTurn();
    void boxSurrender();
    void boxDefaite();
    void boxVictoire();
    void boxOpponentTurn();
    void boxISurrender();
    void boxRageQuit();

    void on_abandonButton_clicked();

    void on_jouerButton_clicked();

    void on_attaquerButton_clicked();
    void setForceClose(int);

    void changeAd(int i);


signals:
    void endSignal();
    void threadBoxDefaite();
    void threadBoxVictoire();
    void threadBoxOpponentTurn();
    void threadBoxEndTurn();
    void threadBoxSurrender();
    void threadBoxISurrender();
    void threadBoxRageQuit();
    void threadStartTurn();

    void changeAdSignal(int i);

private:
    pthread_t waitThread = 0;
    pthread_t adsThread = 0;
    Ui::DuelWindow *ui;
    Client* myClient;
    FriendsList* friendslist;
    vector<QPixmap> adVector;
    int gameOver;
    int canPlay;
    int rounds;
    string opponent = "None";
    vector<GraphicalCard*> myCards;
    int newTurn = 1;
    int forceClose = 1;
};

#endif // DUELWINDOW_H
