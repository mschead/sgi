#ifndef _LINE_H_
#define _LINE_H_

#include "object.h"

class Line : public Object {
	
public:

	Line(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void clipping (Window window, Viewport viewport) {
		float coeficienteAngularX;
		float coeficienteAngularY;

		// w topo, w fundo, w direita, w esquerda
		int rc1[4] = {0, 0, 0, 0};
		int rc2[4] = {0, 0, 0, 0};

		// Primeiro ponto
		Coordenada* c1 = this->normalizedCoordinates.at(0);
		
		rc1[0] = c1->getY() <= 1 ? 0 : 1;
		rc1[1] = c1->getY() >= -1 ? 0 : 1;
		rc1[2] = c1->getX() <= 1 ? 0 : 1;
		rc1[3] = c1->getX() >= -1 ? 0 : 1;

		// Segundo ponto
		Coordenada* c2 = this->normalizedCoordinates.at(1);

		rc2[0] = c2->getY() <= 1 ? 0 : 1;
		rc2[1] = c2->getY() >= -1 ? 0 : 1;
		rc2[2] = c2->getX() <= 1 ? 0 : 1;
		rc2[3] = c2->getX() >= -1 ? 0 : 1;

		// 1 0 1 0
		// 0 0 1 0



		coeficienteAngularX = (c1->getY() - c2->getY())/(c1->getX() - c2->getX());
		coeficienteAngularY = 1/coeficienteAngularX;

		printf("\n%s\n", "Coeficiente angular:");
		printf("%f\n\n", coeficienteAngularX);

		bool rcComparer = rc1[0] && rc2[0] || rc1[1] && rc2[1] || rc1[2] && rc2[2] || rc1[3] && rc2[3];
		int sum = rc1[0] + rc1[1] + rc1[2] + rc1[3] + rc2[0] + rc2[1] + rc2[2] + rc2[3]; 

		if (!sum) {
			printf("%s\n", "TUDO DENTRO");
		} else if (!rcComparer) {
			printf("%s\n", "CALCULAR PARCIALMENTE");

			if( rc1[0] == 1 || rc2[0] == 1 ){
				printf("%s\n", "CALCULAR X QUE ALCANCA TOPO");
				float topX;

				printf("%s\n", "X em relacao a window");
				printf("%f\n", c1->getX());
				printf("%s\n", "Y em relacao a window");
				printf("%f\n", c1->getY());
				
				topX = coeficienteAngularY * (1 - c1->getY()) + c1->getX();
				
				if(topX <= 1 && topX >= -1){
				c2->setY(1);
				c2->setX(topX);
				}
				printf("%s\n", "X de interseccao calculado");
				printf("%f\n", topX);
			}

			if( rc1[1] == 1 || rc2[1] == 1){
				printf("%s\n", "CALCULAR X QUE ALCANCA BASE");
				float bottonX;

				printf("%s\n", "X em relacao a window");
				printf("%f\n", c1->getX());
				printf("%s\n", "Y em relacao a window");
				printf("%f\n", c1->getY());
				
				bottonX = coeficienteAngularY * (-1 - c1->getY()) + c1->getX();
				
				if(bottonX <= 1 && bottonX >= -1){
				c1->setY(-1);
				c1->setX(bottonX);
				}
				printf("%s\n", "X de interseccao calculado");
				printf("%f\n", bottonX);
			}

			if( rc1[2] == 1 || rc2[2] == 1 ){
				printf("%s\n", "CALCULAR Y QUE ALCANCA LADO DIREITO");
				float rightY;

				printf("%s\n", "X em relacao a window");
				printf("%f\n", c1->getX());
				printf("%s\n", "Y em relacao a window");
				printf("%f\n", c1->getY());
				
				rightY = coeficienteAngularX * (1 - c1->getX()) + c1->getY();
				
				if(rightY <= 1 && rightY >= -1){
				c2->setY(rightY);
				c2->setX(1);
				}
				printf("%s\n", "Y de interseccao calculado");
				printf("%f\n", rightY);
			}

			if( rc1[3] == 1 || rc2[3] == 1){
				printf("%s\n", "CALCULAR Y QUE ALCANCA LADO ESQUERDO");
				float leftY;

				printf("%s\n", "X em relacao a window");
				printf("%f\n", c1->getX());
				printf("%s\n", "Y em relacao a window");
				printf("%f\n", c1->getY());
				
				leftY = coeficienteAngularX * (-1 - c1->getX()) + c1->getY();
				
				if(leftY <= 1 && leftY >= -1){
				c1->setY(leftY);
				c1->setX(-1);
				}
				printf("%s\n", "Y de interseccao calculado");
				printf("%f\n", leftY);

			}
		}				
		else {
			printf("%s\n", "TA FORA");
		}




	}

	void draw(Viewport viewport, Window window, cairo_t *cr) {
	  normalizedCoordinates.clear();
	  drawNormalized(window);
	  clipping(window, viewport);

	  // for (Coordenada* c : normalizedCoordinates) {
	  // 	printf("%f\n", c->getX());
	  // 	printf("%f\n", c->getY());
	  // }

	  // printf("%f\n", normalizedCoordinates.at(0)->getX());
	  // printf("%f\n", normalizedCoordinates.at(0)->getY());

  	//   printf("%f\n", normalizedCoordinates.at(1)->getX());
	  // printf("%f\n", normalizedCoordinates.at(1)->getY());

	  int x1 = viewport.obterXdaViewport(normalizedCoordinates.at(0)->getX(), window.getXmin(), window.getXmax());
	  int y1 = viewport.obterYdaViewport(normalizedCoordinates.at(0)->getY(), window.getYmin(), window.getYmax());

	  int x2 = viewport.obterXdaViewport(normalizedCoordinates.at(1)->getX(), window.getXmin(), window.getXmax());
	  int y2 = viewport.obterYdaViewport(normalizedCoordinates.at(1)->getY(), window.getYmin(), window.getYmax());

	  // printf("%d\n", x1);
	  // printf("%d\n", y1);

  	  printf("%d\n", x2);
	  printf("%d\n", y2);


	  cairo_move_to(cr, x1, y1);
	  cairo_line_to(cr, x2, y2);
	  cairo_stroke(cr);
	}

};

#endif
