#ifndef CREATEDECKDIALOG_H
#define CREATEDECKDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"
#include <vector>

namespace Ui {
class CreateDeckDialog;
}

class CreateDeckDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::CreateDeckDialog *ui;
    Client* myClient;
    vector<int> vectId;

public:
    explicit CreateDeckDialog(QWidget *parent = 0);
    explicit CreateDeckDialog(Client* myCl, QWidget *parent = 0);
    ~CreateDeckDialog();
    void collectionView();

private slots:
    void closeEvent(QCloseEvent *bar);

    void on_addButton_clicked();

    void on_validateButton_clicked();

    void on_exitButton_clicked();

signals:
    void closeCreateDeckSignal();

};

#endif // CREATEDCKDIALOG_H
