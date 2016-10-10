#ifndef CHOSEDECKDIALOG_H
#define CHOSEDECKDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include "client.h"
#include "graphicalcard.h"
#include "waitingopponentdialog.h"

namespace Ui {
class choseDeckDialog;
}

class choseDeckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit choseDeckDialog(QWidget *parent = 0);
    explicit choseDeckDialog(Client* myCl,DuelWindow* dw,QWidget *parent = 0);
    ~choseDeckDialog();
    void loadDecks();


private slots:
    void on_lancerButton_clicked();

    void on_lancerButton_2_clicked();

    void closeEvent(QCloseEvent *bar);


private:
    Ui::choseDeckDialog *ui;
    Client* myClient;
    waitingOpponentDialog* waitOppDial;


signals:
    void closeChoseDeckSignal();


};

#endif // CHOSEDECKDIALOG_H
