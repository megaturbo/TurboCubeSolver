#include "turbocubesolver.h"
#include "ui_turbocubesolver.h"

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
