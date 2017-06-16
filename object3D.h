#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <vector>
#include "object.h"

using namespace std;

class Object3D : public Object {
    
public:
    Object3D(const char* nome, vector<Polygon*> wireframePolygons, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
        this->nome = nome;
        this->wireframePolygons = wireframePolygons;
    }
    
    void clipping (Window window, Viewport viewport) {
        //clipping feito pelas retas
    }
    
    void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
        normalizedCoordinates.clear();
        
        for (int i = 0; i < wireframePolygons.size(); i++) {
            wireframePolygons.at(i)->draw(viewport, window, cr, clippingType);
        }
    }
    
    ~Object3D() {
        wireframePolygons.clear();
    }
    
protected:
    vector<Polygon*> wireframePolygons;
};

#endif
