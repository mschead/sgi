#include "object3d.h"

Object3D::Object3D(const char* nome, vector<Polygon*> wireframePolygons, vector<Point*> coordenadas) : Object(nome, coordenadas) {
    this->nome = nome;
    this->wireframePolygons = wireframePolygons;
}

Object3D::~Object3D() {
    wireframePolygons.clear();
}

void Object3D::clipping(Window window, Viewport viewport) {
    //clipping feito pelas retas
}

void Object3D::draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
    normalizedCoordinates.clear();

    for (int i = 0; i < wireframePolygons.size(); i++) {
        wireframePolygons.at(i)->draw(viewport, window, cr, clippingType);
    }
}

