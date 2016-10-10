#ifndef CARD_HPP
#define CARD_HPP

#include <QJsonObject>

typedef struct CardIdentity {
    int id;
    QString name;
    QString description;
    int energyCost;
    QString artwork; // Only necessary for interface
} CardIdentity;

class Card
{
public:
    CardIdentity type;
    Card();
    Card(QJsonObject);
    ~Card();

private:
    static int id;
    QJsonObject creator;
};

#endif // CARD_HPP
