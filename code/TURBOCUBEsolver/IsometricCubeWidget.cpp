/**
This class is used to represent the cube in a isometric view


**/
#include "IsometricCubeWidget.h"
#include <QPainter>
#include <QtWidgets>
#include <qdebug.h>

#define W 100
#define H 60

IsometricCubeWidget::IsometricCubeWidget(Cube c, QWidget *parent)
    : QWidget(parent)
{
    // Widget size
    this->resize(1000,550);
    this->setStyleSheet("background-color: rgb(220,220,220);");

    // init isometric grid, used to create polygons
    initIsoGrid();

    // Set orientation
    colU = YELLOW;
    colF = RED;

    // Use the right cube
    this->setCube(c);
}


void IsometricCubeWidget::setOrientation(QChar axe, int nbQ)
{
    int tmpMatrix[18][3];

    if(axe == 'y')
    {

        for(int x = 0; x < 12; x++)
        {
            for(int y = 0; y < 3; y++)
            {
                tmpMatrix[x][x] = displayCube[(x+3)%12][y];
            }
        }
    }
}

void IsometricCubeWidget::setCube(Cube c)
{
    for(int x = 0; x < 18; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            displayCube[x][y] = c.getMatrix()[x][y];
        }
    }

    this->update();
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

                isogrid[x][y] = QPoint(sX,sY+H*5);
        }
    }

}

void IsometricCubeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBackground(Qt::blue);

    // START TITLES
    painter.setPen(Qt::black);

    //int rdFontID = QFontDatabase::addApplicationFont(":/Fonts/reservoirdogs.ttf");
    //QString fontFamily = QFontDatabase::applicationFontFamilies(rdFontID).at(0);
    //QFont font(fontFamily);

    QFont font("Arial", 30);
    //font.setPointSize(30);

    painter.setFont(QFont(font));

    painter.drawText(isogrid[3][0].rx() + 0.3 * W, 100, "FRONT");
    painter.drawText(isogrid[4][0].rx() + 4 * W, 100, "BACK");

    // END TITLES

    // START SHADOW
    painter.setPen(Qt::transparent);
    painter.setBrush(Qt::lightGray);

    QPolygon shadow;
    shadow.append(isogrid[3][6]);
    shadow.append(isogrid[5][6]);
    shadow.append(isogrid[5][3]);
    shadow.append(isogrid[3][3]);
    painter.drawPolygon(shadow);

    shadow.translate(4 * W, 0);
    //painter.drawPolygon(shadow);

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
                plgnUp.append(isogrid[6-y][x]);
                plgnUp.append(isogrid[6-y][x+1]);
                plgnUp.append(isogrid[5-y][x+1]);
                plgnUp.append(isogrid[5-y][x]);

                plgnFront.append(isogrid[3-y][x+y]);
                plgnFront.append(isogrid[3-y][x+y+1]);
                plgnFront.append(isogrid[2-y][x+y+2]);
                plgnFront.append(isogrid[2-y][x+y+1]);

                plgnRight.append(isogrid[3+x-y][3+y]);
                plgnRight.append(isogrid[4+x-y][3+y]);
                plgnRight.append(isogrid[3+x-y][4+y]);
                plgnRight.append(isogrid[2+x-y][4+y]);

                // CREATE AND TRANSLATE THE HIDDEN FACES
                plgnDown = QPolygon(plgnUp);
                plgnDown.translate(4*W,3*H);

                plgnBack = QPolygon(plgnRight);
                plgnBack.translate(2.5*W,-1.5*H);

                plgnLeft = QPolygon(plgnFront);
                plgnLeft.translate(5.5*W,-1.5*H);

                // DRAWING

                QPen pen(Qt::black, 3);
                painter.setPen(pen);

                // ### ALPHA 255

                // FRONT FACE
                painter.setBrush(getQColorFromValue(displayCube[x][y]));
                painter.drawPolygon(plgnFront);

                // RIGHT FACE
                painter.setBrush(getQColorFromValue(displayCube[x+3][y]));
                painter.drawPolygon(plgnRight);

                // BACK FACE
                painter.setBrush(getQColorFromValue(displayCube[x+6][y]));
                painter.drawPolygon(plgnBack);

                // LEFT FACE
                painter.setBrush(getQColorFromValue(displayCube[x+9][y]));
                painter.drawPolygon(plgnLeft);

                // UP FACE
                painter.setBrush(getQColorFromValue(displayCube[x+12][y]));
                painter.drawPolygon(plgnUp);

                // DOWN FACE
                // y and x reversed, and y decrease instead of increasing
                // cuz the down and up face are drawn in opposed positions
                painter.setBrush(getQColorFromValue(displayCube[17-y][x]));
                painter.drawPolygon(plgnDown);



        }
    }

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
