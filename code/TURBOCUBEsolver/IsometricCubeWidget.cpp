/**
This class is used to represent the cube in a isometric view

@author: Thomas Roulin
**/

#include "IsometricCubeWidget.h"
#include <QPainter>
#include <QtWidgets>
#include <qdebug.h>

#define W 100
#define H 60

/**********************************************************\
|****************    Internal class    ********************|
\**********************************************************/
class Face{
public:
    // Construct
    Face(color colSrc, int orientationSrc){
        col = new color;
        orientation = new int;
        *col = colSrc;
        *orientation = orientationSrc;
    }
    Face(const Face &src)
    {
        col = new color;
        *col = *src.col;
        orientation = new int;
        *orientation = *src.orientation;
    }
    ~Face()
    {
        delete col;
        delete orientation;
        col = NULL;
        orientation = NULL;
    }

    // Getter / Setter
    void setO(int value)
    {
        *orientation += value;
        *orientation %= 4;
    }
    int getO()
    {
        return *orientation;
    }
    color getC()
    {
        return *col;
    }

private:
    // Attribs
    color *col;
    int *orientation;
};
/**********************************************************\
|****************      Constructor     ********************|
\**********************************************************/
IsometricCubeWidget::IsometricCubeWidget(Cube c, QWidget *parent)
    : QWidget(parent)
{
    config = false;

    // Widget size
    this->resize(1000,550);
    this->setStyleSheet("background-color: rgb(220,220,220);");

    // init isometric grid, used to create polygons
    initIsoGrid();

    // Set Faces colors and orientations
    faceU = new Face(WHITE, 0);
    faceF = new Face(RED, 0);
    faceB = new Face(ORANGE, 0);
    faceD = new Face(YELLOW, 0);
    faceR = new Face(BLUE, 0);
    faceL = new Face(GREEN, 0);

    // Use the right cube
    this->setCube(c);
}

void IsometricCubeWidget::setOrientation(QChar axe, int nbQ)
{
    Face *faceSave;
    switch(axe.toLatin1()){
    case 'x':
        if(nbQ == 1){
            // Switch faces
            faceSave = new Face(*faceU);
            faceU = faceF;
            faceF = faceD;
            faceD = faceB;
            faceB = faceSave;
            // Turn parallels faces
            faceR->setO(1);
            faceL->setO(3);
            // Cuz of the drawing logic
            faceB->setO(2);
            faceF->setO(2);
        } else {
            // Switch faces
            faceSave = new Face(*faceU);
            faceU = faceB;
            faceB = faceD;
            faceD = faceF;
            faceF = faceSave;
            // Turn parallels faces
            faceR->setO(3);
            faceL->setO(1);
            // Cuz of the drawing logic
            faceU->setO(2);
            faceD->setO(2);
        }
        break;
    case 'y':
        if(nbQ == 1){
            // Switch faces
            faceSave = new Face(*faceF);
            faceF = faceR;
            faceR = faceB;
            faceB = faceL;
            faceL = faceSave;
            // Turn parallels faces
            faceU->setO(1);
            faceD->setO(3);
        } else {
            // Switch faces
            faceSave = new Face(*faceF);
            faceF = faceL;
            faceL = faceB;
            faceB = faceR;
            faceR = faceSave;
            // Turn parallels faces
            faceU->setO(3);
            faceD->setO(1);
        }
        break;
    case 'z':
        if(nbQ == 1){
            // Switch faces
            faceSave = new Face(*faceU);
            faceU = faceL;
            faceL = faceD;
            faceD = faceR;
            faceR = faceSave;
            // Turn parallels faces
            faceF->setO(1);
            faceB->setO(3);
            // Cuz of the drawing logic
            faceR->setO(1);
            faceD->setO(3);
            faceL->setO(3);
            faceU->setO(1);
        } else {
            // Switch faces
            faceSave = new Face(*faceU);
            faceU = faceR;
            faceR = faceD;
            faceD = faceL;
            faceL = faceSave;
            // Turn parallels faces
            faceF->setO(3);
            faceB->setO(1);
            // Cuz of the drawing logic
            faceR->setO(1);
            faceD->setO(1);
            faceL->setO(3);
            faceU->setO(3);
        }
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

    for (int y = 0; y < 3 ; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            // Creating the polygon's vector
            plgnUp[x][y].append(isogrid[6-y][x]);
            plgnUp[x][y].append(isogrid[6-y][x+1]);
            plgnUp[x][y].append(isogrid[5-y][x+1]);
            plgnUp[x][y].append(isogrid[5-y][x]);

            plgnFront[x][y].append(isogrid[3-y][x+y]);
            plgnFront[x][y].append(isogrid[3-y][x+y+1]);
            plgnFront[x][y].append(isogrid[2-y][x+y+2]);
            plgnFront[x][y].append(isogrid[2-y][x+y+1]);

            plgnRight[x][y].append(isogrid[3+x-y][3+y]);
            plgnRight[x][y].append(isogrid[4+x-y][3+y]);
            plgnRight[x][y].append(isogrid[3+x-y][4+y]);
            plgnRight[x][y].append(isogrid[2+x-y][4+y]);

            plgnDown[x][y].append(isogrid[x][y+4]);
            plgnDown[x][y].append(isogrid[x+1][y+4]);
            plgnDown[x][y].append(isogrid[x+1][y+3]);
            plgnDown[x][y].append(isogrid[x][y+3]);
            plgnDown[x][y].translate(4*W,0);

            plgnBack[x][y] = QPolygon(plgnRight[x][y]);
            plgnBack[x][y].translate(2.5*W,-1.5*H);

            plgnLeft[x][y] = QPolygon(plgnFront[x][y]);
            plgnLeft[x][y].translate(5.5*W,-1.5*H);
        }
    }

}

void IsometricCubeWidget::mousePressEvent(QMouseEvent *e){
    if (config) {
        QChar face = 'r';
        int matX;
        int matY;
        //Checking each isometric polygon and saving x, y and the face if we find the correct polygon
        int x = 0;
        int y = 0;
        while(x < 3 && face == 'r')
        {
            if(plgnBack[x][y].containsPoint(e->pos(), Qt::OddEvenFill)){
                face = 'B';
                matX = x;
                matY = y;
            }
            if(plgnUp[x][y].containsPoint(e->pos(), Qt::OddEvenFill)){
                face = 'U';
                matX = x;
                matY = y;
            }
            if(plgnFront[x][y].containsPoint(e->pos(), Qt::OddEvenFill)){
                face = 'F';
                matX = x;
                matY = y;
            }
            if(plgnLeft[x][y].containsPoint(e->pos(), Qt::OddEvenFill)){
                face = 'L';
                matX = x;
                matY = y;
            }
            if(plgnDown[x][y].containsPoint(e->pos(), Qt::OddEvenFill)){
                face = 'D';
                matX = x;
                matY = y;
            }
            if(plgnRight[x][y].containsPoint(e->pos(), Qt::OddEvenFill)){
                face = 'R';
                matX = x;
                matY = y;
            }
            if (++y == 3){
                x++;
                y %= 3;
            }
        }

        //if event->pos() is into a polygon
        if(face != 'r'){
            //Getting the indices on the cube matrix
            int mx, my;
            // Get the right x and y dependig on the orientation
            getMXMY(matX, matY, mx, my, face);

            // Check if not center
            if(!(mx % 3 == 1 && my == 1)){
                color mc = UNDEFINED;
                if(e->button() == Qt::LeftButton){
                     mc = (color)((displayCube[mx][my] + 1) % 6);
                } else {
                    mc = (color)((displayCube[mx][my] + 5) % 6);
                }
                emit cubieModified(mx, my, mc);
                this->update();
            }
        }
    }
}

void IsometricCubeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBackground(Qt::blue);

    // START TITLES
    painter.setPen(Qt::black);


    int id = QFontDatabase::addApplicationFont(":/Fonts/reservoirdogs.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont rdFont(family);
    rdFont.setPointSize(30);
    painter.setFont(rdFont);

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


    for (int y = 0; y < 3 ; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            // DRAWING

            QPen pen(Qt::black, 3);
            painter.setPen(pen);

            // FRONT FACE
            painter.setBrush(getDaCola('F', x, y));
            painter.drawPolygon(plgnFront[x][y]);

            // RIGHT FACE
            painter.setBrush(getDaCola('R', x, y));
            painter.drawPolygon(plgnRight[x][y]);

            // BACK FACE
            painter.setBrush(getDaCola('B', x, y));
            painter.drawPolygon(plgnBack[x][y]);

            // LEFT FACE
            painter.setBrush(getDaCola('L', x, y));
            painter.drawPolygon(plgnLeft[x][y]);

            // UP FACE
            painter.setBrush(getDaCola('U', x, y));
            painter.drawPolygon(plgnUp[x][y]);

            // DOWN FACE
            painter.setBrush(getDaCola('D', x, y));
            painter.drawPolygon(plgnDown[x][y]);


        }
    }


}

QColor IsometricCubeWidget::getDaCola(QChar face, int x, int y)
{
    return getQColorFromValue(getValueFromFace(face, x , y));
}

void IsometricCubeWidget::getMXMY(int x, int y, int &mx, int &my, QChar face)
{
    Face *actFace;
    switch(face.toLatin1())
    {
    case 'U':
        actFace = faceU;
        break;
    case 'D':
        actFace = faceD;
        break;
    case 'L':
        actFace = faceL;
        break;
    case 'R':
        actFace = faceR;
        break;
    case 'F':
        actFace = faceF;
        break;
    case 'B':
        actFace = faceB;
        break;
    }

    switch(actFace->getO())
    {
    case 0:
        mx = x;
        my = y;
        break;
    case 1:
        mx = y;
        my = 2-x;
        break;
    case 2:
        mx = 2-x;
        my = 2-y;
        break;
    case 3:
        mx = 2-y;
        my = x;
        break;
    }

    mx = mx+actFace->getC()*3;
}
bool IsometricCubeWidget::getConfig() const
{
    return config;
}

void IsometricCubeWidget::setConfig(bool value)
{
    config = value;
}


int IsometricCubeWidget::getValueFromFace(QChar face, int x, int y)
{
    int value;

    int mx, my;

    // cuz value will change with the orientation
    getMXMY(x, y, mx, my, face);


    value = displayCube[mx][my];


    return value;

}

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
    return faceF->getC();
}

color IsometricCubeWidget::getUp(){
    return faceU->getC();
}
