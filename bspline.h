#ifndef _BSPLINE_H_
#define _BSPLINE_H_

class BSpline : public Object {
	
	public:

		BSpline(char* nome, vector<Coordenada*> coordenadas, vector<Coordenada*> userPoints) : Object(nome, coordenadas) {
			this->userPoints = userPoints;
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

			Matrix m;

			float coeficienteX[4], coeficienteY[4], coeficienteZ[4];
			float resultX[4], resultY[4];
			float pontosFwdX[4], pontosFwdY[4];

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
				
				m.multiplyBSplineToGeometryVector(coeficienteX, resultX);
				m.multiplyBSplineToGeometryVector(coeficienteY, resultY);
				//m.multiplyBSplineToGeometryVector(coeficienteZ, resultZ);

				pontosFwdX[0] = 0;
				pontosFwdX[1] = 0;
				pontosFwdX[2] = 0;
				pontosFwdX[3] = 0;
				
				pontosFwdY[0] = 0;
				pontosFwdY[1] = 0;
				pontosFwdY[2] = 0;
				pontosFwdY[3] = 0;

				m.multiplyTetaMatrixBSplineToGeometryVector(matrizTeta, resultX, pontosFwdX);
				m.multiplyTetaMatrixBSplineToGeometryVector(matrizTeta, resultY, pontosFwdY);

				desenharCurvaFwdDiff(pontosFwdX, pontosFwdY);

			}

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

	void desenharCurvaFwdDiff(float pontosFwdX[4], float pontosFwdY[4]) {
		float xOld = pontosFwdX[0];
		float yOld = pontosFwdY[0];

		// printf("%f, %f, %f, %f\n", pontosFwdX[0], pontosFwdX[1], pontosFwdX[2], pontosFwdX[3]);
		// printf("%f, %f, %f, %f\n", pontosFwdY[0], pontosFwdY[1], pontosFwdY[2], pontosFwdY[3]);

		for (int i = 0; i <= userPoints.size(); i++) {
			pontosFwdX[0] += pontosFwdX[1];
			pontosFwdX[1] += pontosFwdX[2];
			pontosFwdX[2] += pontosFwdX[3];

			pontosFwdY[0] += pontosFwdY[1];
			pontosFwdY[1] += pontosFwdY[2];
			pontosFwdY[2] += pontosFwdY[3];

			// adicionar no atributo "coordenadas"			

			printf("%f, %f, %f, %f\n", pontosFwdX[0], pontosFwdX[1], pontosFwdX[2], pontosFwdX[3]);
			printf("%f, %f, %f, %f\n", pontosFwdY[0], pontosFwdY[1], pontosFwdY[2], pontosFwdY[3]);

			xOld = pontosFwdX[0];
			yOld = pontosFwdY[0];			
		}


	}

	void clipping (Window window, Viewport viewport) {
	}

	private:
		std::vector<Coordenada*> userPoints;
		std::vector<Line*> auxLines;
		float matrizTeta[4][4];

};

#endif