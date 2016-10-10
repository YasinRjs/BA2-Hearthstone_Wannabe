#ifndef DECKTOMODIFY_H
#define DECKTOMODIFY_H

#include <QDialog>
#include "viewonedeck.h"
#include "collectionmenudialog.h"

class CollectionMenuDialog;

namespace Ui {
class DeckToModify;
}

class DeckToModify : public QDialog
{
    Q_OBJECT

public:
    explicit DeckToModify(QWidget *parent = 0);
    explicit DeckToModify(Client* myCl,CollectionMenuDialog* cm, QWidget *parent = 0);
    void loadDecks();
    ~DeckToModify();

private slots:
    void on_lancerButton_clicked();
    void closeEvent(QCloseEvent *bar);
    void closeOneDeck();
signals:
    void closeDeckToModifySignal();


private:
    Ui::DeckToModify *ui;
    Client *myClient;
    CollectionMenuDialog* collecMenu;
    viewOneDeck *vod = nullptr;
};

#endif // DECKTOMODIFY_H
