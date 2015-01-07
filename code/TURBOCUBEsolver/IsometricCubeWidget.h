#ifndef ISOMETRICCUBEWIDGET_H
#define ISOMETRICCUBEWIDGET_H

#include "CubeColor.h"
#include "Cube.h"
#include <QWidget>

using namespace CubeColor;

class IsometricCubeWidget : public QWidget
{
    Q_OBJECT

public:
    IsometricCubeWidget(Cube c, QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void setCube(Cube c);

private:
    QPoint isogrid[7][7];
    int displayCube[18][3];

    QColor getQColorFromValue(int color, int alpha = 255);
    void initIsoGrid();
};

#endif // ISOMETRICCUBEWIDGET_H
