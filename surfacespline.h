#ifndef _SURFACESPLINE_H_
#define _SURFACESPLINE_H_ 

#include "object.h"

class SurfaceSpline : public Object {
	
public:
	SurfaceSpline(char* nome, vector<Coordenada*> coordenadas, 
		Coordenada *p11, Coordenada *p12, Coordenada *p13, Coordenada *p14, Coordenada *p21, Coordenada *p22,Coordenada *p23,Coordenada *p24,Coordenada *p31,Coordenada *p32,Coordenada *p33,Coordenada *p34,Coordenada *p41,Coordenada *p42, Coordenada *p43, Coordenada *p44) : Object(nome, coordenadas) {	
		printf("%s\n", "entrei no construtor");
		this->p11 = p11;
		this->p12 = p12;
		this->p13 = p13;
		this->p14 = p14;

		this->p21 = p21;
		this->p22 = p22;
		this->p23 = p23;
		this->p24 = p24;

		this->p31 = p31;
		this->p32 = p32;
		this->p33 = p33;
		this->p34 = p34;

		this->p41 = p41;
		this->p42 = p42;
		this->p43 = p43;
		this->p44 = p44;

		Matrix m;

		float geometryVectorX[4][4];
		printf("\n vetor geometria %f   %f   %f   %f\n",p11->getX(), p12->getX(), p13->getX(),p14->getX());
		printf("%f   %f   %f   %f\n",p21->getX(), p22->getX(), p23->getX(),p24->getX());
		printf("%f   %f   %f   %f\n",p31->getX(), p32->getX(), p33->getX(),p34->getX());
		printf("%f   %f   %f   %f\n",p41->getX(), p42->getX(), p43->getX(),p44->getX());

		geometryVectorX[0][0] = p11->getX();
		geometryVectorX[0][1] = p12->getX();
		geometryVectorX[0][2] = p13->getX();
		geometryVectorX[0][3] = p14->getX();

		geometryVectorX[1][0] = p21->getX();
		geometryVectorX[1][1] = p22->getX();
		geometryVectorX[1][2] = p23->getX();
		geometryVectorX[1][3] = p24->getX();

		geometryVectorX[2][0] = p31->getX();
		geometryVectorX[2][1] = p32->getX();
		geometryVectorX[2][2] = p33->getX();
		geometryVectorX[2][3] = p34->getX();

		geometryVectorX[3][0] = p41->getX();
		geometryVectorX[3][1] = p42->getX();
		geometryVectorX[3][2] = p43->getX();
		geometryVectorX[3][3] = p44->getX();

		float geometryVectorY[4][4];

		geometryVectorY[0][0] = p11->getY();
		geometryVectorY[0][1] = p12->getY();
		geometryVectorY[0][2] = p13->getY();
		geometryVectorY[0][3] = p14->getY();

		geometryVectorY[1][0] = p21->getY();
		geometryVectorY[1][1] = p22->getY();
		geometryVectorY[1][2] = p23->getY();
		geometryVectorY[1][3] = p24->getY();

		geometryVectorY[2][0] = p31->getY();
		geometryVectorY[2][1] = p32->getY();
		geometryVectorY[2][2] = p33->getY();
		geometryVectorY[2][3] = p34->getY();

		geometryVectorY[3][0] = p41->getY();
		geometryVectorY[3][1] = p42->getY();
		geometryVectorY[3][2] = p43->getY();
		geometryVectorY[3][3] = p44->getY();

		float geometryVectorZ[4][4];

		geometryVectorZ[0][0] = p11->getZ();
		geometryVectorZ[0][1] = p12->getZ();
		geometryVectorZ[0][2] = p13->getZ();
		geometryVectorZ[0][3] = p14->getZ();

		geometryVectorZ[1][0] = p21->getZ();
		geometryVectorZ[1][1] = p22->getZ();
		geometryVectorZ[1][2] = p23->getZ();
		geometryVectorZ[1][3] = p24->getZ();

		geometryVectorZ[2][0] = p31->getZ();
		geometryVectorZ[2][1] = p32->getZ();
		geometryVectorZ[2][2] = p33->getZ();
		geometryVectorZ[2][3] = p34->getZ();

		geometryVectorZ[3][0] = p41->getZ();
		geometryVectorZ[3][1] = p42->getZ();
		geometryVectorZ[3][2] = p43->getZ();
		geometryVectorZ[3][3] = p44->getZ();

		printf("%s\n", "setei vetor geometria");

		float spline[4][4];

		spline[0][0] = -1.0/6.0;
		spline[0][1] = 3.0/6.0;
		spline[0][2] = -3.0/6.0;
		spline[0][3] = 1.0/6.0;

		spline[1][0] = 3.0/6.0;
		spline[1][1] = -6.0/6.0;
		spline[1][2] = 3.0/6.0;
		spline[1][3] = 0.0/6.0;

		spline[2][0] = -3.0/6.0;
		spline[2][1] = 0/6.0;
		spline[2][2] = 3.0/6.0;
		spline[2][3] = 0.0/6.0;

		spline[3][0] = 1.0/6.0;
		spline[3][1] = 4.0/6.0;
		spline[3][2] = 1.0/6.0;
		spline[3][3] = 0;

		float resultX[4][4];
		resultX[0][0] = 0;
		resultX[0][1] = 0;
		resultX[0][2] = 0;
		resultX[0][3] = 0;

		resultX[1][0] = 0;
		resultX[1][1] = 0;
		resultX[1][2] = 0;
		resultX[1][3] = 0;

		resultX[2][0] = 0;
		resultX[2][1] = 0;
		resultX[2][2] = 0;
		resultX[2][3] = 0;

		resultX[3][0] = 0;
		resultX[3][1] = 0;
		resultX[3][2] = 0;
		resultX[3][3] = 0;

		float resultY[4][4];
		resultY[0][0] = 0;
		resultY[0][1] = 0;
		resultY[0][2] = 0;
		resultY[0][3] = 0;

		resultY[1][0] = 0;
		resultY[1][1] = 0;
		resultY[1][2] = 0;
		resultY[1][3] = 0;

		resultY[2][0] = 0;
		resultY[2][1] = 0;
		resultY[2][2] = 0;
		resultY[2][3] = 0;

		resultY[3][0] = 0;
		resultY[3][1] = 0;
		resultY[3][2] = 0;
		resultY[3][3] = 0;

		float resultZ[4][4];
		resultZ[0][0] = 0;
		resultZ[0][1] = 0;
		resultZ[0][2] = 0;
		resultZ[0][3] = 0;

		resultZ[1][0] = 0;
		resultZ[1][1] = 0;
		resultZ[1][2] = 0;
		resultZ[1][3] = 0;

		resultZ[2][0] = 0;
		resultZ[2][1] = 0;
		resultZ[2][2] = 0;
		resultZ[2][3] = 0;

		resultZ[3][0] = 0;
		resultZ[3][1] = 0;
		resultZ[3][2] = 0;
		resultZ[3][3] = 0;

		printf("\n\n %f   %f   %f   %f\n", spline[0][0], spline[0][1], spline[0][2], spline[0][3]);
		printf("\n\n %f   %f   %f   %f\n", spline[1][0], spline[1][1], spline[1][2], spline[1][3]);
		printf("\n\n %f   %f   %f   %f\n", spline[2][0], spline[2][1], spline[2][2], spline[2][3]);
		printf("\n\n %f   %f   %f   %f\n", spline[3][0], spline[3][1], spline[3][2], spline[3][3]);

		printf("%s\n", "Matriz spline por geometria em X");
		
		m.multiplyMatrices4x4by4x4(spline,geometryVectorX, resultX);

		printf("%s\n", "Matriz spline por geometria em Y");
		m.multiplyMatrices4x4by4x4(spline,geometryVectorY, resultY);

		printf("%s\n", "Matriz spline por geometria em Z");
		m.multiplyMatrices4x4by4x4(spline,geometryVectorZ, resultZ);

		float splineTransposta[4][4];

		splineTransposta[0][0] = -1.0/6.0;
		splineTransposta[0][1] = 3.0/6.0;
		splineTransposta[0][2] = -3.0/6.0;
		splineTransposta[0][3] = 1.0/6.0;

		splineTransposta[1][0] = 3.0/6.0;
		splineTransposta[1][1] = -6.0/6.0;
		splineTransposta[1][2] = 0/6.0;
		splineTransposta[1][3] = 4/6.0;

		splineTransposta[2][0] = -3.0/6.0;
		splineTransposta[2][1] = 3.0/6.0;
		splineTransposta[2][2] = 3/6.0;
		splineTransposta[2][3] = 1/6.0;

		splineTransposta[3][0] = 1.0/6.0;
		splineTransposta[3][1] = 0.0/6.0;
		splineTransposta[3][2] = 0/6.0;
		splineTransposta[3][3] = 0/6.0;

		printf("\n\n transposta\n");
		printf("\n\n %f   %f   %f   %f\n", splineTransposta[0][0], splineTransposta[0][1], splineTransposta[0][2], splineTransposta[0][3]);
		printf("\n\n %f   %f   %f   %f\n", splineTransposta[1][0], splineTransposta[1][1], splineTransposta[1][2], splineTransposta[1][3]);
		printf("\n\n %f   %f   %f   %f\n", splineTransposta[2][0], splineTransposta[2][1], splineTransposta[2][2], splineTransposta[2][3]);
		printf("\n\n %f   %f   %f   %f\n", splineTransposta[3][0], splineTransposta[3][1], splineTransposta[3][2], splineTransposta[3][3]);

		printf("%s\n", "setei splineTransposta");

		float resultX2[4][4];
		resultX2[0][0] = 0;
		resultX2[0][1] = 0;
		resultX2[0][2] = 0;
		resultX2[0][3] = 0;

		resultX2[1][0] = 0;
		resultX2[1][1] = 0;
		resultX2[1][2] = 0;
		resultX2[1][3] = 0;

		resultX2[2][0] = 0;
		resultX2[2][1] = 0;
		resultX2[2][2] = 0;
		resultX2[2][3] = 0;

		resultX2[3][0] = 0;
		resultX2[3][1] = 0;
		resultX2[3][2] = 0;
		resultX2[3][3] = 0;

		float resultY2[4][4];
		resultY2[0][0] = 0;
		resultY2[0][1] = 0;
		resultY2[0][2] = 0;
		resultY2[0][3] = 0;

		resultY2[1][0] = 0;
		resultY2[1][1] = 0;
		resultY2[1][2] = 0;
		resultY2[1][3] = 0;

		resultY2[2][0] = 0;
		resultY2[2][1] = 0;
		resultY2[2][2] = 0;
		resultY2[2][3] = 0;

		resultY2[3][0] = 0;
		resultY2[3][1] = 0;
		resultY2[3][2] = 0;
		resultY2[3][3] = 0;

		float resultZ2[4][4];
		resultZ2[0][0] = 0;
		resultZ2[0][1] = 0;
		resultZ2[0][2] = 0;
		resultZ2[0][3] = 0;

		resultZ2[1][0] = 0;
		resultZ2[1][1] = 0;
		resultZ2[1][2] = 0;
		resultZ2[1][3] = 0;

		resultZ2[2][0] = 0;
		resultZ2[2][1] = 0;
		resultZ2[2][2] = 0;
		resultZ2[2][3] = 0;

		resultZ2[3][0] = 0;
		resultZ2[3][1] = 0;
		resultZ2[3][2] = 0;
		resultZ2[3][3] = 0;

		float resultX3[4];
		float resultY3[4];
		float resultZ3[4];
                
		printf("%s\n", "Matriz resultX por resultX");
		m.multiplyMatrices4x4by4x4(resultX,splineTransposta, resultX2);
		//printf("%s\n", "Matriz splineTransposta por resultY");
		m.multiplyMatrices4x4by4x4(resultY,splineTransposta, resultY2);
		//printf("%s\n", "Matriz splineTransposta por resultZ");
		m.multiplyMatrices4x4by4x4(resultZ,splineTransposta, resultZ2);

		printf("%s\n", "multipliquei splineTransposta");

		float tVariation[4];
		float sVariation[4];

		float x_final;
		float y_final;
		float z_final;

		int auxliarVetor = -1;

		for (float s = 0.0; s < 1.1; s = s + 0.2) {
			printf("%s%f\n", "entrei no laco", s);
			sVariation[0] = s * s * s;
			sVariation[1] = s * s;
			sVariation[2] = s;
			sVariation[3] = 1.0;
			auxliarVetor = auxliarVetor + 1;

			m.multiplyPointToMatrix3D(sVariation, resultX2, resultX3);
			m.multiplyPointToMatrix3D(sVariation, resultY2, resultY3);
			m.multiplyPointToMatrix3D(sVariation, resultZ2, resultZ3);
				for( float t = 0.0; t < 1.1; t = t + 0.2){
				tVariation[0] = t * t * t;
				tVariation[1] = t * t;
				tVariation[2] = t;
				tVariation[3] = 1.0;
				x_final = 0;
				y_final = 0;
				z_final = 0;

				x_final = resultX3[0] * tVariation[0];
				x_final += resultX3[1] * tVariation[1];
				x_final += resultX3[2] * tVariation[2];
				x_final += resultX3[3] * tVariation[3];

				y_final = resultY3[0] * tVariation[0];
				y_final += resultY3[1] * tVariation[1];
				y_final += resultY3[2] * tVariation[2];
				y_final += resultY3[3] * tVariation[3];

				z_final = resultZ3[0] * tVariation[0];
				z_final += resultZ3[1] * tVariation[1];
				z_final += resultZ3[2] * tVariation[2];
				z_final += resultZ3[3] * tVariation[3];

				printf("\n\n %f   %f   %f   %f\n", x_final, y_final, z_final, t);

				Coordenada* coordenadaNova = new Coordenada(x_final,y_final,z_final);
				this->coordenadas.push_back(coordenadaNova);
				vetores[auxliarVetor].push_back(coordenadaNova);
				}		
		}

	}

	void clipping(Window window, Viewport viewport) {
		// método de clippagem da reta invocado
	}

	void draw(Viewport viewport, Window window, cairo_t *cr, int clippingType) {
		auxLines.clear();

		
		for(int i= 0; i<6; i++){ //( ligando pontos da esquerda pra direita)
			for (int j= 0; j<5; j++){			
				vector<Coordenada*> points;
				/*printf("Ligando ponto %f %f %f \n", vetores[i].at(j)->getX(),  vetores[i].at(j)->getY(), vetores[i].at(j)->getZ());*/
    				points.push_back(vetores[i].at(j));
   				points.push_back(vetores[i].at(j+1));
    				Line* line = new Line("", points);
				auxLines.push_back(line);
				}
			}

		for(int i= 0; i<6; i++){ //( ligando pontos de cima pra baixo)
			for (int j= 0; j<5; j++){			
				vector<Coordenada*> points;
    				points.push_back(vetores[j].at(i));
   				points.push_back(vetores[j+1].at(i));
    				Line* line = new Line("", points);
				auxLines.push_back(line);
				}
			}

		for( int i = 0; i<auxLines.size(); i++){
				auxLines.at(i)->draw(viewport, window, cr, 1);	
			}
		}

private:
	Coordenada *p11, *p12, *p13, *p14, *p21, *p22, *p23, *p24, *p31, *p32, *p33, *p34, *p41, *p42, *p43, *p44;
	std::vector<Line*> auxLines;
	std::vector<Coordenada*> vetores[6];


};

#endif