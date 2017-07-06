/* 
 * File:   SurfaceSplineFD.h
 * Author: schead
 *
 * Created on 27 de Maio de 2017, 22:58
 */

#ifndef SURFACESPLINEFD_H
#define SURFACESPLINEFD_H

#include <cstdio>
#include "line.h"

class SurfaceSplineFD : public Object {
public:
    SurfaceSplineFD(const char* nome, vector<Point*> coordenadas,
            Point *p11, Point *p12, Point *p13, Point *p14,
            Point *p21, Point *p22, Point *p23, Point *p24,
            Point *p31, Point *p32, Point *p33, Point *p34,
            Point *p41, Point *p42, Point *p43, Point *p44);

    void drawCurveInT(float DDX[4][4], float DDY[4][4], float DDZ[4][4]);
    void drawCurveInS(float DDX[4][4], float DDY[4][4], float DDZ[4][4]);
    void drawCurveFwdDiff(float pontosFwdX[4], float pontosFwdY[4], float pontosFwdZ[4], int vector, bool usingVectorsT);

    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);
    void clipping(Window window, Viewport viewport);


private:
    Point *p11, *p12, *p13, *p14, 
          *p21, *p22, *p23, *p24, 
          *p31, *p32, *p33, *p34, 
          *p41, *p42, *p43, *p44;
    
    vector<Line*> auxLines;
    vector<Point*> vectors_t[6];
    vector<Point*> vectors_s[6];

};

#endif /* SURFACESPLINEFD_H */

