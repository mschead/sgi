#ifndef _DOT_H_
#define _DOT_H_

#include "object.h"

class Dot : public Object {
public:

    Dot(const char* nome, vector<Point*> coordenadas);

    void clipping(Window window, Viewport viewport);
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

private:
    bool desenhar = true;
};

#endif
