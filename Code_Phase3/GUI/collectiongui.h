#ifndef COLLECTIONGUI_H
#define COLLECTIONGUI_H

#include <QDialog>
#include "client.h"

namespace Ui {
class CollectionGUI;
}

class CollectionGUI : public QDialog
{
    Q_OBJECT

public:
    explicit CollectionGUI(QWidget *parent = 0);
    explicit CollectionGUI(Client* myCl, QWidget *parent = 0);
    ~CollectionGUI();
    void testCards();
    void test30Cards();

private:
    Ui::CollectionGUI *ui;
    Client* myClient;

private slots:
    void closeEvent(QCloseEvent *bar);

    void on_Retour_clicked();

signals:
    void closeCollecGuiSignal();

};

#endif // COLLECTIONGUI_H
