#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "object.h"

class Polygon : public Object{
	
public:

	Polygon(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void draw(Viewport viewport, Window window, cairo_t *cr) {
		int x_inicial, y_inicial, x_final, y_final;
		int x_init = coordenadas.back()->getX();
		int y_init = coordenadas.back()->getY();

		for(int n = 0; n < coordenadas.size(); n++){
			x_inicial = coordenadas.back()->getX();			
			y_inicial = coordenadas.back()->getY();
			
			coordenadas.pop_back();

			if(n == coordenadas.size() - 1){
				x_final = x_init;
				y_final = y_init;
			} else {
				x_final = coordenadas.back()->getX();
				y_final = coordenadas.back()->getY();
			}

			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
		}
	}


};

#endif