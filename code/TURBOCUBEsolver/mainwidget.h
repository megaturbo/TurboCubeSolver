#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "CubeInput.h"
#include "IsometricCubeWidget.h"
#include "Cube.h"
#include "Fridrich.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

private:
    CubeInputWidget *cubeInputWidget;
    IsometricCubeWidget *isometricCubeWidget;

    // Menu
    QPushButton *scramblePB;
    QPushButton *solvePB;
    QPushButton *resetPB;
    QPushButton *sequencePB;
    QPushButton *reverseSequencePB;
    QPushButton *cubeInputPB;
    QLineEdit *sequenceLE;

    // Orientation menu
    QPushButton **movesPB;

    Cube *displayedCube;

    void initSolvedCube();

signals:

public slots:
    void scrambleSlot();
    void solveSlot();
    void sendSequenceSlot();
    void resetSlot();
    void reverseSequenceSlot();
    void turnYSlot();
    void startCubeInput();

};

#endif // MAINWIDGET_H
