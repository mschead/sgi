#ifndef _BSPLINE_H_
#define _BSPLINE_H_

#include "line.h"

class BSpline : public Object {
public:

    BSpline(const char* nome, vector<Point*> coordenadas, vector<Point*> userPoints);

    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

    void clipping(Window window, Viewport viewport);
    void desenharCurvaFwdDiff(float pontosFwdX[4], float pontosFwdY[4], float pontosFwdZ[4]);

private:
    std::vector<Point*> userPoints;
    std::vector<Line*> auxLines;
    float matrizTeta[4][4];

};

#endif
