#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "coordenada.h"
#include "matriz.h"
#include <math.h>
#include "matrix3D.h"

using namespace std;

class Object {

public:
	Object(const char* nome, vector<Coordenada*> coordenadas) {
		this->nome = nome;
		this->coordenadas = coordenadas;
	}

	Object(const char* nome) {
		this->nome = nome;
	}

	~Object() {
            delete nome;
            
            for (Coordenada* coordinate : coordenadas) {
                delete coordinate;
            }
            
            for (Coordenada* normalizedCoordinate : normalizedCoordinates) {
                delete normalizedCoordinate;
            }
	}

	const char* getName() {
		return nome;
	}

	vector<Coordenada*> getPoints() {
		return coordenadas;
	}

	virtual void draw (Viewport viewport, Window window, cairo_t *cr, int clippingType) = 0;

	virtual void clipping (Window window, Viewport viewport) = 0;

	Coordenada pontoMedio() {
		float x = 0;
		float y = 0;
		float z = 0;

		for (Coordenada* coordenada : coordenadas) {
			x += coordenada->getX();
			y += coordenada->getY();
			z += coordenada->getZ();
		}

		x = x / coordenadas.size();
		y = y / coordenadas.size();
		z = z / coordenadas.size();

		Coordenada c(x, y, z);
		return c;
	}

	void drawNormalized(Window window) {
		vector<Coordenada*> ortogonalized = ortogonalize(window);

		Matrix translateCenter, rotate, scale;

		Matrix result1, result2, result3, result;

		result1.setZero();
		result2.setZero();
		result3.setZero();
		result.setZero();

		// printf("%f, %f\n", -1.0 * window.getXCenter(), -1.0 * window.getYCenter());

		translateCenter.setTranslate(-1.0 * window.getXCenter(), -1.0 * window.getYCenter());
		rotate.setRotate(-1.0 * window.getAngleZ());
		
		float t1;
		float t2;

		if (window.getXSize() == 0 || window.getYSize() == 0) {
			t1 = 1.0;
			t2 = 1.0;
		} else {
			t1 = 1.0 / window.getXSize();
			t2 = 1.0 / window.getYSize() ;
		}

		scale.setScale(t1, t2);

		float f1, f2;

		if (window.getXCenter() == 0 || window.getYCenter() == 0) {
			f1 = 0.0;
			f2 = 0.0;
		} else {
			f1 = (-1.0 / window.getXCenter());
			f2 = (-1.0 / window.getYCenter());			
		}

		// printf("%f, %f\n", f1, f2);
		
		// translateBack.setTranslate(f1, f2);

		// result1.printMatrix3x3(translateCenter);
		// printf("\n");
		// result1.printMatrix3x3(rotate);
		// printf("\n");
		// result1.printMatrix3x3(scale);
		// printf("\n");
		// result1.printMatrix3x3(translateBack);

//		result.multiplyMatrices(translateCenter, rotate, result1);
//		result.multiplyMatrices(rotate, scale, result2);
//                result.multiplyMatrices(result2, translateCenter, result1);

		// printf("\n");
		// result1.printMatrix3x3(result1);
		// printf("\n");
		// result1.printMatrix3x3(result2);
		// printf("\n");
		// result1.printMatrix3x3(result3);

		for (Coordenada* coordenada : ortogonalized) {
			float normalizePoint[3] = {0, 0, 0};
                        // verificar essa coordenada aqui
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};

			result.multiplyPointToMatrix(point, scale, normalizePoint);
                        
                        printf("%f, %f\n", normalizePoint[0], normalizePoint[1]);
			normalizedCoordinates.push_back(new Coordenada(normalizePoint[0], normalizePoint[1], 1));
		}

	}

	void translate(int entryX, int entryY, int entryZ) {
		Matrix3D m;
		m.setTranslate(entryX, entryY, entryZ);
            for (Coordenada* coordenada : coordenadas) {
			printf("ANTES: %f, %f, %f\n", coordenada->getX(), coordenada->getY(), coordenada->getZ());
			float result[4] = {0, 0, 0, 0};
			float point[4] = {coordenada->getX(), coordenada->getY(), coordenada->getZ(), 1};
			m.multiplyPointToMatrix(point, m, result);
			coordenada->setCoordenada(result);
		}

		for (Coordenada* coordenada : coordenadas) {
			printf("DEPOIS: %f, %f, %f\n", coordenada->getX(), coordenada->getY(), coordenada->getZ());
		}
	}


	void scale(float entryX, float entryY, float entryZ) {
		Coordenada pontoMedio = this->pontoMedio();

		Matrix3D m1, m2, m3, result1, result2;

		m1.setTranslate(-1 * pontoMedio.getX(), -1 * pontoMedio.getY(), -1 * pontoMedio.getZ());
		m2.setScale(entryX, entryY, entryZ);
		m3.setTranslate(pontoMedio.getX(), pontoMedio.getY(), pontoMedio.getZ());

		result1.setZero();
		result2.setZero();
		
		m1.multiplyMatrices(m1, m2, result1);
		m1.multiplyMatrices(result1, m3, result2);

		for (Coordenada* coordenada : coordenadas) {
			float result3[4] = {0, 0, 0, 0};
			float point[4] = {coordenada->getX(), coordenada->getY(), coordenada->getZ(), 1};
			m1.multiplyPointToMatrix(point, result2, result3);
			coordenada->setCoordenada(result3);
		}

	}

	void rotate(int angX, int angY, int angZ) {

		Coordenada pontoMedio = this->pontoMedio();

		Matrix3D m1, matrixX, matrixY, matrixZ, m3, resultX, resultY, resultZ, final;
		m1.setTranslate(-1 * pontoMedio.getX(), -1 * pontoMedio.getY(), -1 * pontoMedio.getZ());
		
		// matrixX.printMatrix4x4(matrixX);
		matrixX.setRotateX(angX);
		// matrixX.printMatrix4x4(matrixX);

		matrixY.setRotateY(angY);
		matrixZ.setRotateZ(angZ);
		m3.setTranslate(pontoMedio.getX(), pontoMedio.getY(), pontoMedio.getZ());
		
		resultX.setZero();
		resultY.setZero();
		resultZ.setZero();
		final.setZero();
		
		// matrixX.printMatrix4x4(matrixX);
		// matrixY.printMatrix4x4(matrixY);
		// matrixZ.printMatrix4x4(matrixZ);

		// resultX.printMatrix4x4(resultX);
		// resultY.printMatrix4x4(resultY);
		// resultZ.printMatrix4x4(resultZ);
		



		m1.multiplyMatrices(m1, matrixX, resultX);
		m1.multiplyMatrices(resultX, matrixY, resultY);
		m1.multiplyMatrices(resultY, matrixZ, resultZ);
		m1.multiplyMatrices(resultZ, m3, final);

		resultZ.printMatrix4x4(m1);
		resultZ.printMatrix4x4(m3);

		matrixX.printMatrix4x4(matrixX);
		matrixY.printMatrix4x4(matrixY);
		matrixZ.printMatrix4x4(matrixZ);

		resultX.printMatrix4x4(resultX);
		resultY.printMatrix4x4(resultY);
		resultZ.printMatrix4x4(resultZ);
		// resultZ.printMatrix4x4(m1);
		
		// final.printMatrix4x4(final);
		// m1.printMatrix3x3(result2);

		for (Coordenada* coordenada : coordenadas) {
			float finalPoint[4] = {0, 0, 0, 0};
			float point[4] = {coordenada->getX(), coordenada->getY(), coordenada->getZ(), 1};
			m1.multiplyPointToMatrix(point, final, finalPoint);
			coordenada->setCoordenada(finalPoint);
		}

	}


	void rotateUsingCoordinate(int ang, float entryX, float entryY) {
		Matrix m1, m2, m3, result1, result2;

		m1.setTranslate(-1 * entryX, -1 * entryY);
		m2.setRotate(ang);
		m3.setTranslate(entryX, entryY);
		
		result1.setZero();
		result2.setZero();

		// m1.printMatrix3x3(m1);
		// m1.printMatrix3x3(m2);
		// m1.printMatrix3x3(m3);


		m1.multiplyMatrices(m1, m2, result1);

		m1.printMatrix3x3(result1);


		m1.multiplyMatrices(result1, m3, result2);

		// m1.printMatrix3x3(result2);

		for (Coordenada* coordenada : coordenadas) {
			float result3[3] = {0, 0, 0};
			float point[3] = {coordenada->getX(), coordenada->getY(), 1};
			m1.multiplyPointToMatrix(point, result2, result3);
			coordenada->setCoordenada(result3);
		}

	}


	std::vector<Coordenada*> ortogonalize(Window window) {
            
		std::vector<Coordenada*> perspectiva;
		Matrix3D m, translateCenter, rotateZ, rotateY, rotateX, projecao;
		Matrix3D result1, result2, result3, result4;
                result1.setZero();
                result2.setZero();
                result3.setZero();
                result4.setZero();

                if (!window.getProjecaoType()) {
                    translateCenter.setTranslate(-1.0 * window.getXCenter(), -1.0 * window.getYCenter(), -1.0 * window.getZPos());
                } else {
                    translateCenter.setTranslate(-1.0 * window.getXCenter(), -1.0 * window.getYCenter(), -189.0);
                    projecao.setProjecaoPerspectiva(-189.0);
                }
                
		rotateY.setRotateY(-1 * window.getAngleY());
		rotateX.setRotateX(-1 * window.getAngleX());
                rotateZ.setRotateZ(-1 * window.getAngleZ());
                
		m.multiplyMatrices(translateCenter, rotateX, result1);
		m.multiplyMatrices(result1, rotateY, result2);
                m.multiplyMatrices(result2, rotateZ, result3);
                m.multiplyMatrices(result3, projecao, result4);
                
		for (Coordenada* coordenada : coordenadas) {
			float result5[4] = {0, 0, 0, 0};
			float point[4] = {coordenada->getX(), coordenada->getY(), coordenada->getZ(), 1.0};
			m.multiplyPointToMatrix(point, result4, result5);

                        perspectiva.push_back(new Coordenada(result5[0] / result5[3], result5[1] / result5[3], result5[3] / result5[3]));
		}

		return perspectiva;

	}


protected:
	const char* nome;
	vector<Coordenada*> coordenadas;
	vector<Coordenada*> normalizedCoordinates;
	
};

#endif
