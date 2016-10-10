#include "Ranking.hpp"

Ranking::Ranking() : serverRanking(vector<User*>()){}

Ranking::Ranking(vector<User*> users) : serverRanking(vector<User*>()){
	initServerRanking(users);
	updateRanking();
	//printRanking();       //Si on veut afficher le ranking à la construction serveur.
}


void Ranking::initServerRanking(vector<User*> users){
	for (size_t i = 0; i < users.size(); ++i){
		serverRanking.push_back(users[i]);
	}
}

void Ranking::updateRanking() {	//Met à jour le classement au moyen d'un tri fusion.
	vector<User*> tmp(serverRanking.size());
	mergeSort(tmp, 0,serverRanking.size()-1);

}
void Ranking::mergeSort(vector<User*> tmp, size_t left, size_t right) {
	if (left < right) {
		size_t mid = (left + right) / 2;
		mergeSort(tmp, left, mid);
		mergeSort(tmp, mid + 1, right);
		merge(tmp, left, mid + 1, right);
	}
}

void Ranking::merge(vector<User*> tmp, size_t left, size_t right, size_t rightEnd) {
	size_t leftEnd = right - 1;
	size_t k = left;
	size_t num = rightEnd - left + 1;
	while((left <= leftEnd) && (right <= rightEnd)) {
		if(serverRanking[left]->getRatio() < serverRanking[right]->getRatio())
			tmp[k++] = serverRanking[left++];
		else
			tmp[k++] = serverRanking[right++];
	}
	while(left <= leftEnd)
		tmp[k++] = serverRanking[left++];

	while(right <= rightEnd)
		tmp[k++] = serverRanking[right++];

	for(size_t i = 0; i < num; i++, rightEnd--)
		serverRanking[rightEnd] = tmp[rightEnd];
}

void Ranking::printRanking() {	//affiche le classement.
	cout << "~~~ Afffichage du classement ~~~" << endl;
	cout << "~~~ Victoires - Défaites = Nombres de points ~~~" << endl;
	int j = 1;
	for(size_t i = 0; i < serverRanking.size(); ++i) {
		size_t k = serverRanking.size() - 1 - i;
		cout << setColor(j);
		cout << j << ". : " << serverRanking[k]->getUsername() << " -> " << serverRanking[k]->getVictory() 
		<< ":" << serverRanking[k]->getDefeat() << endl;
		++j;
		cout << endColor();
	}
	cout << "-----------------------------" << endl;
}

string Ranking::getRanking(){
	vector<User*> tmp(serverRanking.size());
	mergeSort(tmp, 0,serverRanking.size()-1);
	string ranking = "";
	int j = 1;
	for (size_t i = 0; i < serverRanking.size(); ++i){
		size_t k = serverRanking.size() - 1 - i;		
		ranking += setColor(j);
		ranking += to_string(j) + ". : " + serverRanking[k]->getUsername() + " -> " + to_string(serverRanking[k]->getVictory())
		+ ":" + to_string(serverRanking[k]->getDefeat()) + "\n";
		++j;
		ranking += endColor();
	}
	return ranking;
}

string Ranking::setColor(int j){
	string color = "";
	if ( j == 1 ){
		color = "\x1B[36m\033[1m";	//Bleu BG
	}
	else if ( j == 2 ){
		color = "\x1B[35m\033[1m";	// Magenta
	}
	else if ( j == 3 ){
		color = "\x1B[31m\033[1m";	//RED
	}
	else{
		color = "\x1B[33m\033[1m";
	}
	return color;
}

string Ranking::endColor(){
	string color = "\033[0m\x1B[0m";
	return color;
}

int Ranking::searchPlayer(string id) {	//renvois son index dans le classement
	bool found = false;
	int res = -1;
	int unsigned i = 0;	//vector.size() renvois un non signé.(cf Comparaison ci-dessous)
	while((i < serverRanking.size()) && (!found)) {	
		if (serverRanking[i]->getId() == id) {
			res = i;
			found = true;
		}
		++i;
	}
	return res;	
}

void Ranking::updatePlayer(User* user) {	//Met à jour un joueur.
	int index = searchPlayer(user->getId());
	if( index > -1) {
		serverRanking[index] = user;
		updateRanking();
	}
}

void Ranking::addPlayer(User* user) {	//Ajout d'un joueur au classement.
	if(searchPlayer(user->getId()) == -1) {
		serverRanking.push_back(user);
		updateRanking();
	}
}
