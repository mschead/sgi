#ifndef _LINE_H_
#define _LINE_H_

#include "object.h"

class Line : public Object {
	
public:

	Line(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void draw(Viewport viewport, Window window, cairo_t *cr) {
	  normalizedCoordinates.clear();
	  drawNormalized(window);

	  // for (Coordenada* c : normalizedCoordinates) {
	  // 	printf("%f\n", c->getX());
	  // 	printf("%f\n", c->getY());
	  // }

	  int x1 = viewport.obterXdaViewport(normalizedCoordinates.at(0)->getX(), window.getXmin(), window.getXmax());
	  int y1 = viewport.obterYdaViewport(normalizedCoordinates.at(0)->getY(), window.getYmin(), window.getYmax());

	  int x2 = viewport.obterXdaViewport(normalizedCoordinates.at(1)->getX(), window.getXmin(), window.getXmax());
	  int y2 = viewport.obterYdaViewport(normalizedCoordinates.at(1)->getY(), window.getYmin(), window.getYmax());

	  printf("%d\n", x1);
	  printf("%d\n", y1);

  	  printf("%d\n", x2);
	  printf("%d\n", y2);


	  cairo_move_to(cr, x1, y1);
	  cairo_line_to(cr, x2, y2);
	  cairo_stroke(cr);
	}

};

#endif