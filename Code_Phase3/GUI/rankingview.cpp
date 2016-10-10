#include "rankingview.h"
#include "rankingview_ui.h"


RankingView::RankingView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingView),
    rankFromClient(myClient->getMsgServer())
{
    ui->setupUi(this,rankFromClient);
}

RankingView::RankingView(Client *myCl,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingView),
    myClient(myCl),
    rankFromClient(myClient->getMsgServer())
{
    ui->setupUi(this,rankFromClient);
}

RankingView::~RankingView()
{
    delete ui;
}


void RankingView::closeEvent(QCloseEvent *bar){
    emit closeRankingSignal();
}
