#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "InputWidget.h"
#include "CubeInputWidget.h"
#include "IsometricCubeWidget.h"
#include "Cube.h"
#include "Fridrich.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

private:
    InputWidget *inputWidget;
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

    // Resolution menu
    QLabel *pastMovesLabel;
    QLabel *nextMovesLabel;
    QLabel *actMoveLabel;
    QPushButton *pastMovePB;
    QPushButton *nextMovePB;
    QStringList *sResolution;
    int actMoveID;

    // Orientation menu
    QPushButton **movesPB;

    Cube *displayedCube;

    void initSolvedCube();
    void refreshResolutionState();

signals:

public slots:
    void scrambleSlot();
    void solveSlot();
    void sendSequenceSlot();
    void resetSlot();
    void reverseSequenceSlot();
    void turnXSlot();
    void turnYSlot();
    void turnZSlot();
    void startCubeInput();
    void cubieModified(int, int, color);

    void nextMove();
    void pastMove();

};

#endif // MAINWIDGET_H
