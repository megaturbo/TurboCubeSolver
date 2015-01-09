#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "IsometricCubeWidget.h"
#include "Cube.h"
#include "Fridrich.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

private:
    IsometricCubeWidget *isometricCubeWidget;
    QPushButton *scramblePB;
    QPushButton *solvePB;
    QPushButton *resetPB;
    QPushButton *sequencePB;
    QLineEdit *sequenceLE;

    Cube *displayedCube;

signals:

public slots:
    void scrambleSlot();
    void solveSlot();
    void sendSequenceSlot();

};

#endif // MAINWIDGET_H