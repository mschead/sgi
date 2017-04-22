#ifndef _HERMITESPLINE_H_
#define _HERMITESPLINE_H_ 

#include "object.h"

class HermiteSpline : public Object {
	
public:
	HermiteSpline(char* nome, vector<Coordenada*> coordenadas, 
		Coordenada *p1, Coordenada *p4, Coordenada *r1, Coordenada *r4) : Object(nome, coordenadas) {
		this->p1 = p1;
		this->p4 = p4;
		this->r1 = r1;
		this->r4 = r4;

		Matrix m;
		
		float geometryVectorX[4] = {p1->getX(), p4->getX(), r1->getX(), r4->getX()};
		float geometryVectorY[4] = {p1->getY(), p4->getY(), r1->getY(), r4->getY()};

		float geometryVectorZ[4] = {0, 0, 0, 0};

		float resultX[4] = {0, 0, 0, 0};
		float resultY[4] = {0, 0, 0, 0};
		// float resultZ[4] = {0, 0, 0, 0};


		m.multiplyHermiteToGeometryVector(geometryVectorX, resultX);
		m.multiplyHermiteToGeometryVector(geometryVectorY, resultY);
		// m.multiplyHermiteToGeometryVector(geometryVectorZ, resultZ);

		float x_final, y_final, z_final;

		float matrixT[4];

		for (float t = 0.0; t < 1.1; t = t + 0.1) {
			matrixT[0] = 3.0 * t * t;
			matrixT[1] = 2.0 * t;
			matrixT[2] = 1.0;
			matrixT[3] = 0.0;
			
			x_final = 0.0;
			y_final = 0.0;
			for (int i = 0; i < 4; i++) {
				x_final += matrixT[i] * resultX[i];
				y_final += matrixT[i] * resultY[i];
				// por enquanto nao precisa
				//z = matrixT[i] * resultZ[i];				
			}

			this->coordenadas.push_back(new Coordenada(x_final, y_final));
		}

	}

	void clipping(Window window, Viewport viewport) {
		// método de clippagem da reta invocado
	}

	void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
		normalizedCoordinates.clear();
		auxLines.clear();
		drawNormalized(window);

		for (int i = 0; i < normalizedCoordinates.size() - 1; i++) {
		
		    int x1 = viewport.obterXdaViewport(normalizedCoordinates.at(i)->getX(), window.getXmin(), window.getXmax());
		    int y1 = viewport.obterYdaViewport(normalizedCoordinates.at(i)->getY(), window.getYmin(), window.getYmax());

		    int x2 = viewport.obterXdaViewport(normalizedCoordinates.at(i+1)->getX(), window.getXmin(), window.getXmax());
		    int y2 = viewport.obterYdaViewport(normalizedCoordinates.at(i+1)->getY(), window.getYmin(), window.getYmax());

		    vector<Coordenada*> points;
		    points.push_back(new Coordenada(x1, y1));
		    points.push_back(new Coordenada(x2, y2));
		    char* emptyName = "";
		    Line* line = new Line(emptyName, points);
		    auxLines.push_back(line);
		    line->draw(viewport, window, cr, clippingType);
			// printf("(%f, %f) - (%f, %f)\n", normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY(), 
			// 	normalizedCoordinates.at(i + 1)->getX(), normalizedCoordinates.at(i + 1)->getY());
		}

	}

private:
	Coordenada *p1, *p4, *r1, *r4;
	std::vector<Line*> auxLines;


};

#endif
