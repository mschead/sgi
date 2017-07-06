#ifndef _HERMITESPLINE_H_
#define _HERMITESPLINE_H_ 

#include "line.h"

class HermiteSpline : public Object {
public:
    HermiteSpline(const char* nome, vector<Point*> coordenadas,
            Point *p1, Point *p4, Point *r1, Point *r4);

    void clipping(Window window, Viewport viewport);
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

private:
    Point *p1, *p4, *r1, *r4;
    vector<Line*> auxLines;

};

#endif
