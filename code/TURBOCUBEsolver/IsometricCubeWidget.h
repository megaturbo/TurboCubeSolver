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
    void setCubeMatrix(int matrix[18][3]);
    void setOrientation(QChar axe, int nbQ);

    color getFront();
    color getUp();

private:
    color colU;
    color colF;
    color colB;
    color colR;
    color colL;
    color colD;

    Cube *cube;
    QPoint isogrid[7][7];
    int displayCube[18][3];

    QColor getQColorFromValue(int color, int alpha = 255);
    void initIsoGrid();
};

#endif // ISOMETRICCUBEWIDGET_H
