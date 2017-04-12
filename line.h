#ifndef _LINE_H_
#define _LINE_H_

#include "object.h"

using namespace std;

class Line : public Object {
	
public:

	Line(char* nome, vector<Coordenada*> coordenadas) : Object(nome, coordenadas) {
	}

	void clipping (Window window, Viewport viewport) {

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

		bool rcComparer = rc1[0] && rc2[0] || rc1[1] && rc2[1] || rc1[2] && rc2[2] || rc1[3] && rc2[3];
		int sum = rc1[0] + rc1[1] + rc1[2] + rc1[3] + rc2[0] + rc2[1] + rc2[2] + rc2[3]; 

		if (!sum) {
			printf("%s\n", "TUDO DENTRO");
		} else if (!rcComparer)
			printf("%s\n", "CALCULAR PARCIALMENTE");

			

			
		else {
			printf("%s\n", "TA FORA");
		}




	}


	bool clipping2(Window window, Viewport viewport) {
		Coordenada* pontoR1 = normalizedCoordinates.at(0);
		Coordenada* pontoR2 = normalizedCoordinates.at(1);

		float p2 = pontoR2->getX() - pontoR1->getX();
		float p1 = -1.0 * p2;
		float p4 = pontoR2->getY() - pontoR1->getY();
		float p3 = -1.0 * p4;

		float q1 = pontoR1->getX() + 0.9; // - xwmin
		float q2 = 0.9 - pontoR1->getX();
		float q3 = pontoR1->getY() + 0.9; // - ymin
		float q4 = 0.9 - pontoR1->getY();


		float r1_teta1, r2_teta1;
		float r1_teta2, r2_teta2; 

		if (p1 < 0.0) {
			r1_teta1 = q1 / p1;
			r2_teta1 = q3 / p3;

			r1_teta2 = q2 / p2;
			r2_teta2 = q4 / p4;
		} else {
			r1_teta2 = q1 / p1;
			r2_teta2 = q3 / p3;

			r1_teta1 = q2 / p2;
			r2_teta1 = q4 / p4;
		}


		
		// printf("%f, ", r1);
		// printf("%f\n", r3);

		float teta1 = fmax(0.0, fmax(r1_teta1, r2_teta1));
		float teta2 = fmin(1.0, fmin(r1_teta2, r2_teta2));

		// printf("%s\n", "verificar teta");
		// printf("%f, ", teta1);
		// printf("%f\n", teta2);

		if (teta1 > teta2) {
			return false;
		}

		// printf("%s\n", "reta clipada");
		if (teta1 != 0) {
			pontoR1->setX(pontoR1->getX() + teta1 * p2);
			pontoR1->setY(pontoR1->getY() + teta1 * p4);
		}


		if (teta2 != 1) {
			pontoR2->setX(pontoR1->getX() + teta2 * p2);
			pontoR2->setY(pontoR1->getY() + teta2 * p4);
		}

		return true;
	}


	void draw(Viewport viewport, Window window, cairo_t *cr) {
	  normalizedCoordinates.clear();
	  drawNormalized(window);
	  clipping2(window, viewport);

	  // for (Coordenada* c : normalizedCoordinates) {
	  // 	printf("%f\n", c->getX());
	  // 	printf("%f\n", c->getY());
	  // }

	  // printf("%f\n", normalizedCoordinates.at(0)->getX());
	  // printf("%f\n", normalizedCoordinates.at(0)->getY());

  	//   printf("%f\n", normalizedCoordinates.at(1)->getX());
	  // printf("%f\n", normalizedCoordinates.at(1)->getY());

	  // if (!clipping2(window, viewport)) {
		  int x1 = viewport.obterXdaViewport(normalizedCoordinates.at(0)->getX(), window.getXmin(), window.getXmax());
		  int y1 = viewport.obterYdaViewport(normalizedCoordinates.at(0)->getY(), window.getYmin(), window.getYmax());

		  int x2 = viewport.obterXdaViewport(normalizedCoordinates.at(1)->getX(), window.getXmin(), window.getXmax());
		  int y2 = viewport.obterYdaViewport(normalizedCoordinates.at(1)->getY(), window.getYmin(), window.getYmax());

		  printf("PONTOS COM VIEWPORT: \n");
		  printf("%d, ", x1);
		  printf("%d\n", y1);

	  	  printf("%d, ", x2);
		  printf("%d\n", y2);


		  cairo_move_to(cr, x1, y1);
		  cairo_line_to(cr, x2, y2);
		  cairo_stroke(cr);	  	
	  // }


	}

};

#endif