#include "TurboCubeSolver.h"
<<<<<<< HEAD
#include "ui_TurboCubeSolver.h"
#include "CubeInput.h"
=======
#include "ui_turbocubesolver.h"
#include "cube.h"
#include "qdebug.h"
>>>>>>> 48a3c84d87bc4b76d7f6510f87d443f9b1394ec0

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
    CubeInput *c = new CubeInput();
    c->show();
}

void TURBOCUBEsolver::on_pushButton_released()
{

}
