#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "object.h"

class Canvas : public Object {
	
public:

	Canvas(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void clipping(Window window, Viewport viewport) {
		
	}

	void draw(Viewport viewport, Window window, cairo_t *cr) {
		float x_inicial, y_inicial, x_final, y_final;
		float x_init = coordenadas.front()->getX();
		float y_init = coordenadas.front()->getY();

		for(int n = 0; n < coordenadas.size(); n++){
			x_inicial = coordenadas.at(n)->getX();			
			y_inicial = coordenadas.at(n)->getY();
			
			if(n == coordenadas.size() - 1){
				x_final = x_init;
				y_final = y_init;
			} else {
				x_final = coordenadas.at(n+1)->getX();
				y_final = coordenadas.at(n+1)->getY();
			}


			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
			cairo_stroke(cr);
		}
	}


};

#endif