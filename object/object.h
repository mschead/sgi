#include <vector>
#include "../coordenada.h"
#include "../tipo.h"

using namespace std;

class Object {

public:
	Object(char* nome, Tipo tipo, vector<Coordenada*> coordenadas) {
		this->nome = nome;
		this->tipo = tipo;
		this->coordenadas = coordenadas;
	}

	vector<Coordenada*> getPoints() {
		return coordenadas;
	}

	// virtual void draw() = 0;

private:
	char* nome;
	Tipo tipo;
	vector<Coordenada*> coordenadas;
	
};