#ifndef CUBEINPUT_H
#define CUBEINPUT_H

#include <QDialog>

namespace Ui{
class CubeInput;
}

class CubeInput : public QDialog
{
public:
    CubeInput(QDialog *parent = 0);
private:
    Ui::CubeInput *ui;
};

#endif // CUBEINPUT_H
