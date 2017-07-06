#include <math.h>
#include <stdio.h>
#define PI 3.14159265

class Matrix3D {
public:
    Matrix3D();

    void setZero();
    void setTranslate(float entryX, float entryY, float entryZ);
    void setScale(float entryX, float entryY, float entryZ);
    void setRotateX(int ang);
    void setRotateY(int ang);
    void setRotateZ(int ang);
    void setProjecaoPerspectiva(float zCop);
    void multiplyPointToMatrix(float point[4], Matrix3D transform, float result[4]);
    void multiplyMatrices(Matrix3D a, Matrix3D b, Matrix3D &result);
    void printMatrix4x4(Matrix3D a);
    void printMatrix1x4(int a[4]);

private:
    float identity[4][4];


};