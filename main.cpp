#include "widget.h"

#include <QApplication>
#include <QLibrary>
#include <QDebug>
int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR","2");
    QApplication a(argc, argv);
    widget w;
    w.show();

    return a.exec();
}
