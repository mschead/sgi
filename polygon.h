#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "object.h"
#define Z_STUB 0

class Polygon : public Object{

private:
	std::vector<Coordenada*> coordenadaAuxiliar;
public:

	Polygon(const char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void clipping(Window window, Viewport viewport) {
		printf("%s\n\n", "Entrei no clipping");
		vector<Coordenada*> clippingPolygon;
		vector<Coordenada*> subjectPolygon;
		vector<Coordenada*> intersection;
		vector<Coordenada*> reverseIntersection;

		normalizedCoordinates.push_back(new Coordenada(normalizedCoordinates.at(0)->getX(),normalizedCoordinates.at(0)->getY(), Z_STUB));
		
		//Identificar interseccoes
		for( int i =0; i<normalizedCoordinates.size()-1; i++){
			if(normalizedCoordinates.at(i)->getX() >= -0.9 && normalizedCoordinates.at(i)->getX() <= 0.9 && normalizedCoordinates.at(i)->getY() >= -0.9 && normalizedCoordinates.at(i)->getY() <= 0.9){
			//Vertice atual dentro da window
			printf("vertice atual dentro da window: %f  %f\n", normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY());
				if(normalizedCoordinates.at(i+1)->getX() >= -0.9 && normalizedCoordinates.at(i+1)->getX() <= 0.9 && normalizedCoordinates.at(i+1)->getY() >= -0.9 && normalizedCoordinates.at(i+1)->getY() <= 0.9){
			//Vertice seguinte dentro da window
			printf("vertice seguinte dentro da window: %f  %f\n\n", normalizedCoordinates.at(i+1)->getX(), normalizedCoordinates.at(i+1)->getY());
				}else{
			//Vertice seguinte fora da window
			printf("vertice seguinte fora da window\n\n");
				Coordenada* coordenadaPosterior = new Coordenada(normalizedCoordinates.at(i+1)->getX(),normalizedCoordinates.at(i+1)->getY(), Z_STUB);
				clippingReta(normalizedCoordinates.at(i), coordenadaPosterior);
				intersection.push_back(coordenadaPosterior);
				printf("%s\n\n", "interseccao calculada, coordenada posterior adicionada ao vetor de interseccoes");
				}
			}else{
			// Se nao estiver dentro da window verificar se o proximo pronto esta dentro
			printf("vertice atual fora da window: %f  %f\n", normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY());
				if(normalizedCoordinates.at(i+1)->getX() >= -0.9 && normalizedCoordinates.at(i+1)->getX() <= 0.9 && normalizedCoordinates.at(i+1)->getY() >= -0.9 && normalizedCoordinates.at(i+1)->getY() <= 0.9){
			// Proximo vertice dentro da window, calcular interseccao da coordenada anterior
			printf("vertice seguinte dentro da window: %f  %f\n", normalizedCoordinates.at(i+1)->getX(), normalizedCoordinates.at(i+1)->getY());
			Coordenada* coordenadaAnterior = new Coordenada(normalizedCoordinates.at(i)->getX(),normalizedCoordinates.at(i)->getY(), Z_STUB);
			clippingReta(coordenadaAnterior, normalizedCoordinates.at(i+1));
			intersection.push_back(coordenadaAnterior);
			printf("%s\n\n", "interseccao calculada, coordenada anterior adicionada ao vetor de interseccoes");
				}else{
				// Proximo vertice fora da window, calcular se existe interseccao
				printf("vertice seguinte fora da window: %f  %f\n", normalizedCoordinates.at(i+1)->getX(), normalizedCoordinates.at(i+1)->getY());
				
				}
			}
		}
//		printf("Numero total de interseccoes: %u\n", intersection.size());
		int posicaoAtualDaInterseccao = 0;
		
		//Adicionar as interseccoes para o vetor resultante
		for( int i =0; i<normalizedCoordinates.size()-1; i++){
			if(normalizedCoordinates.at(i)->getX() >= -0.9 && normalizedCoordinates.at(i)->getX() <= 0.9 && normalizedCoordinates.at(i)->getY() >= -0.9 && normalizedCoordinates.at(i)->getY() <= 0.9){
			//Vertice atual dentro da window e adicionado no clippingPolygon
			printf("vertice atual dentro e adicionado no clippingPolygon: %f  %f\n", normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY());
			Coordenada* coordenadaAtual = new Coordenada(normalizedCoordinates.at(i)->getX(),normalizedCoordinates.at(i)->getY(), Z_STUB);
			clippingPolygon.push_back(coordenadaAtual);
				if(normalizedCoordinates.at(i+1)->getX() >= -0.9 && normalizedCoordinates.at(i+1)->getX() <= 0.9 && normalizedCoordinates.at(i+1)->getY() >= -0.9 && normalizedCoordinates.at(i+1)->getY() <= 0.9){
			//Vertice seguinte dentro da window
			printf("vertice seguinte dentro da window, nada a fazer\n");
				}else{
			//Vertice seguinte fora da window
			printf("vertice seguinte fora da window, adicionar interseccao\n\n");
			Coordenada* coordenadaAtual = new Coordenada(intersection.at(posicaoAtualDaInterseccao)->getX(),intersection.at(posicaoAtualDaInterseccao)->getY(), Z_STUB);
			clippingPolygon.push_back(coordenadaAtual);
			posicaoAtualDaInterseccao++;
				}
			}else{
			// Se nao estiver dentro da window verificar se o proximo pronto esta dentro
			printf("vertice atual fora da window: %f  %f\n", normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY());
				if(normalizedCoordinates.at(i+1)->getX() >= -0.9 && normalizedCoordinates.at(i+1)->getX() <= 0.9 && normalizedCoordinates.at(i+1)->getY() >= -0.9 && normalizedCoordinates.at(i+1)->getY() <= 0.9){
			// Proximo vertice dentro da window, calcular interseccao da coordenada anterior
			printf("vertice seguinte dentro da window, adiciona ponto: %f  %f\n", normalizedCoordinates.at(i+1)->getX(), normalizedCoordinates.at(i+1)->getY());
			Coordenada* coordenadaAtual = new Coordenada(intersection.at(posicaoAtualDaInterseccao)->getX(),intersection.at(posicaoAtualDaInterseccao)->getY(), Z_STUB);
			clippingPolygon.push_back(coordenadaAtual);
			printf("vertice seguinte fora da window, adicionar interseccao \n\n");
			posicaoAtualDaInterseccao++;
				}else{
				// Proximo vertice fora da window, calcular se existe interseccao
				printf("vertice seguinte fora da window TRATAR ISSO: %f  %f\n", normalizedCoordinates.at(i+1)->getX(), normalizedCoordinates.at(i+1)->getY());
				}
			}
		}
			for( int i=0; i<clippingPolygon.size();i++){
			printf("\nCoordenada numero %u x: %f y: %f\n", i+1,clippingPolygon.at(i)->getX(), clippingPolygon.at(i)->getY());
		}
		normalizedCoordinates = clippingPolygon;
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

		for(int i = 0; i< normalizedCoordinates.size(); i++){
		coordenadaAuxiliar.push_back(new Coordenada (normalizedCoordinates.at(i)->getX(), normalizedCoordinates.at(i)->getY(), Z_STUB));
		}

		clipping(window, viewport);

		printf("Setei o auxiliar \n\n");
		
		//Primeira iteracao
		if(normalizedCoordinates.size() > 0){

		normalizedCoordinates.push_back(normalizedCoordinates.at(0));

		float x_inicial, y_inicial, x_final, y_final;

		x_inicial = normalizedCoordinates.at(0)->getX();			
		y_inicial = normalizedCoordinates.at(0)->getY();

			
		x_final = normalizedCoordinates.at(1)->getX();
		y_final = normalizedCoordinates.at(1)->getY();
		bool anteriorDentro = false;
		bool atualDentro = false;
		bool proximoDentro = false;

			for(int i = 0; i< coordenadaAuxiliar.size(); i++){
				if(x_inicial == coordenadaAuxiliar.at(i)->getX() && y_inicial == coordenadaAuxiliar.at(i)->getY()){
			printf("comecou dentro \n\n");
			anteriorDentro = true;
				}
			}

			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());
			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
			cairo_stroke(cr);

		for(int n = 1; n < normalizedCoordinates.size()-1; n++){
			x_inicial = normalizedCoordinates.at(n)->getX();			
			y_inicial = normalizedCoordinates.at(n)->getY();

			for(int i = 0; i< coordenadaAuxiliar.size(); i++){
				if(normalizedCoordinates.at(n)->getX() == coordenadaAuxiliar.at(i)->getX() && normalizedCoordinates.at(n)->getY() == coordenadaAuxiliar.at(i)->getY()){
			printf("Atual dentro\n\n");
			atualDentro = true;
			i = coordenadaAuxiliar.size();
				}else{
				atualDentro = false;				
				}
			}
			
			x_final = normalizedCoordinates.at(n+1)->getX();
			y_final = normalizedCoordinates.at(n+1)->getY();

			for(int i = 0; i< coordenadaAuxiliar.size(); i++){
				if(normalizedCoordinates.at(n+1)->getX() == coordenadaAuxiliar.at(i)->getX() && normalizedCoordinates.at(n+1)->getY() == coordenadaAuxiliar.at(i)->getY()){
			printf("Proximo dentro\n\n");
			proximoDentro = true;
			i = coordenadaAuxiliar.size();
				}else{
				proximoDentro = false;				
				}
			}

			for(int i = 0; i< coordenadaAuxiliar.size(); i++){
				if(normalizedCoordinates.at(n-1)->getX() == coordenadaAuxiliar.at(i)->getX() && normalizedCoordinates.at(n-1)->getY() == coordenadaAuxiliar.at(i)->getY()){
			printf("Anterior dentro, desenhar\n\n");
			anteriorDentro = true;
			i = coordenadaAuxiliar.size();
				}else{
				anteriorDentro = false;				
				}
			}

			if(anteriorDentro&&atualDentro){
			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
			cairo_stroke(cr);
			}

			if(atualDentro){
			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
			cairo_stroke(cr);
			}

			if(proximoDentro){
			x_inicial = viewport.obterXdaViewport(x_inicial, window.getXmin(), window.getXmax());
			y_inicial = viewport.obterYdaViewport(y_inicial, window.getYmin(), window.getYmax());

			x_final = viewport.obterXdaViewport(x_final, window.getXmin(), window.getXmax());
			y_final = viewport.obterYdaViewport(y_final, window.getYmin(), window.getYmax());

			cairo_move_to(cr, x_inicial, y_inicial);
			cairo_line_to(cr, x_final, y_final);
			cairo_stroke(cr);
			}
		}
		}
	}


};

#endif
