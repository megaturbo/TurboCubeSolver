#include "TurboCubeSolver.h"
#include "ui_TurboCubeSolver.h"
#include "CubeInput.h"


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

void TURBOCUBEsolver::on_pushButton_clicked()
{
    CubeInput *c = new CubeInput();
    c->show();
}

void TURBOCUBEsolver::on_pushButton_released()
{

}
