#include "card.hpp"

Card::Card(QJsonObject json) {
    creator = json;
    QString theName = json["name"].toString();
    QString desc = json["description"].toString();
    QString theId = json["id"].toString();
    int manaCost = json["baseManaCost"].toInt();

    this->type.artwork = ":/Images/"+theId+".jpg";
    this->type.description = desc;
    this->type.energyCost = manaCost;
    //this->type.id = Card::id;
    this->type.name = theName;
    //++Card::id;
}
