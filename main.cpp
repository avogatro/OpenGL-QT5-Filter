#include "filterdemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FilterDemo w;
    w.show();

    return a.exec();
}
