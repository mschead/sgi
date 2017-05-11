#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "object.h"
#define Z_STUB 0

class Polygon : public Object{
	
public:

	Polygon(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void clipping(Window window, Viewport viewport) {
		int n= 1;
		bool estavaDentro;
		bool comecouFora;
		vector<Coordenada*> coordenadasClippadas;
		Coordenada* coordenadaFora = new Coordenada( -10, -10, Z_STUB);
		float controleX;
		float controleY;
			if(normalizedCoordinates.at(0)->getX() <= 0.9 && normalizedCoordinates.at(0)->getX() >= -0.9 && normalizedCoordinates.at(0)->getY() <= 0.9 && normalizedCoordinates.at(0)->getY() >= -0.9){
		printf("%s\n", " inicializando com ponto dentro");		
		coordenadasClippadas.push_back(normalizedCoordinates.at(0));
		estavaDentro = true;
		comecouFora = false;
			} else {
			printf("%s\n", " inicializando com ponto fora");
			comecouFora = true;
			coordenadaFora->setX(normalizedCoordinates.at(0)->getX());
			coordenadaFora->setY(normalizedCoordinates.at(0)->getY());
			estavaDentro = false;
			}
		for( n; n < normalizedCoordinates.size(); n++){
			if(normalizedCoordinates.at(n)->getX() <= 0.9 && normalizedCoordinates.at(n)->getX() >= -0.9 && normalizedCoordinates.at(n)->getY() <= 0.9 && normalizedCoordinates.at(n)->getY() >= -0.9){
				if(estavaDentro){
				printf("%s\n", " Ponto continua dentro, nada a fazer");
				coordenadasClippadas.push_back(normalizedCoordinates.at(n));
				estavaDentro = true;				
				}else{
				printf("%s\n", " Ponto estava fora, necessario clippar");
				controleX = coordenadaFora->getX();
				controleY = coordenadaFora->getY();

				clippingReta(coordenadaFora, normalizedCoordinates.at(n));
				coordenadasClippadas.push_back(new Coordenada (coordenadaFora->getX(),coordenadaFora->getY(), Z_STUB));
				coordenadaFora->setX(controleX);
				coordenadaFora->setY(controleY);
				estavaDentro = true;
				coordenadasClippadas.push_back(normalizedCoordinates.at(n));
				}
			}else{
				coordenadaFora->setX(normalizedCoordinates.at(n)->getX());
				coordenadaFora->setY(normalizedCoordinates.at(n)->getY());
				if(estavaDentro){
				printf("%s\n", " Ponto estava dentro, necessario clippar");
				controleX = coordenadaFora->getX();
				controleY = coordenadaFora->getY();

				clippingReta(coordenadaFora, coordenadasClippadas.back());
				printf("%s\n", " Clipagem feita");
				coordenadasClippadas.push_back(new Coordenada (coordenadaFora->getX(),coordenadaFora->getY(), Z_STUB));	
				coordenadaFora->setX(controleX);
				coordenadaFora->setY(controleY);
				estavaDentro = false;
				}
			
			}
		}
		n = n-1;
		if(comecouFora && estavaDentro){
			coordenadaFora->setX(normalizedCoordinates.at(0)->getX());
			coordenadaFora->setY(normalizedCoordinates.at(0)->getY());
			clippingReta(coordenadaFora, coordenadasClippadas.back());
			coordenadasClippadas.push_back(new Coordenada (coordenadaFora->getX(),coordenadaFora->getY(), Z_STUB));
		}if(comecouFora && !estavaDentro){
			float controleX2 = normalizedCoordinates.at(n)->getX();
			float controleY2 = normalizedCoordinates.at(n)->getY();
			controleX = coordenadaFora->getX();
			controleY = coordenadaFora->getY();

			clippingReta(coordenadaFora, normalizedCoordinates.at(n));
			if(normalizedCoordinates.at(n)->getX() <= 0.9 && normalizedCoordinates.at(n)->getX() >= -0.9 && normalizedCoordinates.at(n)->getY() >= -0.9 && normalizedCoordinates.at(n)->getY() <= 0.9){
			coordenadasClippadas.push_back(new Coordenada (normalizedCoordinates.at(n)->getX(),normalizedCoordinates.at(n)->getY(), Z_STUB));
			}if(coordenadaFora->getX() <= 0.9 && coordenadaFora->getX() >= -0.9 && coordenadaFora->getY() >= -0.9 && coordenadaFora->getY() <= 0.9){
			coordenadasClippadas.push_back(new Coordenada (coordenadaFora->getX(),coordenadaFora->getY(), Z_STUB));
			}
			
			normalizedCoordinates.at(n)->setX(controleX2);
			normalizedCoordinates.at(n)->setY(controleY2);
			coordenadaFora->setX(controleX);
			coordenadaFora->setY(controleY);
			estavaDentro = true;
			coordenadasClippadas.push_back(normalizedCoordinates.at(n));
		}if(!comecouFora && !estavaDentro){
				controleX = coordenadaFora->getX();
				controleY = coordenadaFora->getY();

				clippingReta(coordenadaFora, normalizedCoordinates.at(n));
				coordenadasClippadas.push_back(new Coordenada (coordenadaFora->getX(),coordenadaFora->getY(), Z_STUB));
				coordenadaFora->setX(controleX);
				coordenadaFora->setY(controleY);
				estavaDentro = true;
		}
		printf("%s\n", "Numero de vertices");
		// printf("%u\n", coordenadasClippadas.size());
		normalizedCoordinates = coordenadasClippadas;
	}


	void clippingReta (Coordenada* coordenadaAnterior, Coordenada* coordenadaPosterior) {
		float coeficienteAngularX;
		float coeficienteAngularY;

		// w topo, w fundo, w direita, w esquerda
		int rc1[4] = {0, 0, 0, 0};
		int rc2[4] = {0, 0, 0, 0};

		// Primeiro ponto
		Coordenada* c1 = coordenadaAnterior;
		
		rc1[0] = c1->getY() <= 0.9 ? 0 : 1;
		rc1[1] = c1->getY() >= -0.9 ? 0 : 1;
		rc1[2] = c1->getX() <= 0.9 ? 0 : 1;
		rc1[3] = c1->getX() >= -0.9 ? 0 : 1;

		// Segundo ponto
		Coordenada* c2 = coordenadaPosterior;

		rc2[0] = c2->getY() <= 0.9 ? 0 : 1;
		rc2[1] = c2->getY() >= -0.9 ? 0 : 1;
		rc2[2] = c2->getX() <= 0.9 ? 0 : 1;
		rc2[3] = c2->getX() >= -0.9 ? 0 : 1;

		// 1 0 1 0
		// 0 0 1 0


		if(c1->getY() == c2->getY() || c1->getX() == c2->getX()){
		coeficienteAngularX =0;
		coeficienteAngularY= 0;
		} else {
		coeficienteAngularX = (c1->getY() - c2->getY())/(c1->getX() - c2->getX());
		coeficienteAngularY = 1/coeficienteAngularX;
		}

		bool rcComparer = rc1[0] && rc2[0] || rc1[1] && rc2[1] || rc1[2] && rc2[2] || rc1[3] && rc2[3];
		int sum = rc1[0] + rc1[1] + rc1[2] + rc1[3] + rc2[0] + rc2[1] + rc2[2] + rc2[3]; 

		if (!sum) {
		} else if (!rcComparer) {

			if( rc1[0] == 1 || rc2[0] == 1 ){
				float topX;
				topX = coeficienteAngularY * (0.9 - c1->getY()) + c1->getX();
				
				if(topX <= 0.9 && topX >= -0.9){
					if (rc1[0] == 1){
					c1->setY(0.9);
					c1->setX(topX);
					}if (rc2[0] == 1){
					c2->setY(0.9);
					c2->setX(topX);
					}
				}
			}

			if( rc1[1] == 1 || rc2[1] == 1){
				float bottonX;
				
				bottonX = coeficienteAngularY * (-0.9 - c1->getY()) + c1->getX();
				
				if(bottonX <= 0.9 && bottonX >= -0.9){
					if (rc1[1] == 1){
					c1->setY(-0.9);
					c1->setX(bottonX);
					}if (rc2[1] == 1){
					c2->setY(-0.9);
					c2->setX(bottonX);
					}
				}
			}

			if( rc1[2] == 1 || rc2[2] == 1 ){
				float rightY;
				
				rightY = coeficienteAngularX * (0.9 - c1->getX()) + c1->getY();
				
				if(rightY <= 0.9 && rightY >= -0.9){
				if (rc1[2] == 1){
					c1->setY(rightY);
					c1->setX(0.9);
					}if (rc2[2] == 1){
					c2->setY(rightY);
					c2->setX(0.9);
					}
				}
			}

			if( rc1[3] == 1 || rc2[3] == 1){
				float leftY;

				leftY = coeficienteAngularX * (-0.9 - c1->getX()) + c1->getY();
				
				if(leftY <= 0.9 && leftY >= -0.9){
					if (rc1[3] == 1){
					c1->setY(leftY);
					c1->setX(-0.9);
					}if (rc2[3] == 1){
					c2->setY(leftY);
					c2->setX(-0.9);
					}
				}
			}
		}				
		else {

		}

	}
	
	void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
		normalizedCoordinates.clear();
		drawNormalized(window);
		clipping(window, viewport);

		float x_inicial, y_inicial, x_final, y_final;
		float x_init = normalizedCoordinates.front()->getX();
		float y_init = normalizedCoordinates.front()->getY();

		for(int n = 0; n < normalizedCoordinates.size(); n++){
			x_inicial = normalizedCoordinates.at(n)->getX();			
			y_inicial = normalizedCoordinates.at(n)->getY();
			
			if(n == normalizedCoordinates.size() - 1){
				x_final = x_init;
				y_final = y_init;
			} else {
				x_final = normalizedCoordinates.at(n+1)->getX();
				y_final = normalizedCoordinates.at(n+1)->getY();
			}


			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
			cairo_stroke(cr);
		}
	}


};

#endif
