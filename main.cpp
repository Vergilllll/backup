#include "widget.h"
#include "backup.h"
#include "filefilter.h"
#include <QApplication>
#include <QDebug>
#include <QLibrary>
#include <QObject>
int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR", "2");
    QApplication a(argc, argv);
    widget w;
    w.show();
    return a.exec();
}
