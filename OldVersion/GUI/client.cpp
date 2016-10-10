#include "client.h"

Client::Client() : my_addr(sockaddr_in()),he(new hostent()),myCollection(Collection())
{}

Client::Client(int argSize,char* ip) : my_addr(sockaddr_in()),he(new hostent()),myCollection(Collection()){
    verifArgs(argSize);
    init(ip);
}

Client& Client::operator=(const Client&){
    return *this;
}

Client::~Client(){}

void Client::verifArgs(int argSize){
    if (argSize < 2){
        cout << "Manque adresse ip" << endl;
        exit(1);
    }
}

Client::Client(const Client&) : my_addr(sockaddr_in()),he(new hostent()),myCollection(Collection())
{}

void Client::init(char* ip){
    if ((he = gethostbyname(ip)) == NULL){
        perror("gethostbyname");
        exit(1);
    }
    if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("socket");
        exit(1);
    }

    if ((rcvChat_fd=socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("socket");
        exit(1);
    }

    if ((sendChat_fd=socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("socket");
        exit(1);
    }
    if ((gameSocket=socket(AF_INET,SOCK_STREAM,0)) == -1){
        perror("socket");
        exit(1);
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(my_addr.sin_zero),'\0',8);
    if ((connect(sockfd, reinterpret_cast<struct sockaddr *>(&my_addr), sizeof(struct sockaddr))) == -1){
      perror("connect");
      cout <<"sockfd"<<endl;
      exit(1);
    }
    if ((connect(rcvChat_fd, reinterpret_cast<struct sockaddr *>(&my_addr), sizeof(struct sockaddr))) == -1){
      perror("connect");
      cout << "RcvChat_fd" << endl;
      exit(1);
    }
    if ((connect(sendChat_fd, reinterpret_cast<struct sockaddr *>(&my_addr), sizeof(struct sockaddr))) == -1){
      perror("connect");
      cout << "sendChat_fd" << endl;
      exit(1);
    }
    if ((connect(gameSocket, reinterpret_cast<struct sockaddr *>(&my_addr), sizeof(struct sockaddr))) == -1){
      perror("connect");
      exit(1);
    }
}

void Client::welcomeMsg(){
    cout << "Bienvenue sur Wizard-Poker !\n- 1 : S'inscrire\n- 2 : Se connecter\n- 3 : Quitter" << endl;
}

void Client::traceLigne(){
    cout << "---------------------------------------" << endl;
}

void Client::traceDiese(){
    cout << "########################################" << endl;
}

void Client::leaveMsg(){
    cout << "Ce jeu est trop difficile pour vous !" << endl;
}

void Client::askConnection(){
    //Réponse du joueur à "se connecter"
    while (strcmp(inputPlayer,"1") && strcmp(inputPlayer,"2") && strcmp(inputPlayer,"3")){
        cout << "Votre réponse (1,2,3) : ";
        cin >> inputPlayer;
    }
}

void Client::sendInputToServer(){
    if (send(sockfd,inputPlayer,MAXDATASIZE-1,0) == -1) {
        perror("recv");
        exit(1);
    }
}

void Client::receiveFromServer(){
    if ((numbytes=recv(sockfd,msgServer,MAXDATASIZE-1,0)) == -1){
        perror("recv");
        exit(1);
    }
    msgServer[numbytes] = '\0';
}

void Client::signIn(){
    strcpy(inputPlayer,"");
    string username;
    //Demande username
    while (!(strcmp(inputPlayer,""))){
        cout << "Nom d'utilisateur : ";
        cin >> inputPlayer;
        username = inputPlayer;
        sendInputToServer();
        receiveFromServer();
        //Mot de Passe
        if (!strcmp(msgServer,"OK")){
            cout <<"Mot de passe : ";
            cin >> inputPlayer;
            sendInputToServer();
            receiveFromServer();
            if (!strcmp(msgServer,"OK")){
                sendInputToServer();
                receiveFromServer();
                if (!strcmp(msgServer,"OK")){
                    traceDiese();
                    cout << "Connection réussie !" << endl;
                    cout << "# Bienvenue ";
                    cout << "\x1B[31m\033[1m" << username << "\033[0m\x1B[0m" << " !" << endl;
                    clientUsername = username;
                    loadCollection();
                    loadDecks();
                    startReception();
                    mainMenu();
                }
                else{
                    cout << "Cet utilisateur est déjà connecté."<<endl;
                    traceLigne();
                    strcpy(inputPlayer,"");

                }
            }
            else{
                cout << "Mot de passe refusé" << endl;
                traceLigne();
                strcpy(inputPlayer,"");
            }
        }
        else{
            cout << "Nom d'utilisateur refusé" << endl;
            traceLigne();
            strcpy(inputPlayer,"");
        }
    }
}

void Client::signUp(){
    strcpy(inputPlayer,"");
    cout << "~~ Vous allez tenter de vous inscrire ~~" << endl;
    while (!(strcmp(inputPlayer,""))){
        cout << "Nom d'utilisateur : ";
        cin >> inputPlayer;
        sendInputToServer();
        receiveFromServer();
        if (!strcmp(msgServer,"OK")){
            string usernameToInitialise = inputPlayer;
            cout << "Mot de passe : ";
            cin >> inputPlayer;
            sendInputToServer();
            cout << "~~~~ Compte créé avec succès ~~~~" << endl;
            cout << "~~~~ Veuillez vous connecter ~~~~" << endl;
            signIn();
        }
        else{
            cout << "Nom d'utilisateur déjà utilisé !" << endl;
            traceLigne();
            strcpy(inputPlayer,"");
        }
    }
}

void Client::loadCollection(){
    receiveFromServer();	// Recoit la collection
    string collection = msgServer;
    string token;
    char delimiter = ',';
    vector<int> mycollection;
    for(unsigned i=0;i<collection.size();++i){
        if (collection[i] == delimiter){
            mycollection.push_back(atoi(token.c_str()));
            token = "";
        }
        else{
            token += collection[i];
        }
    }
    mycollection.push_back(atoi(token.c_str()));
    //End Critical
    myCollection = Collection(mycollection);
    //LoadDecks
}

//-----------------------------------------------------------------------------

void Client::loadDecks(){
    for(int i=0;i<5;++i){
        receiveFromServer();
        string deckStr = msgServer;
        string token;
        char delimiter = ',';
        vector<int> mydeck;
        if (deckStr.size() > 0){
            for(unsigned i=0;i<deckStr.size();++i){
                if (deckStr[i] == delimiter){
                    mydeck.push_back(atoi(token.c_str()));
                    token = "";
                }
                else{
                    token += deckStr[i];
                }
            }
            mydeck.push_back(atoi(token.c_str()));
            myDecks[i] = Deck(mydeck);//TODO Deck(mydeck)
            myBufferDecks[i] = Deck(mydeck);
        }
        else{
            myDecks[i] = Deck(mydeck);
            myBufferDecks[i] = Deck(mydeck);
        }
        sendStringToServer("OK");
    }
}

bool Client::find (int element, vector<int> vect){//OK
    bool found = false;
    for(size_t i = 0;i<vect.size();i++){
        if (vect[i] == element){
            found = true;
        }
    }
    return found;
}

size_t Client::positionOfAnElement(int element ,vector<int> vect){//OK
    size_t j = 0;
    for (size_t i = 0;i<vect.size();i++){
        if (element == vect[i]){
            j = i;
        }
    }
    return j;
}

void Client::printDeck(vector<int> deck){
        for (size_t i = 0; i<deck.size();i++){
            cout<<deck[i]<<" ";
        }
        cout<<endl;
}

void Client::modifyDeck (string usrname){
    int n(0);
    int cardToRemove(0);
    int cardToAdd;
    printDecks();
    while(n<=0 || n>5){
        cout<<"Choisissez un deck à modifier : ";
        cin>>n;
    }
    vector<int> deckToModify = myDecks[n-1].getMyDeck();
    cout << "~~ Choisissez les ID de carte à supprimer du deck." << endl;
    while(cardToRemove != -1 && deckToModify.size()>0){
        cout<<"ID de la carte à supprimer ( -1 pour finir ) : ";
        cin>>cardToRemove;
        if (find(cardToRemove,deckToModify)){
            size_t position = positionOfAnElement(cardToRemove,deckToModify);
            deckToModify.erase(deckToModify.begin()+position);
        }
        else if (!find(cardToRemove,deckToModify) && cardToRemove != -1 ){
            cout<<"Cette carte n'existe pas dans le deck."<<endl;
        }
        else if (cardToRemove == -1){
            cout <<"Vous avez fini votre choix"<<endl;
        }
        printDeck(deckToModify);
    }

    traceLigne();
    printDeck(deckToModify);
    cout << "Choisissez maintenant les cartes à ajouter dans le deck. " << endl;
    while (deckToModify.size()<20){
        cout<< to_string(deckToModify.size()) << "e Carte :";
        cin>>cardToAdd;
        if (find(cardToAdd,myCollection.getAllCards())){
            if (count(cardToAdd,deckToModify) == 0){
                deckToModify.push_back(cardToAdd);
            }

            else if (count(cardToAdd,deckToModify) == 1){

                if (count(cardToAdd,myCollection.getAllCards()) == 2){

                    deckToModify.push_back(cardToAdd);
                }
                else{
                    cout<<"Vous n'avez pas 2 fois cette carte dans votre collection."<<endl;
                }
            }

            else{
                cout<<"Cette carte est déjà présente 2 fois dans le deck."<<endl;

            }
        }
        else{
            cout<<"Cette carte n'est pas présente dans votre collection ."<<endl;
        }
        printDeck(deckToModify);

    }
    myDecks[n-1] = Deck(deckToModify);
    updateDecksFile(usrname);
}

void Client::updateDecksFile(string usrname){
    rename("src/txt/comptesDecks.txt","src/txt/old.txt");
    ifstream in("src/txt/old.txt");
    ofstream out("src/txt/comptesDecks.txt");
    string tmp;
    while(!in.eof()){
        getline(in,tmp);
        if (!strcmp(tmp.c_str(),usrname.c_str())){
            out<<tmp<<endl;
            for(int i = 0;i<5;i++){
                getline(in,tmp);
                vector<int> deck = myDecks[i].getMyDeck();
                if (deck.size()>0){
                    for (int j = 0;j<19;j++){
                        out<<deck[j]<<",";
                    }
                    out<<deck[19];
                    out<<endl;
                }
                else{
                    out<<endl;
                }
            }
        }
        else{
            if (!in.eof()){
                out<<tmp<<endl;
            }
        }
    }
    in.close();
    out.close();
}

void Client::removeDeck(string usrname){
    printDecks();
    char n[10];
    int flag = 0;
    while (flag == 0) {
        do {
            cout<<"Choisissez le deck à supprimer : ";
            cin>>n;
        } while (!isCorrectInput(n));


        if (myDecks[atoi(n)-1].getMyDeck().size() == 0){
            cout<<"Le deck est vide, veuillez choisir un autre !"<<endl;
            flag = 0;
        }
        else{
            cout<<"~~> Le deck " << n << " a été supprimé ! " << endl;
            flag = 1;
        }
    }
    vector<int> emptyDeck;
    myDecks[atoi(n)-1] = Deck(emptyDeck);
    updateDecksFile(usrname);

}

int Client::isCorrectInputForCollecMenu(char* input){
    return (!strcmp(input,"1") || !strcmp(input,"2") || !strcmp(input,"3") \
            || !strcmp(input,"4") || !strcmp(input,"5")|| !strcmp(input,"6"))
            || !strcmp(input,"7");
}

int Client::numberOfDecksFilled(){
    int numOfDecks = 0 ;
    for (int i = 0;i<5;i++){
        if (myDecks[i].getMyDeck().size() > 0){
            ++numOfDecks;
        }
    }
    return numOfDecks ;
}

void Client::fillTheDeckAtPosition(int position){
    vector<int> deckToFill = myDecks[position].getMyDeck();
    int cardToAdd;
    cout<<"~~ Veuillez à respecter les consignes pour un deck ~~ "<<endl;
    while (deckToFill.size()<20){
        cout<< to_string(deckToFill.size()+1) << "e carte : ";
        cin>>cardToAdd;
        //if présente dans la collection
        if (count(cardToAdd,deckToFill) == 0){
            deckToFill.push_back(cardToAdd);
        }
        else if (count(cardToAdd,deckToFill) == 1){
            if (count(cardToAdd,myCollection.getAllCards()) == 2){
                deckToFill.push_back(cardToAdd);
            }
            else{
                cout<<"--> Vous n'avez pas cette carte 2 fois."<<endl;
            }
        }
        else{
            cout<<"--> Maximum 2 fois la même carte dans un deck."<<endl;
        }
        printDeck(deckToFill);
        myDecks[position] = Deck(deckToFill);
    }
}

int Client::count(int element,vector<int> vector){//OK
    int c = 0;
    for (unsigned int i = 0;i<vector.size();i++){
        if (vector[i] == element){
            c++;
        }
    }
    return c;
}

int Client::emptyDeckAtPosition(){
    int j = -1;
    int i = 0;
    bool found = false;
    while (i<5 && !found){
        if (myDecks[i].getMyDeck().size() == 0){
            found =  true;
            j = i;
        }
        i+=1;
    }
    return j;
}

void Client::createNewDeck(string username){
    if (numberOfDecksFilled() < 5){
        int position  = emptyDeckAtPosition();
        fillTheDeckAtPosition(position);
        updateDecksFile(username);
        cout << "--> Création de deck terminé avec succès ! " << endl;
    }
    else{
        cout<<"Les 5 decks sont remplis.\nSupprimez en un pour en créer un nouveau. "<<endl;
    }
}

void Client::printRanking(){
    receiveFromServer();
    //cout << "\x1B[34m\033[1m";	// BLUE
    //cout << "~~~~ Classement ~~~~";
    //cout << "\033[0m\x1B[0m" << endl;
    cout << msgServer;
}

void Client::mainMenu(){
    while (strcmp(inputPlayer,"5")){
        int flag = 1;
        cout << "\x1B[34m\033[1m";	// BLUE
        cout << "~~~~ Main Menu ~~~~";
        cout << "\033[0m\x1B[0m" << endl;
        cout << "- 1 : Recherche d'un adversaire" << endl;
        cout << "- 2 : Collection" << endl;
        cout << "- 3 : Discuter" << endl;
        cout << "- 4 : Classement" << endl;
        cout << "- 5 : Quitter le jeu" << endl;

        while (flag){
            cout << "Votre Réponse ( 1,2,3,4 ou 5 ) : ";
            cin >> inputPlayer;
            if (isCorrectInput(inputPlayer)){
                flag = 0;
            }
        }
        sendInputToServer();
        if (!strcmp(inputPlayer,"1")){
            string activeDeck;
            cout << "--- Veuillez choisir un deck pour participer ---" << endl;
            int currentDeck = choseDeck();
            activeDeck = convertDeckToString(currentDeck);
            sendStringToServer(activeDeck);
            findOpponent();

            strcpy(inputPlayer,"mainMenu");
        }
        else if (!strcmp(inputPlayer,"2")){
            collectionMenu();
        }
        else if (!strcmp(inputPlayer,"3")){
            startChat();
        }
        else if (!strcmp(inputPlayer,"4")){
            printRanking();
        }
        else if (!strcmp(inputPlayer,"5")){
            cout << "~~ Quitter le jeu ~~" << endl;
            leaveMsg();
            //disconnect()  --- Enlever de la liste des personnes en ligne ---
        }
    }
}

void Client::sendStringToServer(string msg){
    if ((send(sockfd,msg.c_str(),MAXDATASIZE-1,0)) == -1) {
        perror("recv");
        exit(1);
    }
}

void Client::printCollection(){
    cout << "\x1B[31m\033[1m";
    cout << "Liste des IDs disponible dans votre Collection" << endl;
    traceLigne();
    myCollection.printCollection();
    traceLigne();
    cout << "\033[0m\x1B[0m";
}

string Client::convertDeckToString(int indiceDeck){
    int cardInDeck = 20;
    string deckString;
    for(int i=0;i<cardInDeck;++i){
        deckString += to_string((myDecks[indiceDeck].giveDeck())[i]);
        if (i+1<cardInDeck){
            deckString += ",";
        }
    }
    return deckString;
}

void Client::collectionMenu(){
    cout << "\x1B[34m\033[1m";	// BLUE
    cout << "~~~~ Collection Menu ~~~~";
    cout << "\033[0m\x1B[0m" << endl;
    cout << "- 1 : Voir sa collection" << endl;
    cout << "- 2 : Voir ses decks" << endl;
    cout << "- 3 : Voir une carte" << endl;
    cout << "- 4 : Créer un deck" << endl;
    cout << "- 5 : Supprimer un deck" << endl;
    cout << "- 6 : Modifier un deck" << endl;
    cout << "- 7 : Menu principal" << endl;
    int flag = 1;
    while (flag){
        cout << "Votre Réponse ( 1,2,3,4,5,6 ou 7) : ";
        cin >> inputPlayer;
        if (isCorrectInputForCollecMenu(inputPlayer)){
            flag = 0;
        }
    }
    sendInputToServer();
    if (!strcmp(inputPlayer,"1")){
        printCollection();
    }
    else if (!strcmp(inputPlayer,"2")){
        showOneDeck();
    }
    else if (!strcmp(inputPlayer,"3")){
        showOneCard();
    }
    else if (!strcmp(inputPlayer,"4")){//TODO
        createNewDeck(clientUsername);
    }
    else if (!strcmp(inputPlayer,"5")){
        removeOneDeck();
    }
    else if (!strcmp(inputPlayer,"6")){
        modifyDeck(clientUsername);
    }
    strcpy(inputPlayer,"mainMenu");
}

void Client::showOneCard(){
    cout << "~ Vous devez posséder la carte dans votre collection." << endl;
    do{
        cout << "Veuillez donner l'ID d'une carte : ";
        cin >> inputPlayer;
    } while (!hasIDinCollection(atoi(inputPlayer)));
    cout << "--- ID " << inputPlayer << " ---" << endl;
    sendInputToServer();
    receiveFromServer();
    cout << msgServer << endl;
}

void Client::showOneDeck(){
    receiveFromServer();	//OK
    int chosenDeck = choseDeck();
    cout << "~~~~ Votre deck ~~~~" << endl;
    int deckSize = myDecks[chosenDeck].getSize();
    for(int i=0;i<deckSize;++i){
        int pos = myDecks[chosenDeck].getCard(i);
        sendStringToServer(to_string(pos));
        receiveFromServer();
        cout << i+1 << "e Carte : " << msgServer;
        if (i+1==deckSize){
            sendStringToServer("End");
        }
        else{
            sendStringToServer("NotOver");
        }
        receiveFromServer();
    }
    strcpy(inputPlayer,"mainMenu");
}

void Client::removeOneDeck(){
    cout << "~~ Veuillez choisir un deck à supprimer ~~" << endl;
    if (numberOfDecksFilled() > 1){
        removeDeck(clientUsername);
    }
    else{
        cout<<"Vous devez au moins avoir un deck non vide ! "<<endl;
    }
}

int Client::choseDeck(){
    printDecks();
    cout << "Votre réponse ( 1,2,3,4 ou 5 ) : ";
    cin >> inputPlayer;
    while (!isCorrectInput(inputPlayer)){
        cout << "~~ Stop abuser du programme ~~" << endl;
        cout << "Votre réponse ( 1,2,3,4 ou 5 ) : ";
        cin >> inputPlayer;
    }
    return atoi(inputPlayer)-1;
}

bool Client::canPutInDeck(vector<int> deck,int id){
    bool permission;
    if (count(id,deck) == 0){
        permission = true;
    }
    else if (count(id,deck) == 1){
        if (count(id,myCollection.getAllCards()) == 2){
            permission = true;
        }
        else{
            permission = false;
        }
    }
    else{
        permission = false;
    }
    return permission;
}

void Client::createNewDeckFromVector(vector<int> listId, string username) {
    int position  = emptyDeckAtPosition();
    for(int i = 0; i < DECKSIZE; i++) {
        myDecks[position].addCardinDeck(listId[i]);
    }
    sendStringToServer(username);
    sendStringToServer(to_string(position));
    for(int i = 0; i < DECKSIZE; i++) {
        sendStringToServer(to_string(listId[i]));
    }
}

void Client::createNewDeckNumber(int indexDeck){

/*
    Reste à faire des vérifications ( Max 2 fois la même carte dans deck ),
    * Vérifier si la carte est dispo dans la collection, mais si elle est déjà utilisé, vérifier si on l'a une deuxieme fois.
    * Zone critique quand il écrira sur le fichier des decks.
    * Egalement corriger . atoi() renvoie 0 si il recoit une chaine de charactere quelconque, donc trouver un moyen de vérif ça.
*/

    removeDeckatIndex(indexDeck);
    cout << "Attention, les cartes doivent être disponible dans votre collection" << endl;
    for(int i=1;i<21;++i){
        cout << i <<"e carte : ";
        cin >> inputPlayer;
        while (!hasIDinCollection(atoi(inputPlayer))){
            cout << i <<"e carte : ";
            cin >> inputPlayer;
        }
        addIDinDeck(indexDeck,atoi(inputPlayer));
    }
    cout << "~~~ Nouveau deck créé avec succès à l'emplacement : " << indexDeck << "  ~~~" << endl;
}

void Client::removeDeckatIndex(int indexDeck) {
    myDecks[indexDeck].removeDeck();
    sendStringToServer(username);
    sendStringToServer(to_string(indexDeck));
}

int Client::hasIDinCollection(int ID){
    return myCollection.hasID(ID);
}

void Client::addIDinDeck(int indexDeck,int ID){
    myDecks[indexDeck].addCardinDeck(ID);
}

void Client::printDecks(){
    cout << "\x1B[31m\033[1m";
    traceLigne();
    cout << "Liste des IDs pour chaque Deck" << endl;
    for(int i=0;i<NUMBEROFDECK;++i){
        cout << "Deck " << i+1 << " : " << endl;
        cout << "\t";
        if (myDecks[i].getMyDeck().size()>0){
            myDecks[i].printDeck();
            cout << endl;
        }
        else{
            cout << endl;
        }
    }
    traceLigne();
    cout << "\033[0m\x1B[0m";
}

int Client::isCorrectInput(char* input){
    return (!strcmp(input,"1") || !strcmp(input,"2") || !strcmp(input,"3") \
            || !strcmp(input,"4") || !strcmp(input,"5"));
}

//-----------------------------------------------------

void Client::sendConfirmation(int socketfd){
    if (send(socketfd,"ok",2,0) == -1) {
        perror("recv");
        exit(1);
    }
}

void* receiveChat(void* arg){
    Client* clientPtr = reinterpret_cast<Client*>(arg);
    clientPtr->chatReception();
    exit(0);
//	pthread_exit(NULL);
}

void Client::startReception(){
    pthread_create(&chatThread,nullptr,receiveChat,reinterpret_cast<void*>(this));
}

void Client::receiveMsgFromPlayer(){
    if ((rcvNumbytes=recv(rcvChat_fd,msgRcvChat,MAXDATASIZE-1,0)) == -1){
        perror("recv chat");
        exit(1);
    }
    msgRcvChat[rcvNumbytes] = '\0';
}


void Client::chatReception(){
    strcpy(msgRcvChat,"RECEPTION");
    while (strcmp(msgRcvChat,"")){
        receiveMsgFromPlayer();
        if (strcmp(msgRcvChat,"")){
            cout << endl << "\x1B[32m\033[1m";	// GREEN
            cout << "[" << msgRcvChat << "]: ";
            sendConfirmation(rcvChat_fd);
            receiveMsgFromPlayer();
            cout << msgRcvChat << "\033[0m\x1B[0m" << endl;
            sendConfirmation(rcvChat_fd);
        }
        else{
            cout << endl<< "\x1B[31m\033[1m";
            cout << "La connexion avec le serveur a été perdue. (Le serveur a été coupé).";
            cout << "\033[0m\x1B[0m" << endl;
        }
    }
}
//-----------------------------------------------------------------------------

void Client::sendMsgToChatManager(char* msg){
if (send(sendChat_fd,msg, MAXDATASIZE-1,0) == -1) {
    perror("recv");
    exit(1);
    }
}

void Client::receiveFromChatManager(){
    if ((sendNumbytes=recv(sendChat_fd,msgSendChat,MAXDATASIZE-1,0)) == -1){
        perror("recv");
        exit(1);
    }
    msgSendChat[sendNumbytes] = '\0';
}

void Client::startChat(){
    cout << "\x1B[34m\033[1m";	// BLUE
    cout << "~~~~ Chat ~~~~";
    cout << "\033[0m\x1B[0m" << endl;
    int userIndex = 1;
    cout << "Joueurs connectés: ";
    strcpy(msgSendChat, "");
    while(strcmp(msgSendChat,"&")){
        receiveFromChatManager();
        sendConfirmation(sendChat_fd);
        if (strcmp(msgSendChat,"&")){
            cout<<userIndex<<"."<<msgSendChat<<" ";
        }
        userIndex += 1;
    }
    cout << endl;
    strcpy(inputPlayer,"");
    while (strcmp(inputPlayer,"0")){
        cout << "Entrez le chiffre du joueur (0 = quitter): ";
        cin >> inputPlayer;
        int answer = atoi(inputPlayer);
        if ((0 < answer) && (answer < userIndex - 1)){
            sendMsgToChatManager(inputPlayer);
            receiveFromChatManager();
            if (!strcmp(msgSendChat, "OK")){
                giveMsg();
                receiveFromChatManager();
                if (!strcmp(msgSendChat, "NO")){	//RED
                    cout << "\x1B[31m\033[1mLe joueur s'est déconnecté...\033[0m\x1B[0m" << endl;
                }
            }
            else{	// RED
                cout << "\x1B[31m\033[1mLe joueur s'est déconnecté...\033[0m\x1B[0m" << endl;
            }

            strcpy(inputPlayer,"0");
        }
        else if (!strcmp(inputPlayer,"0")){
            sendMsgToChatManager(inputPlayer);
        }

        else{
            cout << "Réponse refusée..." << endl;
            traceLigne();
        }
    }
}

void Client::giveMsg(){
    receiveFromChatManager();
    cout << "\x1B[32m\033[1m"; // GREEN
    cout << "Entrez votre message pour " << msgSendChat << ": ";
    string input;
    getline(cin, input);
    getline(cin, input);
    cout << "\033[0m\x1B[0m";
    sendMsgToChatManager(const_cast<char*>(input.c_str()));
}

void Client::findOpponent(){
    cout << "Recherche d'un adversaire ..."<<endl;
    receiveFromServer();
    cout << "Adversaire trouvé !" <<endl;
    cout << "\x1B[36m\033[1m#################################";
    cout << msgServer << endl;
    cout << "#################################\033[0m\x1B[0m"<<endl;
    startGame();
}

void Client::printGameStarting(){
    cout << "\x1B[31m\033[1m";
    cout << "===============       BON CHONCE       ... ==============" << endl;
    cout << "=============== LA PARTIE VA COMMENCER ... ==============" << endl;
    cout << "===============       BON CHONCE       ... ==============" << endl;
    cout << "\033[0m\x1B[0m" << endl;
}

int Client::askPlayCard(){
    return (!strcmp(inputPlayer,"1"));
}

int Client::isMyTurn(){
    return (!strcmp(msgServer,"1"));
}

int Client::isWaitingTurn(){
    return (!strcmp(msgServer,"0"));
}

void Client::choseMenu(){
    receiveFromServer();
    cout << msgServer << endl;
    sendStringToServer("OK");
    receiveFromServer();
    cout << msgServer << endl;
    cout << "- 1 : Jouer une carte\n";
    cout << "- 2 : Attaquer\n";
    cout << "- 3 : Discuter\n";
    cout << "- 4 : Fin de tour\n";
    cout << "- 5 : Abandonner\n";
    do {
        cout << "Votre réponse ( 1,2,3,4 ou 5 ) : ";
        cin >> inputPlayer;
    } while (!isCorrectInput(inputPlayer));
    sendInputToServer();
}

void Client::choseCard(){
    receiveFromServer();
    int handSize = atoi(msgServer);
    sendStringToServer("OK");
    receiveFromServer();
    cout << msgServer << endl;
    do {
        cout << "Votre carte à jouer ( 0 à " << to_string(handSize-1) << " ) : ";
        cin >> inputPlayer;
    } while (atoi(inputPlayer)<0 || atoi(inputPlayer)>=handSize);

    sendInputToServer();
    strcpy(inputPlayer,"menu");
    receiveFromServer();
    cout << "\x1B[31m\033[1m";
    cout << msgServer;
    cout << "\033[0m\x1B[0m" << endl;
    sendConfirmation(sockfd);
    receiveFromServer();
    if (!strcmp(msgServer,"NO")){
        strcpy(inputPlayer,"4");
    }
}

int Client::askAttack(){
    return (!strcmp(inputPlayer,"2"));
}

void Client::choseTarget(){
    receiveFromServer();	// Recois nbre ennemi
    int nbrTarget = atoi(msgServer);
    sendStringToServer("OK");
    receiveFromServer();
    cout << msgServer << endl;
    do{
        cout << "Votre cible ( 0 à " << to_string(nbrTarget-1) << " ) : ";
        cin >> inputPlayer;
    } while (atoi(inputPlayer)<0 || atoi(inputPlayer)>=nbrTarget);
    sendInputToServer();
    if (!strcmp(inputPlayer,"0")){
        receiveFromServer();
        if (!strcmp(msgServer,"Win")){
            gameOver = 1;
        }
    }
}

void Client::choseMinion(){
    int nbrCanAtk = atoi(msgServer);
    receiveFromServer();
    cout << msgServer << endl;		// Ses monstres capable d'attaquer;
    do{
        cout << "Votre monstre qui doit attaquer ( -1 pour revenir ) : ";
        cin >> inputPlayer;
    } while (strcmp(inputPlayer,"-1") && (atoi(inputPlayer) < 0 || atoi(inputPlayer) >= nbrCanAtk));
    sendInputToServer();
}

void Client::choseMinionAndTarget(){
    //Choix de la personne qui va attack;
    receiveFromServer();
    int nbrCanAtk = atoi(msgServer);
    if (nbrCanAtk > 0){
        choseMinion();
        if (strcmp(inputPlayer,"-1")){
            choseTarget();
        }
    }
    else{
        cout << "\x1B[31m\033[1m";
        cout << "----- Vous n'avez pas de créature capable d'attaquer ! -----" << endl;
        cout << "\033[0m\x1B[0m" << endl;
    }

}

int Client::askChat(){
    return (!strcmp(inputPlayer,"3"));
}

int Client::finishTurn(){
    return (!strcmp(inputPlayer,"4"));
}

void Client::surrender(){
    gameOver = 1;
    cout << "\x1B[31m\033[1m";
    cout << "---------- Quel tristesse, l'abandon n'était pas une option ... ----------" << endl;
    cout << "\033[0m\x1B[0m" << endl;
}

void Client::endTurn(){
    cout << "---> Fin de votre tour \n\n";
}

void Client::waitingTurn(){
    receiveFromServer();
    cout << msgServer << endl;
    cout << "\x1B[31m\033[1m";
    cout << "----------------------------------------------------------";
    cout << "\033[0m\x1B[0m" << endl;
    cout << "En attente de votre tour ..." << endl;
}

void Client::printWinning(){
    cout << "\x1B[31m\033[1m";
    traceLigne();
    traceLigne();
    cout << "\tWINNERRRRRRRRRRRRRRR !!!!!!!!!! " << endl;
    traceLigne();
    traceLigne();
    cout << "\033[0m\x1B[0m" << endl;
}

void Client::printLosing(){
    cout << "\x1B[31m\033[1m";
    traceLigne();
    traceLigne();
    cout << "\tLOSERRRRRRRRRRRRRRRR !!!!!!!!!!" << endl;
    traceLigne();
    traceLigne();
    cout << "\033[0m\x1B[0m" << endl;
}

void Client::actionMenu(){
    while (!gameOver && strcmp(inputPlayer,"4")){
        choseMenu();
        if (askPlayCard()){
            choseCard();
        }
        else if (askAttack()){
            choseMinionAndTarget();
        }
        else if (askChat()){
            startChat();
        }
        else if (finishTurn()){
            endTurn();
        }
        else{
            surrender();
            //Abandonner ? POURQUOI !!!
        }
    }
}

void Client::infoEndGame(){
    cout << "\x1B[36m\033[1m";
    do{
        receiveFromServer();
        sendStringToServer("OK");
    } while (atoi(msgServer) <= 0);
    cout << "~~~ Vous avez joué " << msgServer << " tours ! ~~~";
    cout << "\033[0m\x1B[0m" << endl;
}

void Client::infoSurrender(){
    cout << "\x1B[36m\033[1m";
    receiveFromServer();
    cout << msgServer;
    cout << "\033[0m\x1B[0m" << endl;
}

void Client::infoKill(){
    cout << "\x1B[36m\033[1m";
    receiveFromServer();
    sendStringToServer("OK");
    cout << msgServer;
    cout << "\033[0m\x1B[0m" << endl;
}

void Client::startGame(){
    printGameStarting();
    gameOver = 0;
    while (!gameOver){
        receiveFromServer();
        sendConfirmation(sockfd);	// Pour voir si le client est tjr co
        //C'est son tour, ou ça ne l'est pas.
        if (isMyTurn()){
            strcpy(inputPlayer,"0");
            actionMenu();
        }
        else if (isWaitingTurn()){
            waitingTurn();
        }
        else if ((!strcmp(msgServer,"winBySurrender")) || (!strcmp(msgServer,"Lose"))){
            gameOver = 1;
        }
    }
    if (!strcmp(msgServer,"winBySurrender") || (!strcmp(msgServer,"Win")) ){
        printWinning();
    }
    else{
        printLosing();
    }
    if ((!strcmp(msgServer,"Win")) || (!strcmp(msgServer,"Lose"))){
        infoEndGame();
        infoKill();
    }
    else {
        infoEndGame();
        infoSurrender();
    }
}

//---------- GUI

string Client::getMsgServer(){
    return msgServer;
}

void Client::resetMsgSendChat(){
    strcpy(msgSendChat,"nothing");
}

char* Client::getMsgSendChat(){
    return msgSendChat;
}

char* Client::getMsgRecvChat(){
    return msgRcvChat;
}


int Client::getSockfd(){
    return sockfd;
}

int Client::getSendChatfd(){
    return sendChat_fd;
}

int Client::getRecvChatfd(){
    return rcvChat_fd;
}

void Client::setUsername(string usernm){
    username = usernm;
}

string Client::getUsername(){
    return username;
}

void Client::setPassword(string pwd){
    password = pwd;
}

string Client::parseOneDeck(int indice){
    string deck = "";
    for(int i=0;i<myDecks[indice].getSize();++i){
        if (i+1 == myDecks[indice].getSize()){
            deck += to_string(myDecks[indice].getCard(i));
        }
        else{
            deck += to_string(myDecks[indice].getCard(i)) + ",";
        }
    }
    return deck;
}

void Client::setActiveDeck(string myDeck){
    activeDeck = myDeck;
}

string Client::getActiveDeck(){
    return activeDeck;
}

Collection Client::getCollection(){
    return myCollection;
}

Deck Client::getDeck(int indice){
    return myDecks[indice];
}

void Client::setLaunchDuel(int ld){
    launchDuel = ld;
}

int Client::getLaunchDuel(){
    return launchDuel;
}

void Client::receiveFromGameSocket(){
    if ((numbytes=recv(gameSocket,waitMsg,MAXDATASIZE-1,0)) == -1){
        perror("recv");
        exit(1);
    }
    waitMsg[numbytes] = '\0';
}

string Client::getWaitMsg(){
    return waitMsg;
}

void Client::setHandSize(int size){
    handSize = size;
}

int Client::getHandSize(){
    return handSize;
}

void Client::setCanAtk(int nbr){
    canAtk = nbr;
}

int Client::getCanAtk(){
    return canAtk;
}

void Client::setTargetSize(int size){
    targetSize = size;
}

int Client::getTargetSize(){
    return targetSize;
}

Deck Client::getBufferDeck(int indice){
    return myBufferDecks[indice];
}

void Client::setBufferDeck(Deck newDeck,int indice){
    myBufferDecks[indice] = newDeck;
}

void Client::setMsg(string msg){
    strcpy(msgServer,msg.c_str());

}
