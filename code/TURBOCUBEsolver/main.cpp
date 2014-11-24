#include "turbocubesolver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TURBOCUBEsolver w;
    w.show();

    return a.exec();
}
