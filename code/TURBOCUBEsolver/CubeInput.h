#include <CubeColor.h>
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
using namespace CubeColor;
class CubeInput : public QWidget
{
    Q_OBJECT

public:
    explicit CubeInput(QWidget *parent = 0);
    ~CubeInput();

private:
    //matrix preset
    void setMatrix(color cubeInputMatrix[18][3]);

    //matrix attribute
    color cubeInputMatrix[18][3];

    //button array
    QPushButton ***pbGroup;


    //control
    QPushButton *pbUp;
    QPushButton *pbDown;
    QPushButton *pbRight;
    QPushButton *pbLeft;

    //mold
    QRect *rectMold;

public slots:
    //control slots
    void changeFaceRight();
    void changeFaceLeft();
    void changeFaceUp();
    void changeFaceDown();

    //face slot
    void changeSquare();

};

