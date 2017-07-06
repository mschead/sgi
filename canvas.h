#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "object.h"

class Canvas : public Object {
public:

    Canvas(const char* nome, vector<Point*> coordenadas);

    void clipping(Window window, Viewport viewport);
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

};

#endif
