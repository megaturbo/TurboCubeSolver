#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <CubeColor.h>
#include <Cube.h>

using namespace CubeColor;

class InputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

signals:

public slots:

private:
    color displayCube[18][3];
    int offsetX[6];
    int offsetY[6];

    Cube *cube;
};

#endif // INPUTWIDGET_H
