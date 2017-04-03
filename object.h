#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "coordenada.h"
#include "matriz.h"

using namespace std;

class Object {

public:
	Object(char* nome, vector<Coordenada*> coordenadas) {
		this->nome = nome;
		this->coordenadas = coordenadas;
	}

	char* getName() {
		return nome;
	}

	vector<Coordenada*> getPoints() {
		return coordenadas;
	}

	virtual void draw(Viewport viewport, Window window, cairo_t *cr) = 0;

	Coordenada pontoMedio() {
		int x = 0;
		int y = 0;

		for (Coordenada* coordenada : coordenadas) {
			x += coordenada->getX();
			y += coordenada->getY();
		}

		x = x / coordenadas.size();
		y = y / coordenadas.size();

		Coordenada c(x, y);
		return c;
	}

	void drawNormalized(Window window) {
		Matrix translateCenter, rotate, scale, translateBack;

		Matrix result1, result2, result3, result;

		result1.setZero();
		result2.setZero();
		result3.setZero();
		result.setZero();

		translateCenter.setTranslate(-1 * window.getXCenter(), -1 * window.getYCenter());
		rotate.setRotate(-1 * window.getAngle());
		
		float t1;
		float t2;

		if (window.getXSize() == 0 || window.getYSize() == 0) {
			t1 = 1.0;
			t2 = 1.0;
		} else {
			t1 = 1.0 / window.getXSize();
			t2 = 1.0 / window.getYSize() ;
		}

		scale.setScale(t1, t2);

		float f1, f2;

		if (window.getXCenter() == 0 || window.getYCenter() == 0) {
			f1 = 0.0;
			f2 = 0.0;
		} else {
			f1 = (-1.0 / window.getXCenter());
			f2 = (-1.0 / window.getYCenter());			
		}

		// printf("%f\n", f1);
		// printf("%f\n", f2);
		translateBack.setTranslate(f1, f2);

		// result1.printMatrix3x3(translateCenter);
		// printf("\n");
		// result1.printMatrix3x3(rotate);
		// printf("\n");
		// result1.printMatrix3x3(scale);
		// printf("\n");
		// result1.printMatrix3x3(translateBack);

		result.multiplyMatrices(translateCenter, rotate, result1);
		result.multiplyMatrices(result1, scale, result2);
		result.multiplyMatrices(result2, translateBack, result3);

		printf("\n");
		result1.printMatrix3x3(result1);
		printf("\n");
		result1.printMatrix3x3(result2);
		printf("\n");
		result1.printMatrix3x3(result3);

		for (Coordenada* coordenada : coordenadas) {
			float normalizePoint[3] = {0, 0, 0};
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};

			result.multiplyPointToMatrix(point, result3, normalizePoint);

			printf("%f\n", normalizePoint[0]);
	  		printf("%f\n", normalizePoint[1]);
			normalizedCoordinates.push_back(new Coordenada(normalizePoint[0], normalizePoint[1]));
		}

	}

	void translate(int entryX, int entryY) {
		Matrix m;
		m.setTranslate(entryX, entryY);

		for (Coordenada* coordenada : coordenadas) {
			float result[3] = {0, 0, 0};
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m.multiplyPointToMatrix(point, m, result);
			coordenada->setCoordenada(result);
		}

	}


	void scale(float entryX, float entryY) {
		Coordenada pontoMedio = this->pontoMedio();

		Matrix m1, m2, m3, result1, result2;

		m1.setTranslate(-1 * pontoMedio.getX(), -1 * pontoMedio.getY());
		m2.setScale(entryX, entryY);
		m3.setTranslate(pontoMedio.getX(), pontoMedio.getY());

		result1.setZero();
		result2.setZero();
		
		m1.multiplyMatrices(m1, m2, result1);

		m1.multiplyMatrices(result1, m3, result2);

		m1.printMatrix3x3(result2);

		for (Coordenada* coordenada : coordenadas) {
			float result3[3] = {0, 0, 0};
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m1.multiplyPointToMatrix(point, result2, result3);
			coordenada->setCoordenada(result3);
		}

	}

	void rotate(int ang) {
		Coordenada pontoMedio = this->pontoMedio();

		Matrix m1, m2, m3, result1, result2;

		m1.setTranslate(-1 * pontoMedio.getX(), -1 * pontoMedio.getY());
		m2.setRotate(ang);
		m3.setTranslate(pontoMedio.getX(), pontoMedio.getY());
		
		result1.setZero();
		result2.setZero();

		// m1.printMatrix3x3(m1);
		// m1.printMatrix3x3(m2);
		// m1.printMatrix3x3(m3);


		m1.multiplyMatrices(m1, m2, result1);

		m1.printMatrix3x3(result1);


		m1.multiplyMatrices(result1, m3, result2);

		// m1.printMatrix3x3(result2);

		for (Coordenada* coordenada : coordenadas) {
			float result3[3] = {0, 0, 0};
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m1.multiplyPointToMatrix(point, result2, result3);
			// for (int j = 0; j < 3; j++) {
			// 	printf("%f\n", result3[j]);
			// }
			coordenada->setCoordenada(result3);
		}

	}


	void rotateUsingCoordinate(int ang, float entryX, float entryY) {
		Matrix m1, m2, m3, result1, result2;

		m1.setTranslate(-1 * entryX, -1 * entryY);
		m2.setRotate(ang);
		m3.setTranslate(entryX, entryY);
		
		result1.setZero();
		result2.setZero();

		// m1.printMatrix3x3(m1);
		// m1.printMatrix3x3(m2);
		// m1.printMatrix3x3(m3);


		m1.multiplyMatrices(m1, m2, result1);

		m1.printMatrix3x3(result1);


		m1.multiplyMatrices(result1, m3, result2);

		// m1.printMatrix3x3(result2);

		for (Coordenada* coordenada : coordenadas) {
			float result3[3] = {0, 0, 0};
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m1.multiplyPointToMatrix(point, result2, result3);
			// for (int j = 0; j < 3; j++) {
			// 	printf("%f\n", result3[j]);
			// }
			coordenada->setCoordenada(result3);
		}

	}

protected:
	char* nome;
	vector<Coordenada*> coordenadas;
	vector<Coordenada*> normalizedCoordinates;
	
};

#endif