#include "TurboCubeSolver.h"
#include "ui_turbocubesolver.h"
#include "cube.h"


TURBOCUBEsolver::TURBOCUBEsolver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TURBOCUBEsolver)
{
    ui->setupUi(this);
}

TURBOCUBEsolver::~TURBOCUBEsolver()
{
    delete ui;
}
