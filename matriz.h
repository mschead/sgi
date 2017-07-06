#include <math.h>
#include <stdio.h>
#define PI 3.14159265

class Matrix {
    
public:
    Matrix();
    
    void setTranslate(float entryX, float entryY);
    void setScale(float entryX, float entryY);
    void setRotate(int ang);
    void setZero();
    void multiplyPointToMatrix(float point[3], Matrix transform, float result[3]);
    void multiplyPointToMatrix3D(float point[4], float transform[4][4], float result[4]);
    void multiplyHermiteToGeometryVector(float geometryVector[4], float result[4]);
    void multiplyMatrices4x4by4x4(float matriz[4][4], float geometryVector[4][4], float result[4][4]);
    void multiplyBSplineToGeometryVector(float geometryVector[4], float result[4]);
    void multiply4x4by4x1(float bigMatrix[4][4], float lilyMatrix[4], float result[4]);
    void multiplyTetaMatrixBSplineToGeometryVector(float tetaMatrix[4][4], float geometryVector[4], float result[4]);
    void multiplyMatrices(Matrix a, Matrix b, Matrix &result);
    void printMatrix3x3(Matrix a);
    void printMatrix1x3(int a[3]);
    
private:	
    float identity[3][3];
    
};
