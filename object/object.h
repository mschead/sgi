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
		int transformation[3][3];
		
		transformation[0][0] = 1;
		transformation[1][0] = 0;
		transformation[2][0] = entryX;

		transformation[0][1] = 0;
    	transformation[1][1] = 1;
		transformation[2][1] = entryY;

		transformation[0][2] = 0;
		transformation[1][2] = 0;
		transformation[2][2] = 1;


		for (Coordenada* coordenada : coordenadas) {
			int point[3];
			point[0] = coordenada->getX();
			point[1] = coordenada->getY();
			point[2] = 1;
			coordenada->setCoordenada(multiplyPointToMatrix(point, transformation));
		}

		// for (Coordenada* coordenada : coordenadas) {
		// 	printf("%d\n", coordenada->getX());
		// 	printf("%d\n", coordenada->getY());
		// }

	}


	void scale(int entryX, int entryY) {
		Coordenada pontoMedio = this->pontoMedio();

		int translate[3][3];
		
		translate[0][0] = 1;
		translate[1][0] = 0;
		translate[2][0] = -1 * pontoMedio.getX();

		translate[0][1] = 0;
    	translate[1][1] = 1;
		translate[2][1] = -1 * pontoMedio.getY();

		translate[0][2] = 0;
		translate[1][2] = 0;
		translate[2][2] = 1;

		int scale[3][3];
		
		scale[0][0] = entryX;
		scale[1][0] = 0;
		scale[2][0] = 0;

		scale[0][1] = 0;
    	scale[1][1] = entryY;
		scale[2][1] = 0;

		scale[0][2] = 0;
		scale[1][2] = 0;
		scale[2][2] = 1;

		int translate2[3][3];
		
		translate2[0][0] = 1;
		translate2[1][0] = 0;
		translate2[2][0] = pontoMedio.getX();

		translate2[0][1] = 0;
    	translate2[1][1] = 1;
		translate2[2][1] = pontoMedio.getY();

		translate2[0][2] = 0;
		translate2[1][2] = 0;
		translate2[2][2] = 1;

		int result[3][3] = {(0,0,0), (0,0,0), (0,0,0)};
		int result2[3][3] = {(0,0,0), (0,0,0), (0,0,0)};

		multiplyMatrices(translate, scale, result);
		multiplyMatrices(result, translate2, result2);

		print_matrix(result2);

		for (Coordenada* coordenada : coordenadas) {
			int point[3];
			point[0] = coordenada->getX();
			point[1] = coordenada->getY();
			point[2] = 1;
			coordenada->setCoordenada(multiplyPointToMatrix(point, result2));
		}
	}


	int* multiplyPointToMatrix(int point[3], int transformation[3][3]) {
		int* result = new int[3];
		result[0] = 0;
		result[1] = 0;
		result[2] = 0;

  	for (int j = 0; j < 3; j++) {
  		for (int i = 0; i < 3; i ++) {
    		result[j] += point[i] * transformation[i][j];
  		}
  	}

  		return result;
	}

	void multiplyMatrices(int a[][3], int b[][3], int result[][3])
	{
	    int i, j, k;
	    for(i = 0; i < 3; i++)
	    {
	            for(j = 0; j < 3; j++)
	            {
	                    for(k = 0; k < 3; k++)
	                    {
	                            result[i][j] +=  a[i][k] *  b[k][j];
	                    }
	            }
	    }
	}

	void print_matrix(int a[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
            for(j = 0; j < 3; j++)
            {
                    printf("%d\t", a[i][j]);
            }
            printf("\n");
    }
 }

protected:
	char* nome;
	vector<Coordenada*> coordenadas;
	
};

#endif