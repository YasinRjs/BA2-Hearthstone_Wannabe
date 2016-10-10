#ifndef PLAYONECARDDIALOG_H
#define PLAYONECARDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include "graphicalcard.h"

namespace Ui {
class PlayOneCardDialog;
}

class PlayOneCardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayOneCardDialog(QWidget *parent = 0);
    explicit PlayOneCardDialog(Client* myClient, QWidget *parent = 0);
    ~PlayOneCardDialog();

private slots:
    void on_retourButton_clicked();
    void showHand();
    void closeEvent(QCloseEvent *bar);

    void on_pushButton_clicked();

private:
    Ui::PlayOneCardDialog *ui;
    Client* myClient;
};

#endif // PLAYONECARDDIALOG_H
