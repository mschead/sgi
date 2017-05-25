#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <vector>
#include "object.h"

using namespace std;

class Object3D : public Object {

public:
	Object3D(char* nome, vector<Line*> lines) : Object(nome) {
		this->nome = nome;
		this->lines = lines;
		// printf("%s\n\n", "Vou por as coordenadas");
		this->coordenadas.push_back(lines.at(0)->getPoints().at(0)); //Vetor coordenadas inicializa vazio, logo qualquer coordenada eh uma coordenada nova, aqui adiciona a coordenada inicial da primeira reta
		this->coordenadas.push_back(lines.at(0)->getPoints().at(1)); //Aqui adiciona coordenada final da primeira reta

		// printf("%s\n\n", "Coloquei as iniciais, iniciar verificacao de coordenada repetida");
		// printf("%u\n\n", lines.size());
		for( int i = 2; i < lines.size(); i++){
			// printf("%u\n\n", i);
			Coordenada* coordenada1 = lines.at(i)->getPoints().at(0); // Pega primeira coordenada da reta
			Coordenada* coordenada2 = lines.at(i)->getPoints().at(1); // Pega segunda coordenada da reta
			bool adicionarCoordenada1 = true;
			bool adicionarCoordenada2 = true;

				for( int j = 0; j<coordenadas.size(); j++){
					if ( coordenada1->getX() == coordenadas.at(j)->getX() && coordenada1->getY() == coordenadas.at(j)->getY() && coordenada1->getZ() == coordenadas.at(j)->getZ()){
						//marca para nao adicionar a coordenada1
						adicionarCoordenada1 = false;
					}
					if ( coordenada2->getX() == coordenadas.at(j)->getX() && coordenada2->getY() == coordenadas.at(j)->getY() && coordenada1->getZ() == coordenadas.at(j)->getZ()){
						//marca para nao adicionar a coordenada2
						adicionarCoordenada2 = false;
					}
				}
			if(adicionarCoordenada1){
			coordenadas.push_back(coordenada1);
			// printf("%s\n\n", "coloquei uma coordenada");
			}
			if(adicionarCoordenada2){
			coordenadas.push_back(coordenada2);
			// printf("%s\n\n", "coloquei outra coordenada");
			}
		}
		
		for( int i = 0; i < lines.size(); i++){
				// printf("%u\n\n", i);
				int auxiliarDeCoordenadaUnica1 = -1;
				int auxiliarDeCoordenadaUnica2 = -1;
				bool atualizarCoordenada1 = false;
				bool atualizarCoordenada2 = false;
			
				for( int j = 0; j<coordenadas.size(); j++){
					if ( lines.at(i)->getPoints().at(0)->getX() == coordenadas.at(j)->getX() && lines.at(i)->getPoints().at(0)->getY() == coordenadas.at(j)->getY() && lines.at(i)->getPoints().at(0)->getZ() == coordenadas.at(j)->getZ()){
						printf("%s\n", "atualizar coordenada1");
						printf("%f, %f, %f = %f, %f, %f\n\n", lines.at(i)->getPoints().at(0)->getX(),lines.at(i)->getPoints().at(0)->getY(),lines.at(i)->getPoints().at(0)->getZ(),coordenadas.at(j)->getX(),coordenadas.at(j)->getY(),coordenadas.at(j)->getZ());
						atualizarCoordenada1 = true;
						auxiliarDeCoordenadaUnica1 = j;
						}
					if ( lines.at(i)->getPoints().at(1)->getX() == coordenadas.at(j)->getX() && lines.at(i)->getPoints().at(1)->getY() == coordenadas.at(j)->getY() && lines.at(i)->getPoints().at(1)->getZ() == coordenadas.at(j)->getZ()){
						printf("%s\n\n", "atualizar coordenada2");
						printf("%f, %f, %f = %f, %f, %f\n\n", lines.at(i)->getPoints().at(1)->getX(),lines.at(i)->getPoints().at(1)->getY(),lines.at(i)->getPoints().at(1)->getZ(),coordenadas.at(j)->getX(),coordenadas.at(j)->getY(),coordenadas.at(j)->getZ());
						atualizarCoordenada2 = true;
						auxiliarDeCoordenadaUnica2 = j;
						}
					}
				vector<Coordenada*> points;
				points.clear();
				if(atualizarCoordenada1){
						printf("%f,%f,%f\n\n", coordenadas.at(auxiliarDeCoordenadaUnica1)->getX(),coordenadas.at(auxiliarDeCoordenadaUnica1)->getY(), coordenadas.at(auxiliarDeCoordenadaUnica1)->getZ());
      						points.push_back(coordenadas.at(auxiliarDeCoordenadaUnica1));
					}else{
						points.push_back(lines.at(i)->getPoints().at(0));					
					}
				if(atualizarCoordenada2){
      						points.push_back(coordenadas.at(auxiliarDeCoordenadaUnica2));
					}else{
						points.push_back(lines.at(i)->getPoints().at(1));					
					}
				lines.at(i) = new Line("", points);
				}

		// printf("%s\n\n", "tamanho vetor coordenadas");
		for( int i = 0; i < lines.size(); i++){
			printf("%s\n", "Pares de coordenadas de cada aresta");
			printf("%f, %f, %f\n", lines.at(i)->getPoints().at(0)->getX(), lines.at(i)->getPoints().at(0)->getY(), lines.at(i)->getPoints().at(0)->getZ());
			printf("%f, %f, %f\n\n", lines.at(i)->getPoints().at(1)->getX(), lines.at(i)->getPoints().at(1)->getY(), lines.at(i)->getPoints().at(1)->getZ());

		}
		printf("%u\n\n", coordenadas.size());
		// for(int k = 0; k < coordenadas.size(); k++){ // Printa os " x "  para verificar valores
		// 	printf("\n%f", coordenadas.at(k)->getX());
		// }
	}

	void clipping (Window window, Viewport viewport) {
		//clipping feito pelas retas
	}

	void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
		normalizedCoordinates.clear();
		auxLines.clear();

		for (int i = 0; i < lines.size(); i++) {

		    lines.at(i)->draw(viewport, window, cr, clippingType);
		    /*vector<Coordenada*> points;
		    points.push_back(lines.at(i)->getPoints().at(0));
		    points.push_back(lines.at(i)->getPoints().at(1));
		    char* emptyName = "";
		    Line* line = new Line(emptyName, points);

		    auxLines.push_back(line);
		    line->draw(viewport, window, cr, clippingType);*/
			// printf("(%f, %f) - (%f, %f)\n", normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY(), 
			// 	normalizedCoordinates.at(i + 1)->getX(), normalizedCoordinates.at(i + 1)->getY());
		}
	}

	~Object3D() {
		delete nome;
		lines.clear();
		coordenadas.clear();
		normalizedCoordinates.clear();
	}

protected:
	vector<Line*> lines;
	std::vector<Line*> auxLines;	
};

#endif
