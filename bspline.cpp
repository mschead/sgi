#include "bspline.h"

BSpline::BSpline(const char* nome, vector<Point*> coordenadas, vector<Point*> userPoints) : Object(nome, coordenadas) {
    this->userPoints = userPoints;
    float teta = 0.01;

    matrizTeta[0][0] = 0;
    matrizTeta[0][1] = 0;
    matrizTeta[0][2] = 0;
    matrizTeta[0][3] = 1;

    matrizTeta[1][0] = teta * teta * teta;
    matrizTeta[1][1] = teta * teta;
    matrizTeta[1][2] = teta;
    matrizTeta[1][3] = 0;

    matrizTeta[2][0] = 6.0 * teta * teta * teta;
    matrizTeta[2][1] = 2.0 * teta * teta;
    matrizTeta[2][2] = 0;
    matrizTeta[2][3] = 0;

    matrizTeta[3][0] = 6.0 * teta * teta * teta;
    matrizTeta[3][1] = 0;
    matrizTeta[3][2] = 0;
    matrizTeta[3][3] = 0;

    Matrix m;

    float coeficienteX[4], coeficienteY[4], coeficienteZ[4];
    float resultX[4], resultY[4], resultZ[4];
    float pontosFwdX[4], pontosFwdY[4], pontosFwdZ[4];

    for (int i = 0; i < userPoints.size() - 3; i++) {
        Point *p1 = userPoints.at(i);
        Point *p2 = userPoints.at(i + 1);
        Point *p3 = userPoints.at(i + 2);
        Point *p4 = userPoints.at(i + 3);

        coeficienteX[0] = p1->getX();
        coeficienteX[1] = p2->getX();
        coeficienteX[2] = p3->getX();
        coeficienteX[3] = p4->getX();

        coeficienteY[0] = p1->getY();
        coeficienteY[1] = p2->getY();
        coeficienteY[2] = p3->getY();
        coeficienteY[3] = p4->getY();

        coeficienteZ[0] = p1->getZ();
        coeficienteZ[1] = p2->getZ();
        coeficienteZ[2] = p3->getZ();
        coeficienteZ[3] = p4->getZ();

        resultX[0] = 0;
        resultX[1] = 0;
        resultX[2] = 0;
        resultX[3] = 0;

        resultY[0] = 0;
        resultY[1] = 0;
        resultY[2] = 0;
        resultY[3] = 0;

        resultZ[0] = 0;
        resultZ[1] = 0;
        resultZ[2] = 0;
        resultZ[3] = 0;

        m.multiplyBSplineToGeometryVector(coeficienteX, resultX);
        m.multiplyBSplineToGeometryVector(coeficienteY, resultY);
        m.multiplyBSplineToGeometryVector(coeficienteZ, resultZ);

        pontosFwdX[0] = 0;
        pontosFwdX[1] = 0;
        pontosFwdX[2] = 0;
        pontosFwdX[3] = 0;

        pontosFwdY[0] = 0;
        pontosFwdY[1] = 0;
        pontosFwdY[2] = 0;
        pontosFwdY[3] = 0;

        pontosFwdZ[0] = 0;
        pontosFwdZ[1] = 0;
        pontosFwdZ[2] = 0;
        pontosFwdZ[3] = 0;

        m.multiplyTetaMatrixBSplineToGeometryVector(matrizTeta, resultX, pontosFwdX);
        m.multiplyTetaMatrixBSplineToGeometryVector(matrizTeta, resultY, pontosFwdY);
        m.multiplyTetaMatrixBSplineToGeometryVector(matrizTeta, resultZ, pontosFwdZ);

        desenharCurvaFwdDiff(pontosFwdX, pontosFwdY, pontosFwdZ);

    }

}

void BSpline::draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
    normalizedCoordinates.clear();
    auxLines.clear();
    drawNormalized(window);

    for (int i = 0; i < normalizedCoordinates.size() - 1; i++) {

        vector<Point*> points;
        points.push_back(coordenadas.at(i));
        points.push_back(coordenadas.at(i + 1));
        const char* emptyName = "";
        Line* line = new Line(emptyName, points);

        auxLines.push_back(line);
        line->draw(viewport, window, cr, clippingType);
    }
}

void BSpline::desenharCurvaFwdDiff(float pontosFwdX[4], float pontosFwdY[4], float pontosFwdZ[4]) {
    float xOld = pontosFwdX[0];
    float yOld = pontosFwdY[0];
    float zOld = pontosFwdZ[0];

    coordenadas.push_back(new Point(pontosFwdX[0], pontosFwdY[0], pontosFwdZ[0]));

    printf("%s\n\n", "Comecando foward differences");

    for (int i = 0; i < 99; i++) {
        pontosFwdX[0] += pontosFwdX[1];
        pontosFwdX[1] += pontosFwdX[2];
        pontosFwdX[2] += pontosFwdX[3];

        pontosFwdY[0] += pontosFwdY[1];
        pontosFwdY[1] += pontosFwdY[2];
        pontosFwdY[2] += pontosFwdY[3];

        pontosFwdZ[0] += pontosFwdZ[1];
        pontosFwdZ[1] += pontosFwdZ[2];
        pontosFwdZ[2] += pontosFwdZ[3];

        coordenadas.push_back(new Point(pontosFwdX[0], pontosFwdY[0], pontosFwdZ[0]));

        xOld = pontosFwdX[0];
        yOld = pontosFwdY[0];
        zOld = pontosFwdZ[0];

    }
    printf("%s\n\n", "Terminando foward differences");
}

void BSpline::clipping(Window window, Viewport viewport) {
}
