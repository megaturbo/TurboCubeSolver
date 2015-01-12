#include "TurboCubeSolver.h"
#include "ui_TurboCubeSolver.h"
#include "CubeInputWidget.h"
#include "ui_turbocubesolver.h"
#include "cube.h"
#include "qdebug.h"

using namespace CubeColor;

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
    CubeInputWidget *c = new CubeInputWidget();
    c->show();
}

void TURBOCUBEsolver::on_pushButton_released()
{

}
