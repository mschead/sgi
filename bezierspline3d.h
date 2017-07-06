#ifndef _BEZIERSPLINE3D_H_
#define _BEZIERSPLINE3D_H_ 

#include "line.h"

class BezierSpline3D : public Object {
public:
    BezierSpline3D(char* nome, vector<Point*> coordenadas,
            Point *p11, Point *p12, Point *p13, Point *p14,
            Point *p21, Point *p22, Point *p23, Point *p24,
            Point *p31, Point *p32, Point *p33, Point *p34,
            Point *p41, Point *p42, Point *p43, Point *p44);

    void clipping(Window window, Viewport viewport);
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

private:
    Point *p11, *p12, *p13, *p14, 
          *p21, *p22, *p23, *p24, 
          *p31, *p32, *p33, *p34, 
          *p41, *p42, *p43, *p44;
    
    std::vector<Line*> auxLines;
    std::vector<Point*> vetores[6];

};

#endif
