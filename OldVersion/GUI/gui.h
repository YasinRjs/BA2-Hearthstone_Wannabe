#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QApplication>
#include <QFile>
#include "client.h"
#include "mainmenu.h"


namespace Ui {
class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);

    explicit Gui(Client* myCl, QWidget *parent = 0);
    ~Gui();

private slots:
    void on_signUpButton_clicked();

    void on_signInButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::Gui *ui;
    Client *myClient;
    mainMenu* mainmenu;

};

#endif // GUI_H
