#include "mainwindow.h"
#include <QApplication>
#include "videoplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QFont font;
     //font.setPointSize(16);
    font.setFamily(("Noto Sans S Chinese"));
    a.setFont(font);

    return a.exec();
}
