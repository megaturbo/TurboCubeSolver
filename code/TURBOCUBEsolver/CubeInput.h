
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>

class CubeInput : public QWidget
{
    Q_OBJECT

public:
    explicit CubeInput(QWidget *parent = 0);
    ~CubeInput();

private:
    //top
    QPushButton *pbTop0 ;
    QPushButton *pbTop1 ;
    QPushButton *pbTop2 ;

    //central
    QPushButton *pbMid0 ;
    QPushButton *pbMid1 ;
    QPushButton *pbMid2 ;

    //bottom
    QPushButton *pbBot0 ;
    QPushButton *pbBot1 ;
    QPushButton *pbBot2 ;

    //control
    QPushButton *pbUp;
    QPushButton *pbDown;
    QPushButton *pbRight;
    QPushButton *pbLeft;

    //mold
    QRect *rectMold;

    void setButtonGrid();
};

