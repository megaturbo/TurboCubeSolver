#ifndef CUBE_H
#define CUBE_H

class Cube{
  public:
    Cube ();
    Cube(QMatrix<Cubie> Cube);
    void setMatrix(QMatrix<Cubie> Cube);
    //returns faces the cubie's on
    QArray<int> locateCubie(int c1, int c2, int c3 = 0);
  private:
    //actually moves the faces
    void moveSequence(QString sequence);

    //matrix rotation per face
    void u();
    void up();
    void u2();
    void d();
    void dp();
    void d2();
    void b();
    void bp();
    void b2();
    void f();
    void fp();
    void f2();
    void r();
    void rp();
    void r2();
    void l();
    void lp();
    void l2();

    QMatrix<Cubie> cube;
}
#endif // CUBE_H
