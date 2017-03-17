#include <list>
#include "coordenada.h"
#include "tipo.h"

using namespace std;

class FormaGeometrica {

public:
	FormaGeometrica(char* nome, Tipo tipo, list<Coordenada> coordenadas) {
		this->nome = nome;
		this->tipo = tipo;
		this->coordenadas = coordenadas;
	}

private:
	char* nome;
	Tipo tipo;
	list<Coordenada> coordenadas;
	
};