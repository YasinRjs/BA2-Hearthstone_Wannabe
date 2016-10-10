#ifndef COLLECTIONMENUDIALOG_H
#define COLLECTIONMENUDIALOG_H

#include <QDialog>
#include "client.h"
#include "collectiongui.h"
#include "onecarddialog.h"
#include "viewdecksdialog.h"
#include "createdeckdialog.h"
#include "deletedeckdialog.h"
#include <vector>
#include <pthread.h>
#include "decktomodify.h"

class DeckToModify;

namespace Ui {
class CollectionMenuDialog;
}

class CollectionMenuDialog : public QDialog
{
    Q_OBJECT

public:
    friend void* adsManagerCollecMenu(void* arg);
    explicit CollectionMenuDialog(QWidget *parent = 0);
    explicit CollectionMenuDialog(Client* myCl, vector<QPixmap> adVector, QWidget *parent = 0);
    void startAds();
    void adsManagement();
    ~CollectionMenuDialog();

private slots:
    void on_mainMenuButton_clicked();

    void on_viewCollectionButton_clicked();

    void on_viewCardButton_clicked();

    void on_viewDecksButton_clicked();

    void on_createDeckButton_clicked();

    void on_deleteDeckButton_clicked();

    void closeEvent(QCloseEvent *bar);

    void closeCollecGui();

    void closeOneCard();

    void closeViewDeck();

    void closeCreateDeck();

    void closeDeleteDeck();

    void changeAd(int i);

    void closeDeckToModify();

    void on_modifyDeckButton_clicked();


signals:
    void closeCollectionSignal();
    void changeAdSignal(int i);


private:
    pthread_t adsThread = 0;
    Ui::CollectionMenuDialog *ui;
    Client* myClient;
    vector<QPixmap> adVector;
    CollectionGUI* collecGui;
    OneCardDialog* oneCard;
    viewDecksDialog* viewDeck;
    CreateDeckDialog* createDeck;
    DeleteDeckDialog* deleteDeck;
    DeckToModify* whichDeck;
};

#endif // COLLECTIONMENUDIALOG_H
