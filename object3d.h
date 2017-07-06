#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <vector>
#include "polygon.h"

using namespace std;

class Object3D : public Object {
    
public:
    Object3D(const char* nome, vector<Polygon*> wireframePolygons, vector<Point*> coordenadas);
    ~Object3D();
    
    void clipping (Window window, Viewport viewport);
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType);
    
protected:
    vector<Polygon*> wireframePolygons;
};

#endif
