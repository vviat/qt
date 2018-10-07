#include "QImageProcess.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QImageProcess w;
    w.show();
    return a.exec();
}
