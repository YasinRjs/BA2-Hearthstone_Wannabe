#ifndef VIEWDECKSDIALOG_H
#define VIEWDECKSDIALOG_H

#include <QDialog>
#include "client.h"
#include "graphicalcard.h"

namespace Ui {
class viewDecksDialog;
}

class viewDecksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit viewDecksDialog(QWidget *parent = 0);
    explicit viewDecksDialog(Client* myCl, QWidget *parent = 0);
    ~viewDecksDialog();
    void loadDecks();

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *bar);

private:
    Ui::viewDecksDialog *ui;
    Client* myClient;

signals:
    void closeViewDeckSignal();
};

#endif // VIEWDECKSDIALOG_H
