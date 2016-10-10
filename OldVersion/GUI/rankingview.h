#ifndef RANKINGVIEW_H
#define RANKINGVIEW_H

#include <QDialog>
#include "client.h"

namespace Ui {
class RankingView;
}

class RankingView : public QDialog
{
    Q_OBJECT

public:
    explicit RankingView(QWidget *parent = 0);
    explicit RankingView(Client* myCl, QWidget *parent = 0);
    ~RankingView();

private:
    Ui::RankingView *ui;
    Client *myClient;
    string rankFromClient;

signals:
    void closeRankingSignal();

private slots:
    void closeEvent(QCloseEvent *bar);

};

#endif // RANKINGVIEW_H
