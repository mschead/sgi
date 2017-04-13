#ifndef _HERMITESPLINE_H_
#define _HERMITESPLINE_H_ 

#include "object.h"

class HermiteSpline : public Object {
	
public:
	HermiteSpline(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void virtual draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
		//fazer draw normalized

		Matrix m;
		
		float geometryVectorX = {normalizazedCoordinate.at(0).getX(), normalizazedCoordinate.at(1).getX(), 
			normalizazedCoordinate.at(2).getX(), normalizazedCoordinate.at(3).getX()};

		float geometryVectorY = {normalizazedCoordinate.at(0).getY(), normalizazedCoordinate.at(1).getY(), 
			normalizazedCoordinate.at(2).getY(), normalizazedCoordinate.at(3).getY()};

		float geometryVectorZ = {0, 0, 0, 0};

		float resultX[4] = {0, 0, 0, 0};
		float resultY[4] = {0, 0, 0, 0};
		float resultZ[4] = {0, 0, 0, 0};


		m.multiplyHermiteToGeometryVector(geometryVectorX, resultX);
		m.multiplyHermiteToGeometryVector(geometryVectorY, resultY);
		m.multiplyHermiteToGeometryVector(geometryVectorZ, resultZ);

		float x_inicial, y_inicial, z_final;
		float x_final, y_final, z_final;

		float matrixT[4] = {3.0 * t * t, 2.0 * t, 1.0, 0.0};

		for (int i = 0; i < 4; i++) {
			x_inicial = matrixT[i] * resultX[i];
			y_inicial = matrixT[i] * resultY[i];
		}		

		for (float t = 0.0; 0.0 < 1.1; t = t + 0.1) {
			matrixT[4] = {3.0 * t * t, 2.0 * t, 1.0, 0.0};

			for (int i = 0; i < 4; i++) {
				x_final = matrixT[i] * resultX[i];
				y_final = matrixT[i] * resultY[i];
				// por enquanto nao precisa
				//z = matrixT[i] * resultZ[i];				

				cairo_move_to(cr, x_inicial, y_inicial);
				cairo_line_to(cr, x_final, y_final);
				cairo_stroke(cr);

				x_inicial = x_final;
				y_inicial = y_final;
			}

		}

	}



};

#endif