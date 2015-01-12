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
    int* indicesX;
    int* indicesY;
    switch(axe.toLatin1()){
    case 'x':
        if(nbQ == 1){
            Cube easyToSpin(displayCube);
            easyToSpin.moveSequence("R' L ", RED, WHITE);
            color** mat = easyToSpin.getMatrix();
            for (int x = 0; x < 18; ++x) {
                for (int y = 0; y < 3; ++y) {
                    displayCube[x][y] = mat[x][y];
                }
                delete [] mat[x];
            }
            delete [] mat;
            color colSave = colU;
            colU = colF;
            colF = colD;
            colD = colB;
            colB = colSave;
            indicesX = new int[12]{1, 1, 1, 13, 13, 13, 7, 7, 7, 16, 16, 16};
            indicesY = new int[12]{0, 1, 2, 0, 1, 2, 0, 1, 2, 2, 1, 0};
        } else {
            Cube easyToSpin(displayCube);
            easyToSpin.moveSequence("R L' ", RED, WHITE);
            color** mat = easyToSpin.getMatrix();
            for (int x = 0; x < 18; ++x) {
                for (int y = 0; y < 3; ++y) {
                    displayCube[x][y] = mat[x][y];
                }
                delete [] mat[x];
            }
            delete [] mat;
            color colSave = colU;
            colU = colB;
            colB = colD;
            colD = colF;
            colF = colSave;
            indicesX = new int[12]{1, 1, 1, 16, 16, 16, 7, 7, 7, 13, 13, 13};
            indicesY = new int[12]{0, 1, 2, 2, 1, 0, 0, 1, 2, 0, 1, 2};
        }
        break;
    case 'y':
        if(nbQ == 1){
            Cube easyToSpin(displayCube);
            easyToSpin.moveSequence("U D' ", RED, WHITE);
            color** mat = easyToSpin.getMatrix();
            for (int x = 0; x < 18; ++x) {
                for (int y = 0; y < 3; ++y) {
                    displayCube[x][y] = mat[x][y];
                }
                delete [] mat[x];
            }
            delete [] mat;
            color colSave = colU;
            colU = colB;
            colB = colD;
            colD = colF;
            colF = colSave;
            indicesX = new int[12]{0, 1, 2, 9, 10, 11, 6, 7, 8, 3, 4, 5};
            indicesY = new int[12]{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        } else {
            Cube easyToSpin(displayCube);
            easyToSpin.moveSequence("U' D ", RED, WHITE);
            color** mat = easyToSpin.getMatrix();
            for (int x = 0; x < 18; ++x) {
                for (int y = 0; y < 3; ++y) {
                    displayCube[x][y] = mat[x][y];
                }
                delete [] mat[x];
            }
            delete [] mat;
            color colSave = colF;
            colF = colR;
            colR = colB;
            colB = colL;
            colL = colSave;
            indicesX = new int[12]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
            indicesY = new int[12]{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        }
        break;
    case 'z':
        if(nbQ == 1){
            Cube easyToSpin(displayCube);
            easyToSpin.moveSequence("B' F ", RED, WHITE);
            color** mat = easyToSpin.getMatrix();
            for (int x = 0; x < 18; ++x) {
                for (int y = 0; y < 3; ++y) {
                    displayCube[x][y] = mat[x][y];
                }
                delete [] mat[x];
            }
            delete [] mat;
            color colSave = colU;
            colU = colF;
            colF = colD;
            colD = colB;
            colB = colSave;
            indicesX = new int[12]{4, 4, 4, 15, 16, 17, 10, 10, 10, 12, 13, 14};
            indicesY = new int[12]{0, 1, 2, 1, 1, 1, 2, 1, 0, 1, 1, 1};
        } else {
            Cube easyToSpin(displayCube);
            easyToSpin.moveSequence("B F' ", RED, WHITE);
            color** mat = easyToSpin.getMatrix();
            for (int x = 0; x < 18; ++x) {
                for (int y = 0; y < 3; ++y) {
                    displayCube[x][y] = mat[x][y];
                }
                delete [] mat[x];
            }
            delete [] mat;
            color colSave = colU;
            colU = colB;
            colB = colD;
            colD = colF;
            colF = colSave;
            indicesX = new int[12]{4, 4, 4, 12, 13, 14, 10, 10, 10, 15, 16, 17};
            indicesY = new int[12]{0, 1, 2, 1, 1, 1, 2, 1, 0, 1, 1, 1};
        }
        break;
    default:
        break;
    }
    int saveAdjacent[3];
    for (int i = 0; i < 3; ++i) {
        saveAdjacent[i] = displayCube[indicesX[i + 9]][indicesY[i + 9]];
    }
    for (int i = 11; i > 3; i-=3) {
        displayCube[indicesX[i]][indicesY[i]] = displayCube[indicesX[i - 3]][indicesY[i - 3]];
        displayCube[indicesX[i - 1]][indicesY[i - 1]] = displayCube[indicesX[i - 4]][indicesY[i - 4]];
        displayCube[indicesX[i - 2]][indicesY[i - 2]] = displayCube[indicesX[i - 5]][indicesY[i - 5]];
    }
    displayCube[indicesX[0]][indicesY[0]] = saveAdjacent[0];
    displayCube[indicesX[1]][indicesY[1]] = saveAdjacent[1];
    displayCube[indicesX[2]][indicesY[2]] = saveAdjacent[2];
    delete [] indicesX;
    delete [] indicesY;
    indicesX = 0;
    indicesY = 0;
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


color IsometricCubeWidget::getFront(){
    return colF;
}

color IsometricCubeWidget::getUp(){
    return colU;
}
