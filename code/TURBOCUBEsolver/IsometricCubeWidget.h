#ifndef ISOMETRICCUBEWIDGET_H
#define ISOMETRICCUBEWIDGET_H

#include "CubeColor.h"
#include <QWidget>

using namespace CubeColor;

class IsometricCubeWidget : public QWidget
{
    Q_OBJECT

public:
    IsometricCubeWidget(int cubeGrid[][3], QWidget *parent = 0);
    void paintEvent(QPaintEvent*);

private:
    QPoint isogrid[7][7];
    int testCube[18][3];

    QColor getQColorFromValue(int color, int alpha = 255);
    QPolygon* getPolygon(int first_x, int first_y, int type_polygon);
    void initIsoGrid();
    void initCubeGrid(int cubeGrid[][3]);

};

#endif // ISOMETRICCUBEWIDGET_H
