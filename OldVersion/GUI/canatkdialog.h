#ifndef CANATKDIALOG_H
#define CANATKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include "graphicalcard.h"
#include "targetsdialog.h"

namespace Ui {
class CanAtkDialog;
}

class CanAtkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CanAtkDialog(QWidget *parent = 0);
    explicit CanAtkDialog(Client* myCl, QWidget *parent = 0);
    ~CanAtkDialog();
    void showCanAtk();
    void showTargets();

private slots:
    void on_choseButton_clicked();
    void closeEvent(QCloseEvent *);

    void on_retourButton_clicked();

private:
    Ui::CanAtkDialog *ui;
    Client* myClient;
    int forceClose = 1;
};

#endif // CANATKDIALOG_H
