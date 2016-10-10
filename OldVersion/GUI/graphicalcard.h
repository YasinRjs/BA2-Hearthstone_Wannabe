#ifndef GRAPHICALCARD_H
#define GRAPHICALCARD_H

#include <QWidget>
#include <QPixmap>
#include "card.h"

namespace Ui {
class GraphicalCard;
}

class GraphicalCard : public QWidget
{
    Q_OBJECT


public:
    explicit GraphicalCard(QWidget *parent = 0, string base="-1;No;0;0;0");
    ~GraphicalCard();
    void showCard();
    void hideCard();
    void checkLegendaryCard();

private:
    Ui::GraphicalCard *ui;
    CardIdentity type;
};

#endif // GRAPHICALCARD_H
