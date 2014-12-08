#include "cubeinput.h"
#include "ui_CubeInput.h"

CubeInput::CubeInput(QDialog* parent) :
    QDialog(parent),
    ui(new Ui::CubeInput)
{
    ui->setupUi(this);
}
