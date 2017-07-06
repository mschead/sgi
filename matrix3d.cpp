#include "matrix3d.h"

Matrix3D::Matrix3D() {
    identity[0][0] = 1.0;
    identity[1][0] = 0.0;
    identity[2][0] = 0.0;
    identity[3][0] = 0.0;

    identity[0][1] = 0.0;
    identity[1][1] = 1.0;
    identity[2][1] = 0.0;
    identity[3][1] = 0.0;

    identity[0][2] = 0.0;
    identity[1][2] = 0.0;
    identity[2][2] = 1.0;
    identity[3][2] = 0.0;

    identity[0][3] = 0.0;
    identity[1][3] = 0.0;
    identity[2][3] = 0.0;
    identity[3][3] = 1.0;
}

void Matrix3D::setTranslate(float entryX, float entryY, float entryZ) {
    identity[3][0] = entryX;
    identity[3][1] = entryY;
    identity[3][2] = entryZ;
}

void Matrix3D::setScale(float entryX, float entryY, float entryZ) {
    identity[0][0] = entryX;
    identity[1][1] = entryY;
    identity[2][2] = entryZ;
}

void Matrix3D::setRotateX(int ang) {
    float angleRad = ang * PI / 180;

    identity[1][1] = cos(angleRad);
    identity[1][2] = -1.0 * sin(angleRad);
    identity[2][1] = sin(angleRad);
    identity[2][2] = cos(angleRad);
}

void Matrix3D::setRotateY(int ang) {
    float angleRad = ang * PI / 180;

    identity[0][0] = cos(angleRad);
    identity[0][2] = -1.0 * sin(angleRad);
    identity[2][0] = sin(angleRad);
    identity[2][2] = cos(angleRad);
}

void Matrix3D::setRotateZ(int ang) {
    float angleRad = ang * PI / 180;

    identity[0][0] = cos(angleRad);
    identity[0][1] = sin(angleRad);
    identity[1][0] = -1.0 * sin(angleRad);
    identity[1][1] = cos(angleRad);
}

void Matrix3D::setProjecaoPerspectiva(float zCop) {
    identity[2][3] = 1.0 / zCop;
    identity[3][3] = 0.0;
}

void Matrix3D::setZero() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            identity[i][j] = 0;
        }
    }
}

void Matrix3D::multiplyPointToMatrix(float point[4], Matrix3D transform, float result[4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            result[j] += point[i] * transform.identity[i][j];
        }
    }
}

void Matrix3D::multiplyMatrices(Matrix3D a, Matrix3D b, Matrix3D &result) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.identity[i][j] += a.identity[i][k] * b.identity[k][j];
            }
        }
    }
}

void Matrix3D::printMatrix4x4(Matrix3D a) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f\t", a.identity[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Matrix3D::printMatrix1x4(int a[4]) {
    for (int i = 0; i < 4; i++) {
        printf("%d ", a[i]);
    }
}

