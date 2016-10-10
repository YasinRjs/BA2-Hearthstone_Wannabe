#ifndef RANKING_H
#define RANKING_H

#include <iostream>
#include <vector>

#include "user.h"

using namespace std;

class Ranking {
    private:
        vector<User*> serverRanking; // no need de delete, Serveur s'en occupe
    public:
        Ranking();
        Ranking(vector<User*>);
        ~Ranking();
        void initServerRanking(vector<User*>);
        void updateRanking();
        int searchPlayer(string id);
        void updatePlayer(User* user);
        void printRanking();
        string getRanking();
        void addPlayer(User* user);
        void mergeSort(vector<User*> tmp, size_t left, size_t right);
        void merge(vector<User*> tmp, size_t left, size_t right, size_t rightEnd);
        string setColor(int);
        string endColor();
};

#endif // RANKING_H
