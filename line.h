#ifndef _LINE_H_
#define _LINE_H_

#include "object.h"

using namespace std;

class Line : public Object {
public:

    Line(const char* nome, vector<Point*> coordenadas);

    void clipping(Window window, Viewport viewport);
    bool liang_barsky(Window window, Viewport viewport);

    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);

private:
    bool desenhar = true;

};

#endif
