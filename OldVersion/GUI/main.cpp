#include "gui.h"
#include "collectiongui.h"
#include "client.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char localIP[20] = "127.1";
    Gui w(new Client(2,localIP));
    QFile stylesheet(":/style/style/style.css");
    stylesheet.open(QFile::ReadOnly);
    QString style(stylesheet.readAll());
    w.setStyleSheet(style);
    w.show();

    return a.exec();
}
