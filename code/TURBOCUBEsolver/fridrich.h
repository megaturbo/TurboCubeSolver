#ifndef FRIDRICH_H
#define FRIDRICH_H

class Fridrich
{
public:
    QString solve();

private:
    //int face is the face we begin with,
    //usually white so we set it at 0
    //by default
    QString cross(int face = 0);
    QString F2L(int face = 0);
    //as 2 layers are solved at this point,
    //we don't need to set a face to solve
    QString OLL();
    QString PLL();
};

#endif // FRIDRICH_H
