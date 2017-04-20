#ifndef _BSPLINE_H_
#define _BSPLINE_H_

class BSpline : public Object {
	
	public:

		BSpline(char* nome, vector<Coordenada*> coordenadas, vector<Coordenada*> userPoints) : Object(nome, coordenadas) {
			this->userPoints = userPoints;
			float matrizTeta[4][4];
			float teta = 0.2;

			matrizTeta[0][0] = 0;
			matrizTeta[0][1] = 0;
			matrizTeta[0][2] = 0;
			matrizTeta[0][3] = 1;

			matrizTeta[1][0] = teta * teta * teta;
			matrizTeta[1][1] = teta * teta;
			matrizTeta[1][2] = teta;
			matrizTeta[1][3] = 0;

			matrizTeta[2][0] = 6.0 * teta * teta * teta;
			matrizTeta[2][1] = 2.0 * teta * teta;
			matrizTeta[2][2] = 0;
			matrizTeta[2][3] = 0;

			matrizTeta[3][0] = 6.0 * teta * teta * teta;
			matrizTeta[3][1] = 0;
			matrizTeta[3][2] = 0;
			matrizTeta[3][3] = 0;
		}

		void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
			Matrix m;

			float coeficienteX[4], coeficienteY[4], coeficienteZ[4];
			float resultX[4], resultY[4];

			for (int i = 0; i < userPoints.size() - 3; i++) {
				Coordenada *p1 = userPoints.at(i);
				Coordenada *p2 = userPoints.at(i+1);
				Coordenada *p3 = userPoints.at(i+2);
				Coordenada *p4 = userPoints.at(i+3);

				coeficienteX[0] = p1->getX();
				coeficienteX[1] = p2->getX();
				coeficienteX[2] = p3->getX();
				coeficienteX[3] = p4->getX();

				coeficienteY[0] = p1->getY();
				coeficienteY[1] = p2->getY();
				coeficienteY[2] = p3->getY();
				coeficienteY[3] = p4->getY();

				resultX[0] = 0;
				resultX[1] = 0;
				resultX[2] = 0;
				resultX[3] = 0;

				resultY[0] = 0;
				resultY[1] = 0;
				resultY[2] = 0;
				resultY[3] = 0;
				
				//resultZ[4] = {0, 0, 0, 0};
				
				m.multiplyBSplineToGeometryVector(coeficienteX, resultX);
				m.multiplyBSplineToGeometryVector(coeficienteY, resultY);
				//m.multiplyBSplineToGeometryVector(coeficienteZ, resultZ);

			}

		}


	void clipping (Window window, Viewport viewport) {
	}

	private:
		std::vector<Coordenada*> userPoints;

};

#endif