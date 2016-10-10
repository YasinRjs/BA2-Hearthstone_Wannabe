#ifndef TARGETSDIALOG_H
#define TARGETSDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPixmap>
#include "client.h"
#include "graphicalcard.h"

namespace Ui {
class TargetsDialog;
}

class TargetsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TargetsDialog(QWidget *parent = 0);
    explicit TargetsDialog(Client* myCl, QWidget *parent = 0);
    ~TargetsDialog();
    void showTargets();

private slots:
    void on_retourButton_clicked();
    void closeEvent(QCloseEvent *);

    void on_attaquerButton_clicked();

private:
    Ui::TargetsDialog *ui;
    Client* myClient;
    int forceClose = 1;
};

#endif // TARGETSDIALOG_H
