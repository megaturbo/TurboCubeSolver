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
    QTextEdit *moves_instructions;
    QLineEdit *entry;
    QPushButton *btn_decode;

    bool isAMove(QChar);

public slots:
    void decode();

};
