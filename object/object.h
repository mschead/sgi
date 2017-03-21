#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "../coordenada.h"

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

protected:
	char* nome;
	vector<Coordenada*> coordenadas;
	
};

#endif