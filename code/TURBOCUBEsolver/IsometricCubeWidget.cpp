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
                plgnDown.translate(3*W,3*H);

                plgnBack = QPolygon(plgnRight);
                plgnBack.translate(1.5*W,-1.5*H);

                plgnLeft = QPolygon(plgnFront);
                plgnLeft.translate(4.5*W,-1.5*H);

                // DRAWING

                painter.setPen(Qt::black);

                // ### ALPHA 255

                // FRONT FACE
                painter.setBrush(getQColorFromValue(testCube[x][y]));
                painter.drawPolygon(plgnFront);

                // RIGHT FACE
                painter.setBrush(getQColorFromValue(testCube[y+3][x]));
                painter.drawPolygon(plgnRight);

                // BACK FACE
                painter.setBrush(getQColorFromValue(testCube[y+6][x]));
                painter.drawPolygon(plgnBack);

                // LEFT FACE
                painter.setBrush(getQColorFromValue(testCube[x+9][y]));
                painter.drawPolygon(plgnLeft);

                // UP FACE
                painter.setBrush(getQColorFromValue(testCube[x+12][y]));
                painter.drawPolygon(plgnUp);

                // DOWN FACE
                painter.setBrush(getQColorFromValue(testCube[15+y][2-x]));
                painter.drawPolygon(plgnDown);


                // ### ALPHA 100

                /*QColor c;

                // front
                c = QColor(getQColorFromValue(testCube[x+12][y]), 100);

                plgnUp.translate(4*W,-4*H);
                painter.setBrush(c);
                painter.drawPolygon(plgnUp);


                plgnUp.translate(-8*W, 0);*/



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

QColor IsometricCubeWidget::getQColorFromValue(int color, int alpha)
{
    QColor returnColor;

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
            returnColor = Qt::gray;
        break;
    }

    returnColor.setAlpha(alpha);

    return returnColor;
}
