#ifndef _LINE_H_
#define _LINE_H_

#include "object.h"

class Line : public Object {
	
public:

	Line(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void draw(Viewport viewport, Window window, cairo_t *cr) {
	  int x1 = viewport.obterXdaViewport(getPoints().at(0)->getX(), window.getXmin(), window.getXmax());
	  int y1 = viewport.obterYdaViewport(getPoints().at(0)->getY(), window.getYmin(), window.getYmax());

	  int x2 = viewport.obterXdaViewport(getPoints().at(1)->getX(), window.getXmin(), window.getXmax());
	  int y2 = viewport.obterYdaViewport(getPoints().at(1)->getY(), window.getYmin(), window.getYmax());

	  cairo_move_to(cr, x1, y1);
	  cairo_line_to(cr, x2, y2);
	  cairo_stroke(cr);
	}

};

#endif