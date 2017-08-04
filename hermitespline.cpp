#include "hermitespline.h"

HermiteSpline::HermiteSpline(const char* nome, vector<Point*> coordenadas,
        Point *p1, Point *p4, Point *r1, Point *r4) : Object(nome, coordenadas) {
    
    this->p1 = p1;
    this->p4 = p4;
    this->r1 = r1;
    this->r4 = r4;

    Matrix m;

    float geometryVectorX[4] = {p1->getX(), p4->getX(), r1->getX(), r4->getX()};
    float geometryVectorY[4] = {p1->getY(), p4->getY(), r1->getY(), r4->getY()};

    float geometryVectorZ[4] = {p1->getZ(), p4->getZ(), r1->getZ(), r4->getZ()};

    float resultX[4] = {0, 0, 0, 0};
    float resultY[4] = {0, 0, 0, 0};
    float resultZ[4] = {0, 0, 0, 0};


    m.multiplyHermiteToGeometryVector(geometryVectorX, resultX);
    m.multiplyHermiteToGeometryVector(geometryVectorY, resultY);
    m.multiplyHermiteToGeometryVector(geometryVectorZ, resultZ);

    float x_final, y_final, z_final;

    float matrixT[4];

    for (float t = 0.0; t < 1.1; t = t + 0.1) {
        matrixT[0] = t * t * t;
        matrixT[1] = t * t;
        matrixT[2] = t;
        matrixT[3] = 1.0;

        x_final = 0.0;
        y_final = 0.0;
        for (int i = 0; i < 4; i++) {
            x_final += matrixT[i] * resultX[i];
            y_final += matrixT[i] * resultY[i];
            z_final += matrixT[i] * resultZ[i];
        }

        this->coordenadas.push_back(new Point(x_final, y_final, z_final));
    }

}

void HermiteSpline::clipping(Window window, Viewport viewport) {
    // método de clippagem da reta invocado
}

void HermiteSpline::draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
    auxLines.clear();

    for (int i = 0; i < coordenadas.size() - 1; i++) {
        vector<Point*> points;
        points.push_back(new Point(coordenadas.at(i)->getX(), coordenadas.at(i)->getY(), coordenadas.at(i)->getZ()));
        points.push_back(new Point(coordenadas.at(i + 1)->getX(), coordenadas.at(i + 1)->getY(), coordenadas.at(i + 1)->getZ()));
        const char* emptyName = "";
        Line* line = new Line(emptyName, points);
        auxLines.push_back(line);
        line->draw(viewport, window, cr, clippingType);
    }

}
