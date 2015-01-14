#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QPushButton>
#include "CubeColor.h"


using namespace CubeColor;
class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = 0);
    ~ColorPicker();

    //color buttons
    QPushButton **colorPB;

    //matrix preset
    void setMatrix(color cubeMatrix[18][3]);

    //matrix attribute
    color cubeInputMatrix[18][3];

    //focus change event
    void focusOutEvent(QFocusEvent *);
public slots:
    void colorSelection();
signals:
    void colorSendSignal(color c);


public slots:

};

#endif // COLORPICKER_H
