#include "colorpicker.h"
#include <QApplication>

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setFixedSize(50,110);
    this->setGeometry(QCursor::pos().rx(),QCursor::pos().ry(),50,110);
    this->setFocus();



    colorPB = new QPushButton*[6]();

    for(int i = 0;i<6;i++)
    {
        colorPB[i]=new QPushButton(this);
        colorPB[i]->setGeometry(1,1+i*18,48,18);
        colorPB[i]->
        connect(colorPB[i],SIGNAL(clicked()),this,SLOT(colorSelection()));
    }

    colorPB[0]->setStyleSheet("background-color: red");
    colorPB[1]->setStyleSheet("background-color: blue");
    colorPB[2]->setStyleSheet("background-color: orange");
    colorPB[3]->setStyleSheet("background-color: green");
    colorPB[4]->setStyleSheet("background-color: white");
    colorPB[5]->setStyleSheet("background-color: yellow");



}

void ColorPicker::colorSelection()
{
    for(int i = 0; i < 6 ; i++)
    {
        if(sender() == colorPB[i])
        {
            emit colorSendSignal((color)i);
        }
    }
}

void ColorPicker::setMatrix(color cubeMatrix[18][3])
{
    for(int y = 0;y<18;y++)
    {
        for(int x = 0;x<3;x++)
        {
            cubeInputMatrix[y][x] = cubeMatrix[y][x];
        }
    }
}

void ColorPicker::focusOutEvent(QFocusEvent *)
{
    this->hide();
}

ColorPicker::~ColorPicker()
{

}
