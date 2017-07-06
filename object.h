#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "point.h"
#include "matriz.h"
#include <math.h>
#include "matrix3d.h"
#include "window.h"
#include "viewport.h"
#include <gtk/gtk.h>

using namespace std;

class Object {
    
public:
    Object(const char* nome, vector<Point*> coordenadas);
    Object(const char* nome);
    ~Object();
    
    
    virtual void draw (Viewport viewport, Window window, cairo_t *cr, int clippingType) = 0;
    virtual void clipping (Window window, Viewport viewport) = 0;
    
    
    void drawNormalized(Window window);
    vector<Point*> ortogonalize(Window window);
    
    
    Point pontoMedio();
    void translate(int entryX, int entryY, int entryZ);
    void scale(float entryX, float entryY, float entryZ);
    void rotate(int angX, int angY, int angZ);
    void rotateUsingCoordinate(int ang, float entryX, float entryY);
    
    
    const char* getName() { return nome; }
    vector<Point*> getPoints() { return coordenadas; }
    
    
protected:
    const char* nome;
    vector<Point*> coordenadas;
    vector<Point*> normalizedCoordinates;
    
};

#endif
