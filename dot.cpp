#include "dot.h"

Dot::Dot(const char* nome, vector<Point*> coordenadas) : Object(nome, coordenadas) {
}

void Dot::clipping(Window window, Viewport viewport) {
    if (normalizedCoordinates.at(0)->getX() > 0.9 || normalizedCoordinates.at(0)->getX() < -0.9 || normalizedCoordinates.at(0)->getY() > 0.9 || normalizedCoordinates.at(0)->getY() < -0.9) {
        desenhar = false;
    }
}

void Dot::draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
    normalizedCoordinates.clear();
    drawNormalized(window);
    desenhar = true;
    clipping(window, viewport);

    if (desenhar) {
        int x = viewport.obterXdaViewport(normalizedCoordinates.at(0)->getX(), window.getXmin(), window.getXmax());
        int y = viewport.obterYdaViewport(normalizedCoordinates.at(0)->getY(), window.getYmin(), window.getYmax());

        cairo_arc(cr, x, y, 1, 0, 2 * 3.1415);
        cairo_stroke(cr);
    }
}
