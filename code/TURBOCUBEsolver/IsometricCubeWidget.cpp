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
    colU = WHITE;
    colF = RED;
    colB = ORANGE;
    colD = YELLOW;
    colR = BLUE;
    colL = GREEN;

    // Use the right cube
    this->setCube(c);
}

void IsometricCubeWidget::setOrientation(QChar axe, int nbQ)
{
    switch(axe.toLatin1()){
    case 'x':
        if(nbQ == 1){
            color colSave = colU;
            colU = colF;
            colF = colD;
            colD = colB;
            colB = colSave;
        } else {
            color colSave = colU;
            colU = colB;
            colB = colD;
            colD = colF;
            colF = colSave;
        }
        break;
    case 'y':
        if(nbQ == 1){
            color colSave = colF;
            colF = colR;
            colR = colB;
            colB = colL;
            colL = colSave;
        } else {
            color colSave = colF;
            colF = colL;
            colL = colB;
            colB = colR;
            colR = colSave;
        }
        break;
    case 'z':
        if(nbQ == 1){
            color colSave = colU;
            colU = colL;
            colL = colD;
            colD = colR;
            colR = colSave;
        } else {
            color colSave = colU;
            colU = colR;
            colR = colD;
            colD = colL;
            colL = colSave;
        }
        break;
    default:
        break;
    }

    this->update();
}

void IsometricCubeWidget::setCube(Cube c)
{
    color** mat = c.getMatrix();

    for(int x = 0; x < 18; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            displayCube[x][y] = mat[x][y];
        }
        delete [] mat[x];
    }
    delete [] mat;
    mat = 0;

    this->update();
}

void IsometricCubeWidget::setCubeMatrix(int matrix[18][3])
{
    for(int x = 0; x < 18; x++)
    {
        for(int y = 0; y < 3; y++)
        {
            displayCube[x][y] = matrix[x][y];
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
            painter.setBrush(getDaCola('F', x, y));
            painter.drawPolygon(plgnFront);

            // RIGHT FACE
            painter.setBrush(getDaCola('R', x, y));
            painter.drawPolygon(plgnRight);

            // BACK FACE
            painter.setBrush(getDaCola('B', x, y));
            painter.drawPolygon(plgnBack);

            // LEFT FACE
            painter.setBrush(getDaCola('L', x, y));
            painter.drawPolygon(plgnLeft);

            // UP FACE
            painter.setBrush(getDaCola('U', x, y));
            painter.drawPolygon(plgnUp);

            // DOWN FACE
            painter.setBrush(getDaCola('D', x, y));
            painter.drawPolygon(plgnDown);



        }
    }

}

QColor IsometricCubeWidget::getDaCola(QChar face, int x, int y)
{
    return getQColorFromValue(getValueFromFace(face, x , y));
}

int IsometricCubeWidget::getValueFromFace(QChar face, int x, int y)
{
    int value;

    switch(face.toLatin1())
    {
        case 'U':
            value = displayCube[x+colU*3][y];
            break;
        case 'D':
            // y and x reversed, and y decrease instead of increasing
            // cuz the down and up face are drawn in opposed positions
            value = displayCube[y+colD*3][x];
            break;
        case 'L':
            value = displayCube[x+colL*3][y];
            break;
        case 'R':
            value = displayCube[x+colR*3][y];
            break;
        case 'F':
            value = displayCube[x+colF*3][y];
            break;
        case 'B':
            value = displayCube[x+colB*3][y];
            break;
    }

    return value;

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


color IsometricCubeWidget::getFront(){
    return colF;
}

color IsometricCubeWidget::getUp(){
    return colU;
}
