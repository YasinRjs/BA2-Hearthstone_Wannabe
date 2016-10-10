#include "gui.h"
#include "collectiongui.h"
#include "client.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc > 1){
	    QApplication a(argc, argv);
	    char* localIP = argv[1];
	    Gui w(new Client(2,localIP));
	    w.show();
		return a.exec();
	}
	else{
		cout << "Il manque l'adresse ip." << endl;
	}

    return 1;
}
