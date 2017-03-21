#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "object.h"

class Polygon : public Object{
	
	public:

		Polygon(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
		}

		void draw(Viewport viewport, Window window, cairo_t *cr) {
		}


};

#endif