/**
This class is used to represent the cube in a isometric view


**/
#include "IsometricCubeWidget.h"
#include <QPainter>
#include <QtWidgets>
#include <qdebug.h>

#define W 100
#define H 60

#define POLYGON_UP 0
#define POLYGON_FRONT 1
#define POLYGON_RIGHT 2

IsometricCubeWidget::IsometricCubeWidget(int cubeGrid[][3], QWidget *parent)
    : QWidget(parent)
{
    this->resize(1000,1000);
    initCubeGrid(cubeGrid);
    initIsoGrid();
    this->update();
}

void IsometricCubeWidget::initCubeGrid(int cubeGrid[][3])
{
    for(int x = 0; x < 18; x++)
    {
        for(int y = 0;y < 3; y++)
        {
        testCube[x][y] = cubeGrid[x][y];
        }
    }
}

void IsometricCubeWidget::initIsoGrid()
{
    int sX, sY;


    for (int y = 0; y < 7 ; y++)
    {
        for (int x = 0; x < 7; x++)
        {
                sX = (x * W / 2) + (y * W / 2);
                sY = (y * H / 2) - (x * H / 2);

                isogrid[x][y] = QPoint(sX+2*W,sY+H*7);
        }
    }

}

void IsometricCubeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // START SHADOW
    painter.setPen(Qt::transparent);
    painter.setBrush(Qt::lightGray);

    QVector<QPoint> shadow;
    shadow.append(isogrid[3][6]);
    shadow.append(isogrid[5][6]);
    shadow.append(isogrid[5][3]);
    shadow.append(isogrid[3][3]);
    painter.drawPolygon(shadow);
    // END SHADOW


    QPolygon plgnUp;
    QPolygon plgnFront;
    QPolygon plgnRight;
    QPolygon plgnDown;
    QPolygon plgnBack;
    QPolygon plgnLeft;


    for (int y = 0; y < 3 ; y++)
    {
        for (int x = 0; x < 3; x++)
        {
                // Clearing the polygon's vector
                plgnUp.clear();
                plgnFront.clear();
                plgnRight.clear();

                // Creating the polygon's vector
                plgnUp.append(isogrid[6-x][y]);
                plgnUp.append(isogrid[6-x][y+1]);
                plgnUp.append(isogrid[5-x][y+1]);
                plgnUp.append(isogrid[5-x][y]);

                plgnFront.append(isogrid[3-x][y+x]);
                plgnFront.append(isogrid[3-x][y+x+1]);
                plgnFront.append(isogrid[2-x][y+x+2]);
                plgnFront.append(isogrid[2-x][y+x+1]);

                plgnRight.append(isogrid[3+x-y][3+y]);
                plgnRight.append(isogrid[4+x-y][3+y]);
                plgnRight.append(isogrid[3+x-y][4+y]);
                plgnRight.append(isogrid[2+x-y][4+y]);

                // CREATE AND TRANSLATE THE HIDDEN FACES
                plgnDown = QPolygon(plgnUp);
                plgnDown.translate(0,8*H);

                plgnBack = QPolygon(plgnFront);
                plgnBack.translate(4*W,-4*H);

                plgnLeft = QPolygon(plgnRight);
                plgnLeft.translate(-4*W,-4*H);

                // DRAWING

                painter.setPen(Qt::darkGray);

                // FRONT FACE
                painter.setBrush(getQColorFromValue(testCube[x][y]));
                painter.drawPolygon(plgnFront);

                // RIGHT FACE
                painter.setBrush(getQColorFromValue(testCube[y+3][x]));
                painter.drawPolygon(plgnRight);

                // BACK FACE
                painter.setBrush(getQColorFromValue(testCube[x+6][y]));
                painter.drawPolygon(plgnBack);

                // LEFT FACE
                painter.setBrush(getQColorFromValue(testCube[y+9][x]));
                painter.drawPolygon(plgnLeft);

                // UP FACE
                painter.setBrush(getQColorFromValue(testCube[x+12][y]));
                painter.drawPolygon(plgnUp);

                // DOWN FACE
                painter.setBrush(getQColorFromValue(testCube[x+15][y]));
                painter.drawPolygon(plgnDown);



                // DRAWING INFORMATION POINTS
                /*painter.setPen(Qt::black);
                painter.drawText(plgnFront.at(0),QString::number(x)+","+QString::number(y));
                painter.drawText(plgnRight.at(0),QString::number(x)+","+QString::number(y));
                painter.drawText(plgnUp.at(0),QString::number(x)+","+QString::number(y));
                painter.setPen(Qt::darkGray);*/



                //painter.setPen(textPen);
                //painter.drawText(sX+W, sY+H*5, "("+QString::number(x)+","+QString::number(y)+")");
        }
    }

}

QPolygon* IsometricCubeWidget::getPolygon(int first_x, int first_y, int type_polygon)
{
    QPolygon *returnPolygon = new QPolygon();

    returnPolygon->append(QPoint(first_x, first_y));

    switch (type_polygon)
    {
        case POLYGON_UP:
            returnPolygon->append(QPoint(first_x+1,first_y));
            returnPolygon->append(QPoint(first_x+1,first_y+1));
            returnPolygon->append(QPoint(first_x,first_y+1));
            break;
        case POLYGON_FRONT:
            returnPolygon->append(QPoint(first_x,first_y+1));
            returnPolygon->append(QPoint(first_x-1,first_y+2));
            returnPolygon->append(QPoint(first_x-1,first_y+1));
            break;
        case POLYGON_RIGHT:
            returnPolygon->append(QPoint(first_x+1,first_y));
            returnPolygon->append(QPoint(first_x,first_y+1));
            returnPolygon->append(QPoint(first_x-1,first_y+1));
        break;
    }

    return returnPolygon;
}

// RED = 0, BLUE = 1, ORANGE = 2, GREEN = 3, WHITE = 4, YELLOW = 5

QBrush IsometricCubeWidget::getQColorFromValue(int color)
{
    QBrush returnColor;

    switch(color){
        case RED:
            returnColor = QColor(204,0,0);
        break;
        case BLUE:
            returnColor = QColor(0,153,204);
        break;
        case ORANGE:
            returnColor = QColor(255,136,0);
        break;
        case GREEN:
            returnColor = QColor(102,153,0);
        break;
        case WHITE:
            returnColor = Qt::white;
        break;
        case YELLOW:
            returnColor = QColor(255,219,51);
        break;
        case UNDEFINED:
            returnColor = Qt::VerPattern;
        break;
    }

    return returnColor;
}
