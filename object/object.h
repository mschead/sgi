#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "../coordenada.h"
#include "../matriz.h"

using namespace std;

class Object {

public:
	Object(char* nome, vector<Coordenada*> coordenadas) {
		this->nome = nome;
		this->coordenadas = coordenadas;
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

	void translate(int entryX, int entryY) {
		Matrix m;
		m.setTranslate(entryX, entryY);

		for (Coordenada* coordenada : coordenadas) {
			int result[3] = {0, 0, 0};
			int point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m.multiplyPointToMatrix(point, m, result);
			coordenada->setCoordenada(result);
		}

	}


	void scale(int entryX, int entryY) {
		Coordenada pontoMedio = this->pontoMedio();

		Matrix m1, m2, m3, result1, result2;

		m1.setTranslate(-1 * pontoMedio.getX(), -1 * pontoMedio.getY());
		m2.setScale(entryX, entryY);
		m3.setTranslate(pontoMedio.getX(), pontoMedio.getY());
		
		m1.multiplyMatrices(m1, m2, result1);

		m1.printMatrix3x3(result1);


		m1.multiplyMatrices(result1, m3, result2);

		m1.printMatrix3x3(result2);

		for (Coordenada* coordenada : coordenadas) {
			int result3[3] = {0, 0, 0};
			int point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m1.multiplyPointToMatrix(point, result2, result3);
			coordenada->setCoordenada(result3);
		}

	}


protected:
	char* nome;
	vector<Coordenada*> coordenadas;
	
};

#endif