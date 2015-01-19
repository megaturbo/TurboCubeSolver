#ifndef ISOMETRICCUBEWIDGET_H
#define ISOMETRICCUBEWIDGET_H

#include "CubeColor.h"
#include "Cube.h"
#include <QWidget>

using namespace CubeColor;

// Nested class Face
class Face;

class IsometricCubeWidget : public QWidget
{
    Q_OBJECT

public:
    IsometricCubeWidget(Cube c, QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent*);
    void setCube(Cube c);
    void setCubeMatrix(int matrix[18][3]);
    void setOrientation(QChar axe, int nbQ);

    color getFront();
    color getUp();

    void getMXMY(int x, int y, int &mx, int &my, QChar face);
    bool getConfig() const;
    void setConfig(bool value);

private:
    bool config;

    Face *faceU;
    Face *faceF;
    Face *faceB;
    Face *faceR;
    Face *faceL;
    Face *faceD;

    QPoint isogrid[7][7];
    QPolygon plgnUp[3][3];
    QPolygon plgnFront[3][3];
    QPolygon plgnRight[3][3];
    QPolygon plgnDown[3][3];
    QPolygon plgnBack[3][3];
    QPolygon plgnLeft[3][3];

    Cube *cube;
    int displayCube[18][3];
    QColor getDaCola(QChar face, int x, int y);
    int getValueFromFace(QChar face, int x, int y);
    QColor getQColorFromValue(int color, int alpha = 255);
    void initIsoGrid();

signals:
    void cubieModified(int x, int y, color c);
};

#endif // ISOMETRICCUBEWIDGET_H
