#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "object.h"
#define Z_STUB 0

class Polygon : public Object {
public:

    Polygon(const char* nome, vector<Point*> coordenadas);
    void clipping(Window window, Viewport viewport);
    void clippingReta(Point* coordenadaAnterior, Point* coordenadaPosterior);
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

private:

    vector<Point*> coordenadaAuxiliar;
    bool desenhar;
};

#endif
