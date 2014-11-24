#include "notation_decoder.h"

#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    //Instanciation
    entry = new QLineEdit(this);
    btn_decode = new QPushButton("Decode",this);
    moves = new QTextEdit(this);

    //Layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(entry, 0, 0);
    layout->addWidget(btn_decode, 0, 1);
    layout->addWidget(moves, 1,0);

    this->setLayout(layout);

    connect(btn_decode, SIGNAL(clicked()), this, SLOT(decode()));

}

void Widget::decode()
{
    QString encoded = entry->text();
    QString *decoded = new QString();

    QStringList split = encoded.split(' ');

    foreach (QString move, split) {
        decoded->append("Turn ");
        decoded->append(move[0]);

        if(move.length()>1)
        {
            if(move[1]=='2')
            {
                decoded->append(" +180°");
            }else{
                decoded->append(" -90°");
            }
        }else{
            decoded->append(" +90°");
        }
        decoded->append("\n");
    }



    moves->setText(*decoded);
}
