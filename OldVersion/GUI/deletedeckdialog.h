#ifndef DELETEDECKDIALOG_H
#define DELETEDECKDIALOG_H

#include <QDialog>
#include "client.h"

namespace Ui {
class DeleteDeckDialog;
}

class DeleteDeckDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::DeleteDeckDialog *ui;
    Client *myClient;

public:
    explicit DeleteDeckDialog(QWidget *parent = 0);
    explicit DeleteDeckDialog(Client* myCl, QWidget *parent = 0);
    ~DeleteDeckDialog();
    void disableButtonDeckEmpty();

private slots:
    void closeEvent(QCloseEvent *bar);

    void on_deck1Button_clicked();

    void on_deck2Button_clicked();

    void on_deck3Button_clicked();

    void on_deck4Button_clicked();

    void on_deck5Button_clicked();

    void on_exitButton_clicked();

signals:
    void closeDeleteDeckSignal();

};

#endif // DELETEDECKDIALOG_H
