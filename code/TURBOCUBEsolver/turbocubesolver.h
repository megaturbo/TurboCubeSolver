#ifndef TURBOCUBESOLVER_H
#define TURBOCUBESOLVER_H

#include <QMainWindow>

namespace Ui {
class TURBOCUBEsolver;
}

class TURBOCUBEsolver : public QMainWindow
{
    Q_OBJECT

public:
    explicit TURBOCUBEsolver(QWidget *parent = 0);
    ~TURBOCUBEsolver();

private:
    Ui::TURBOCUBEsolver *ui;
};

#endif // TURBOCUBESOLVER_H
