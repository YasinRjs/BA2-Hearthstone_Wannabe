#ifndef RANKINGVIEW_UI_H
#define RANKINGVIEW_UI_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>

#include <sstream>
#include <iostream>
#include <string>

QT_BEGIN_NAMESPACE

class Ui_RankingView
{
public:
    //Ajout
    string RANG;    //QString::fromStdString(rang);
    int levelRank = 80; //compteur permettant de décaller les rangs vers le bas, sera tjs incrémenter de 35.
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label;

    void setupUi(QDialog *rankingView,string rang)
    {
        RANG = rang;

        if (rankingView->objectName().isEmpty())
            rankingView->setObjectName(QString("rankingView"));
        rankingView->resize(448, 498);
        QFont font;
        font.setKerning(true);
        rankingView->setFont(font);
        QIcon icon;
        icon.addFile(QString(":/img/img/wizardPokerLogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        rankingView->setWindowIcon(icon);
        rankingView->setAutoFillBackground(true);
        rankingView->setStyleSheet(QString("background: url(:/img/img/menuBg.png); background-position: fixed"));

        createGroupBox(rankingView);
        retranslateTitleUi(rankingView, "N\302\260","Id en ligne","Victoires","D\303\251faites","Ratio");
        addRanking(rankingView);

        QMetaObject::connectSlotsByName(rankingView);
    } // setupUi

    void addRanking(QDialog *rankingView)
    {
        istringstream iss(RANG);
        string line;
        while (std::getline( iss, line) )
        {
            istringstream iss2(line);
            string word;
            string rank[5];
            int i = 0;
            while(std::getline(iss2, word, ' '))
            {
                rank[i] = word;
                ++i;
            }
            createGroupBox(rankingView);
            retranslateTitleUi(rankingView, rank[0], rank[1], rank[2], rank[3], rank[4]);
        }
    }

    void createGroupBox(QDialog *rankingView)
    {
        groupBox = new QGroupBox(rankingView);
        groupBox->setObjectName(QString("groupBox"));
        groupBox->setGeometry(QRect(20, levelRank, 421, 31));
        groupBox->setAutoFillBackground(false);
        groupBox->setStyleSheet(QString("background: rgb(182, 182, 182,70)"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString("label_2"));
        label_2->setGeometry(QRect(10, 0, 51, 31));
        label_2->setStyleSheet(QLatin1String("background: transparent;\n"
"color: rgb(255, 255, 255);"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString("label_3"));
        label_3->setGeometry(QRect(70, 0, 171, 31));
        label_3->setStyleSheet(QLatin1String("background: transparent;\n"
"color: rgb(255, 255, 255);"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString("label_4"));
        label_4->setGeometry(QRect(250, 0, 51, 31));
        label_4->setStyleSheet(QLatin1String("background: transparent;\n"
"color: rgb(255, 255, 255);"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString("label_5"));
        label_5->setGeometry(QRect(310, 0, 51, 31));
        label_5->setStyleSheet(QLatin1String("background: transparent;\n"
"color: rgb(255, 255, 255);"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString("label_6"));
        label_6->setGeometry(QRect(370, 0, 51, 31));
        label_6->setStyleSheet(QLatin1String("background: transparent;\n"
"color: rgb(255, 255, 255);"));
        label = new QLabel(rankingView);
        label->setObjectName(QString("label"));
        label->setGeometry(QRect(20, 30, 81, 51));
        label->setContextMenuPolicy(Qt::DefaultContextMenu);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString("background: transparent;color: rgb(255, 255, 255);"));

        levelRank += 35;
    }

    void retranslateTitleUi(QDialog *rankingView, string lvl, string id, string victory, string defeat, string ratio)
    {
        rankingView->setWindowTitle(QApplication::translate("rankingView", "Classement", 0));
        groupBox->setTitle(QString());
        label_2->setText(QString::fromStdString(lvl));
        label_3->setText(QString::fromStdString(id));
        label_4->setText(QString::fromStdString(victory));
        label_5->setText(QString::fromStdString(defeat));
        label_6->setText(QString::fromStdString(ratio));
        label->setText(QApplication::translate("rankingView", "<html><head/><body><p><span style=\" font-weight:600; text-decoration: underline;\">CLASSEMENT</span></p></body></html>", 0));
    } // retranslateUi
};

namespace Ui {
    class RankingView: public Ui_RankingView {};
} // namespace Ui

QT_END_NAMESPACE


#endif // RANKINGVIEW_UI_H
