#include "inputwidget.h"
#include <QPainter>
#include <QtWidgets>
#include <QDebug>

#define W 40

InputWidget::InputWidget(QWidget *parent) :
    QWidget(parent)
{
    //set window size
    this->setFixedSize(14 * W, 11 * W);

    for (int x = 0; x < 18; x++) {
        for (int y = 0; y < 3; y++) {
            if (x % 3 == 1 && y == 1){
                displayCube[x][y] = (color) (x / 3);
            } else {
                displayCube[x][y] = UNDEFINED;
            }
        }
    }
    offsetX[RED] = 1;
    offsetY[RED] = 1;
    offsetX[BLUE] = 2;
    offsetY[BLUE] = 1;
    offsetX[ORANGE] = 3;
    offsetY[ORANGE] = 1;
    offsetX[GREEN] = 0;
    offsetY[GREEN] = 1;
    offsetX[WHITE] = 1;
    offsetY[WHITE] = 0;
    offsetX[YELLOW] = 3;
    offsetY[YELLOW] = 2;

    cube = new Cube(displayCube);
}

void InputWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    int face = UNDEFINED;
    int x = -1;
    int y = -1;

    //mouse pressed on RED, BLUE, ORANGE or GREEN face
    if(pos.y() > 4 * W && pos.y() < 7 * W && pos.x() > W && pos.x() < W * 13){
        face = ((pos.x() / W - 1) / 3 + 3) % 4;
        x = (pos.x() / W - 1) % 3;
        y = (pos.y() / W - 4) % 3;
    }
    //mouse pressed WHITE face
    if(pos.y() > 1 * W && pos.y() < 4 * W && pos.x() > 4 * W && pos.x() < W * 7){
        face = WHITE;
        x = (pos.x() / W - 4) % 3;
        y = (pos.y() / W - 1) % 3;
    }
    //mouse pressed YELLOW face
    if(pos.y() > 7 * W && pos.y() < 10 * W && pos.x() > 10 * W && pos.x() < W * 13){
        face = YELLOW;
        x = (pos.x() / W - 10) % 3;
        y = (pos.y() / W - 7) % 3;
    }

    if(face != -1 && !(x == 1 && y == 1)){
        qDebug() << face << x << y;
        displayCube[x + face * 3][y] = (color)((displayCube[x + face * 3][y] + 1) % 6);
        this->update();
    }
}

void InputWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBackground(Qt::blue);


    for (int face = 0; face < 6; ++face) {
        for (int y = 0; y < 3 ; y++) {
            for (int x = 0; x < 3; x++) {
                // Creating the polygon
                QPolygon plgn;

                // Creating the polygon's vectors
                QPoint p1(W + x * W + 3 * W * offsetX[face], W + y * W + 3 * W * offsetY[face]);
                QPoint p2(W + (x + 1) * W + 3 * W * offsetX[face], W + y * W + 3 * W * offsetY[face]);
                QPoint p3(W + (x + 1) * W + 3 * W * offsetX[face], W + (y + 1) * W + 3 * W * offsetY[face]);
                QPoint p4(W + x * W + 3 * W * offsetX[face], W + (y + 1) * W + 3 * W * offsetY[face]);

                plgn.append(p1);
                plgn.append(p2);
                plgn.append(p3);
                plgn.append(p4);

                // Defining the sticker's color

                QColor drawColor;

                switch(displayCube[x + 3 * face][y]){
                case RED:
                    drawColor = QColor(204,0,0);
                    break;
                case BLUE:
                    drawColor = QColor(0,153,204);
                    break;
                case ORANGE:
                    drawColor = QColor(255,136,0);
                    break;
                case GREEN:
                    drawColor = QColor(102,153,0);
                    break;
                case WHITE:
                    drawColor = Qt::white;
                    break;
                case YELLOW:
                    drawColor = QColor(255,219,51);
                    break;
                case UNDEFINED:
                    drawColor = Qt::gray;
                    break;
                }

                // DRAWING

                QPen pen(Qt::black, 3);
                painter.setPen(pen);

                painter.setBrush(drawColor);
                painter.drawPolygon(plgn);
            }
        }
    }
}
