#include <QWidget>

class QTextEdit;
class QLineEdit;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);

private:
    QTextEdit *moves;
    QLineEdit *entry;
    QPushButton *btn_decode;

public slots:
    void decode();

};
