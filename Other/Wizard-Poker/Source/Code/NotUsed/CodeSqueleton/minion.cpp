#include "minion.hpp"

Minion::Minion() {
   hp = creator["baseHp"].toInt();
   attack = creator["baseAttack"].toInt();
}

int Minion::receiveDamage(int suffer) {
    hp -= suffer;
    if (hp > 0) return 1; // Minion still alive
    return 0; // Minion is dead
}
