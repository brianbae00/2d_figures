#include "portfolio.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    portfolio w;
    w.resize(1200, 900);
    w.show();
    return a.exec();
}
