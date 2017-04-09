#ifndef _POINT_H_
#define _POINT_H_

#include "object.h"

class Point : public Object{

public:

	Point(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void clipping(Window window, Viewport viewport) {
		
	}

	void virtual draw(Viewport viewport, Window window, cairo_t *cr) {
	  normalizedCoordinates.clear();
	  drawNormalized(window);

	  printf("%s\n", "Limite esquerdo window");
  	  printf("%f\n", window.getXmin());

	  printf("%s\n", "Limite esquerdo window");
  	  printf("%f\n", window.getXmax());

	  printf("%s\n", " Esse valor deve ser -1" );
	  printf("%f\n", normalizedCoordinates.at(0)->getX());
	  float x = viewport.obterXdaViewport(normalizedCoordinates.at(0)->getX(), window.getXmin(), window.getXmax());
	  printf("%s\n", " Esse valor deve ser 0" );
	  printf("%f\n", x);

	  float y = viewport.obterYdaViewport(normalizedCoordinates.at(0)->getY(), window.getYmin(), window.getYmax());
	  
	  cairo_arc(cr, x, y, 1, 0, 2*3.1415);
	  cairo_stroke(cr);
	}
	
};

#endif
