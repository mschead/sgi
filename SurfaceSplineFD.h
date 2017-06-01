/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SurfaceSplineFD.h
 * Author: schead
 *
 * Created on 27 de Maio de 2017, 22:58
 */

#ifndef SURFACESPLINEFD_H
#define SURFACESPLINEFD_H

#include <cstdio>

#include "object.h"
#include "line.h"


class SurfaceSplineFD : public Object {
    
    public:
        SurfaceSplineFD(char* nome, vector<Coordenada*> coordenadas, 
		Coordenada *p11, Coordenada *p12, Coordenada *p13, Coordenada *p14, 
                Coordenada *p21, Coordenada *p22, Coordenada *p23, Coordenada *p24, 
                Coordenada *p31, Coordenada *p32, Coordenada *p33, Coordenada *p34, 
                Coordenada *p41, Coordenada *p42, Coordenada *p43, Coordenada *p44) : Object(nome, coordenadas) {
                    
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
                    
                    
                    float matrizBSpline[4][4];
                    
                    // NAO ESQUECER DE DIVIDIR POR 6
                    matrizBSpline[0][0] = -1.0 / 6.0;
                    matrizBSpline[0][1] = 3.0 / 6.0;
                    matrizBSpline[0][2] = -3.0 / 6.0;
                    matrizBSpline[0][3] = 1.0 / 6.0;

                    matrizBSpline[1][0] = 3.0 / 6.0;
                    matrizBSpline[1][1] = -6.0 / 6.0;
                    matrizBSpline[1][2] = 3.0 / 6.0;
                    matrizBSpline[1][3] = 0.0;

                    matrizBSpline[2][0] = -3.0 / 6.0;
                    matrizBSpline[2][1] = 0.0;
                    matrizBSpline[2][2] = 3.0 / 6.0;
                    matrizBSpline[2][3] = 0.0;

                    matrizBSpline[3][0] = 1.0 / 6.0;
                    matrizBSpline[3][1] = 4.0 / 6.0;
                    matrizBSpline[3][2] = 1.0 / 6.0;
                    matrizBSpline[3][3] = 0.0;

                    
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
                    
                    printf("%s\n", "Matriz bezier por geometria em X");
                    
                    m.multiplyMatrices4x4by4x4(matrizBSpline, geometryVectorX, resultX);
                    
                    //printf("%s\n", "Matriz bezier por geometria em Y");
                    m.multiplyMatrices4x4by4x4(matrizBSpline, geometryVectorY, resultY);
                    
                    //printf("%s\n", "Matriz bezier por geometria em Z");
                    m.multiplyMatrices4x4by4x4(matrizBSpline, geometryVectorZ, resultZ);
                    
                    //printf("%s\n", "multipliquei bezier");


                    
                    float matrizBSplineTransposta[4][4];
                    
                    matrizBSplineTransposta[0][0] = -1.0 / 6.0;
                    matrizBSplineTransposta[0][1] = 3.0 / 6.0;
                    matrizBSplineTransposta[0][2] = -3.0 / 6.0;
                    matrizBSplineTransposta[0][3] = 1.0 / 6.0;

                    matrizBSplineTransposta[1][0] = 3.0 / 6.0;
                    matrizBSplineTransposta[1][1] = -6.0 / 6.0;
                    matrizBSplineTransposta[1][2] = 0.0 ;
                    matrizBSplineTransposta[1][3] = 4.0 / 6.0;

                    matrizBSplineTransposta[2][0] = -3.0 / 6.0;
                    matrizBSplineTransposta[2][1] = 3.0 / 6.0;
                    matrizBSplineTransposta[2][2] = 3.0 / 6.0;
                    matrizBSplineTransposta[2][3] = 1.0 / 6.0;

                    matrizBSplineTransposta[3][0] = 1.0 / 6.0;
                    matrizBSplineTransposta[3][1] = 0.0;
                    matrizBSplineTransposta[3][2] = 0.0;
                    matrizBSplineTransposta[3][3] = 0.0;                   
                    printf("%s\n", "setei beziertransposta");
                    
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
                    
                    
                    m.multiplyMatrices4x4by4x4(resultX, matrizBSplineTransposta, resultX2);
                    //printf("%s\n", "Matriz beziertransposta por resultY");
                    m.multiplyMatrices4x4by4x4(resultY, matrizBSplineTransposta, resultY2);
                    //printf("%s\n", "Matriz beziertransposta por resultZ");
                    m.multiplyMatrices4x4by4x4(resultZ, matrizBSplineTransposta, resultZ2);
                    
                    // MATRIZ DOS DELTAS
                    
                    float teta = 0.2;
                    float matrizTeta[4][4];
                    float matrizTetaTransposta[4][4];
                    
                    matrizTeta[0][0] = 0;
                    matrizTeta[0][1] = 0;
                    matrizTeta[0][2] = 0;
                    matrizTeta[0][3] = 1;
                    
                    matrizTeta[1][0] = teta * teta * teta;
                    matrizTeta[1][1] = teta * teta;
                    matrizTeta[1][2] = teta;
                    matrizTeta[1][3] = 0;
                    
                    matrizTeta[2][0] = 6.0 * teta * teta * teta;
                    matrizTeta[2][1] = 2.0 * teta * teta;
                    matrizTeta[2][2] = 0;
                    matrizTeta[2][3] = 0;
                    
                    matrizTeta[3][0] = 6.0 * teta * teta * teta;
                    matrizTeta[3][1] = 0;
                    matrizTeta[3][2] = 0;
                    matrizTeta[3][3] = 0;
                    
                    matrizTetaTransposta[0][0] = 0;
                    matrizTetaTransposta[0][1] = teta * teta * teta;
                    matrizTetaTransposta[0][2] = 6.0 * teta * teta * teta;
                    matrizTetaTransposta[0][3] = 6.0 * teta * teta * teta;
                    
                    matrizTetaTransposta[1][0] = 0;
                    matrizTetaTransposta[1][1] = teta * teta;
                    matrizTetaTransposta[1][2] = 2.0 * teta * teta;
                    matrizTetaTransposta[1][3] = 0.0;
                    
                    matrizTetaTransposta[2][0] = 0.0;
                    matrizTetaTransposta[2][1] = teta;
                    matrizTetaTransposta[2][2] = 0.0;
                    matrizTetaTransposta[2][3] = 0.0;
                    
                    matrizTetaTransposta[3][0] = 1.0;
                    matrizTetaTransposta[3][1] = 0.0;
                    matrizTetaTransposta[3][2] = 0.0;
                    matrizTetaTransposta[3][3] = 0.0;
                    
                    float resultX3[4][4];
                    float resultY3[4][4];
                    float resultZ3[4][4];
                    
                    resultX3[0][0] = 0.0;
                    resultX3[0][1] = 0.0;
                    resultX3[0][2] = 0.0;
                    resultX3[0][3] = 0.0;
                    
                    resultX3[1][0] = 0.0;
                    resultX3[1][1] = 0.0;
                    resultX3[1][2] = 0.0;
                    resultX3[1][3] = 0.0;
                    
                    resultX3[2][0] = 0.0;
                    resultX3[2][1] = 0.0;
                    resultX3[2][2] = 0.0;
                    resultX3[2][3] = 0.0;
                    
                    resultX3[3][0] = 0.0;
                    resultX3[3][1] = 0.0;
                    resultX3[3][2] = 0.0;
                    resultX3[3][3] = 0.0;
                    
                    
                    resultY3[0][0] = 0.0;
                    resultY3[0][1] = 0.0;
                    resultY3[0][2] = 0.0;
                    resultY3[0][3] = 0.0;
                    
                    resultY3[1][0] = 0.0;
                    resultY3[1][1] = 0.0;
                    resultY3[1][2] = 0.0;
                    resultY3[1][3] = 0.0;
                    
                    resultY3[2][0] = 0.0;
                    resultY3[2][1] = 0.0;
                    resultY3[2][2] = 0.0;
                    resultY3[2][3] = 0.0;
                    
                    resultY3[3][0] = 0.0;
                    resultY3[3][1] = 0.0;
                    resultY3[3][2] = 0.0;
                    resultY3[3][3] = 0.0;
                    
                    
                    resultZ3[0][0] = 0.0;
                    resultZ3[0][1] = 0.0;
                    resultZ3[0][2] = 0.0;
                    resultZ3[0][3] = 0.0;
                    
                    resultZ3[1][0] = 0.0;
                    resultZ3[1][1] = 0.0;
                    resultZ3[1][2] = 0.0;
                    resultZ3[1][3] = 0.0;
                    
                    resultZ3[2][0] = 0.0;
                    resultZ3[2][1] = 0.0;
                    resultZ3[2][2] = 0.0;
                    resultZ3[2][3] = 0.0;
                    
                    resultZ3[3][0] = 0.0;
                    resultZ3[3][1] = 0.0;
                    resultZ3[3][2] = 0.0;
                    resultZ3[3][3] = 0.0;
                    
                    
                    m.multiplyMatrices4x4by4x4(matrizTeta, resultX2, resultX3);
                    m.multiplyMatrices4x4by4x4(matrizTeta, resultY2, resultY3);
                    m.multiplyMatrices4x4by4x4(matrizTeta, resultZ2, resultZ3);
                    
                    
                    float DDX[4][4];
                    float DDY[4][4];
                    float DDZ[4][4];
                    
                    DDX[0][0] = 0.0;
                    DDX[0][1] = 0.0;
                    DDX[0][2] = 0.0;
                    DDX[0][3] = 0.0;
                    
                    DDX[1][0] = 0.0;
                    DDX[1][1] = 0.0;
                    DDX[1][2] = 0.0;
                    DDX[1][3] = 0.0;
                    
                    DDX[2][0] = 0.0;
                    DDX[2][1] = 0.0;
                    DDX[2][2] = 0.0;
                    DDX[2][3] = 0.0;
                    
                    DDX[3][0] = 0.0;
                    DDX[3][1] = 0.0;
                    DDX[3][2] = 0.0;
                    DDX[3][3] = 0.0;
                    
                    
                    DDY[0][0] = 0.0;
                    DDY[0][1] = 0.0;
                    DDY[0][2] = 0.0;
                    DDY[0][3] = 0.0;
                    
                    DDY[1][0] = 0.0;
                    DDY[1][1] = 0.0;
                    DDY[1][2] = 0.0;
                    DDY[1][3] = 0.0;
                    
                    DDY[2][0] = 0.0;
                    DDY[2][1] = 0.0;
                    DDY[2][2] = 0.0;
                    DDY[2][3] = 0.0;
                    
                    DDY[3][0] = 0.0;
                    DDY[3][1] = 0.0;
                    DDY[3][2] = 0.0;
                    DDY[3][3] = 0.0;
                    
                    
                    DDZ[0][0] = 0.0;
                    DDZ[0][1] = 0.0;
                    DDZ[0][2] = 0.0;
                    DDZ[0][3] = 0.0;
                    
                    DDZ[1][0] = 0.0;
                    DDZ[1][1] = 0.0;
                    DDZ[1][2] = 0.0;
                    DDZ[1][3] = 0.0;
                    
                    DDZ[2][0] = 0.0;
                    DDZ[2][1] = 0.0;
                    DDZ[2][2] = 0.0;
                    DDZ[2][3] = 0.0;
                    
                    DDZ[3][0] = 0.0;
                    DDZ[3][1] = 0.0;
                    DDZ[3][2] = 0.0;
                    DDZ[3][3] = 0.0;
                    
                    
                    m.multiplyMatrices4x4by4x4(resultX3, matrizTetaTransposta, DDX);
                    m.multiplyMatrices4x4by4x4(resultY3, matrizTetaTransposta, DDY);
                    m.multiplyMatrices4x4by4x4(resultZ3, matrizTetaTransposta, DDZ);
                    
                    float DDX_transposta[4][4];
                    
                    DDX_transposta[0][0] = DDX[0][0];
                    DDX_transposta[0][1] = DDX[1][0];
                    DDX_transposta[0][2] = DDX[2][0];
                    DDX_transposta[0][3] = DDX[3][0];

                    DDX_transposta[1][0] = DDX[0][1];
                    DDX_transposta[1][1] = DDX[1][1];
                    DDX_transposta[1][2] = DDX[2][1];
                    DDX_transposta[1][3] = DDX[3][1];
                    
                    DDX_transposta[2][0] = DDX[0][2];
                    DDX_transposta[2][1] = DDX[1][2];
                    DDX_transposta[2][2] = DDX[2][2];
                    DDX_transposta[2][3] = DDX[3][2];
                    
                    DDX_transposta[3][0] = DDX[0][3];
                    DDX_transposta[3][1] = DDX[1][3];
                    DDX_transposta[3][2] = DDX[2][3];
                    DDX_transposta[3][3] = DDX[3][3];
                    
                    
                    
                    float DDY_transposta[4][4];
                    
                    DDY_transposta[0][0] = DDY[0][0];
                    DDY_transposta[0][1] = DDY[1][0];
                    DDY_transposta[0][2] = DDY[2][0];
                    DDY_transposta[0][3] = DDY[3][0];

                    DDY_transposta[1][0] = DDY[0][1];
                    DDY_transposta[1][1] = DDY[1][1];
                    DDY_transposta[1][2] = DDY[2][1];
                    DDY_transposta[1][3] = DDY[3][1];
                    
                    DDY_transposta[2][0] = DDY[0][2];
                    DDY_transposta[2][1] = DDY[1][2];
                    DDY_transposta[2][2] = DDY[2][2];
                    DDY_transposta[2][3] = DDY[3][2];
                    
                    DDY_transposta[3][0] = DDY[0][3];
                    DDY_transposta[3][1] = DDY[1][3];
                    DDY_transposta[3][2] = DDY[2][3];
                    DDY_transposta[3][3] = DDY[3][3];
                    
                    
                    
                    float DDZ_transposta[4][4];
                    
                    DDZ_transposta[0][0] = DDZ[0][0];
                    DDZ_transposta[0][1] = DDZ[1][0];
                    DDZ_transposta[0][2] = DDZ[2][0];
                    DDZ_transposta[0][3] = DDZ[3][0];

                    DDZ_transposta[1][0] = DDZ[0][1];
                    DDZ_transposta[1][1] = DDZ[1][1];
                    DDZ_transposta[1][2] = DDZ[2][1];
                    DDZ_transposta[1][3] = DDZ[3][1];
                    
                    DDZ_transposta[2][0] = DDZ[0][2];
                    DDZ_transposta[2][1] = DDZ[1][2];
                    DDZ_transposta[2][2] = DDZ[2][2];
                    DDZ_transposta[2][3] = DDZ[3][2];
                    
                    DDZ_transposta[3][0] = DDZ[0][3];
                    DDZ_transposta[3][1] = DDZ[1][3];
                    DDZ_transposta[3][2] = DDZ[2][3];
                    DDZ_transposta[3][3] = DDZ[3][3];
                    
                    
                    drawCurveInT(DDX, DDY, DDZ);
                    drawCurveInS(DDX_transposta, DDY_transposta, DDZ_transposta);
                    
                }
                
                
                void drawCurveInT(float DDX[4][4], float DDY[4][4], float DDZ[4][4]) {
                    float DDX_T[4][4], DDY_T[4][4], DDZ_T[4][4];
                    
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            DDX_T[i][j] = DDX[i][j];
                            DDY_T[i][j] = DDY[i][j];
                            DDZ_T[i][j] = DDZ[i][j];
                        }
                    }
                    
                    for (int t = 0; t < 6; t++) {
                        
                        float X[4], Y[4], Z[4];
                        
                        for (int i = 0; i < 4; i++) {
                            X[i] = DDX_T[0][i];
                            Y[i] = DDY_T[0][i];
                            Z[i] = DDZ_T[0][i];
                        }
                        
                        drawCurveFwdDiff(X, Y, Z, t, true);
                        
                        DDX_T[0][0] += DDX_T[1][0];
                        DDX_T[0][1] += DDX_T[1][1];
                        DDX_T[0][2] += DDX_T[1][2];
                        
                        DDX_T[1][0] += DDX_T[2][0];
                        DDX_T[1][1] += DDX_T[2][1];
                        DDX_T[1][2] += DDX_T[2][2];
                        
                        DDX_T[2][0] += DDX_T[3][0];
                        DDX_T[2][1] += DDX_T[3][1];
                        DDX_T[2][2] += DDX_T[3][2];
                        
                        
                        DDY_T[0][0] += DDY_T[1][0];
                        DDY_T[0][1] += DDY_T[1][1];
                        DDY_T[0][2] += DDY_T[1][2];
                        
                        DDY_T[1][0] += DDY_T[2][0];
                        DDY_T[1][1] += DDY_T[2][1];
                        DDY_T[1][2] += DDY_T[2][2];
                        
                        DDY_T[2][0] += DDY_T[3][0];
                        DDY_T[2][1] += DDY_T[3][1];
                        DDY_T[2][2] += DDY_T[3][2];
                        
                        
                        DDZ_T[0][0] += DDZ_T[1][0];
                        DDZ_T[0][1] += DDZ_T[1][1];
                        DDZ_T[0][2] += DDZ_T[1][2];
                        
                        DDZ_T[1][0] += DDZ_T[2][0];
                        DDZ_T[1][1] += DDZ_T[2][1];
                        DDZ_T[1][2] += DDZ_T[2][2];
                        
                        DDZ_T[2][0] += DDZ_T[3][0];
                        DDZ_T[2][1] += DDZ_T[3][1];
                        DDZ_T[2][2] += DDZ_T[3][2];
                        
                    }
                }
                
                void drawCurveInS(float DDX[4][4], float DDY[4][4], float DDZ[4][4]) {
                    float DDX_S[4][4], DDY_S[4][4], DDZ_S[4][4];
                    
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            DDX_S[i][j] = DDX[i][j];
                            DDY_S[i][j] = DDY[i][j];
                            DDZ_S[i][j] = DDZ[i][j];
                        }
                    }
                    
                    for (int s = 0; s < 6; s++) {
                        
                        float X[4], Y[4], Z[4];
                        
                        for (int i = 0; i < 4; i++) {
                            X[i] = DDX_S[0][i];
                            Y[i] = DDY_S[0][i];
                            Z[i] = DDZ_S[0][i];
                        }
                        
                        drawCurveFwdDiff(X, Y, Z, s, false);
                        
                        DDX_S[0][0] += DDX_S[1][0];
                        DDX_S[0][1] += DDX_S[1][1];
                        DDX_S[0][2] += DDX_S[1][2];
                        
                        DDX_S[1][0] += DDX_S[2][0];
                        DDX_S[1][1] += DDX_S[2][1];
                        DDX_S[1][2] += DDX_S[2][2];
                        
                        DDX_S[2][0] += DDX_S[3][0];
                        DDX_S[2][1] += DDX_S[3][1];
                        DDX_S[2][2] += DDX_S[3][2];
                        
                        
                        DDY_S[0][0] += DDY_S[1][0];
                        DDY_S[0][1] += DDY_S[1][1];
                        DDY_S[0][2] += DDY_S[1][2];
                        
                        DDY_S[1][0] += DDY_S[2][0];
                        DDY_S[1][1] += DDY_S[2][1];
                        DDY_S[1][2] += DDY_S[2][2];
                        
                        DDY_S[2][0] += DDY_S[3][0];
                        DDY_S[2][1] += DDY_S[3][1];
                        DDY_S[2][2] += DDY_S[3][2];
                        
                        
                        DDZ_S[0][0] += DDZ_S[1][0];
                        DDZ_S[0][1] += DDZ_S[1][1];
                        DDZ_S[0][2] += DDZ_S[1][2];
                        
                        DDZ_S[1][0] += DDZ_S[2][0];
                        DDZ_S[1][1] += DDZ_S[2][1];
                        DDZ_S[1][2] += DDZ_S[2][2];
                        
                        DDZ_S[2][0] += DDZ_S[3][0];
                        DDZ_S[2][1] += DDZ_S[3][1];
                        DDZ_S[2][2] += DDZ_S[3][2];
                    }
                    
                }
                
                
                
                void drawCurveFwdDiff(float pontosFwdX[4], float pontosFwdY[4], float pontosFwdZ[4], int vector, bool usingVectorsT) {
                    printf("%f, %f, %f, %f\n", pontosFwdX[0], pontosFwdX[1], pontosFwdX[2], pontosFwdX[3]);
                    
                    float xOld = pontosFwdX[0];
                    float yOld = pontosFwdY[0];
                    float zOld = pontosFwdZ[0];
                    
                    Coordenada* c = new Coordenada(pontosFwdX[0], pontosFwdY[0], pontosFwdZ[0]);
                    coordenadas.push_back(c);
                    if (usingVectorsT) {
                        this->vectors_t[vector].push_back(c); 
                    } else {
                        this->vectors_s[vector].push_back(c);
                    }
                    
                    printf("%s\n\n", "Comecando foward differences");
                    
                    for (int i = 0; i < 6; i++) {
			pontosFwdX[0] += pontosFwdX[1];
			pontosFwdX[1] += pontosFwdX[2];
			pontosFwdX[2] += pontosFwdX[3];
                        
			pontosFwdY[0] += pontosFwdY[1];
			pontosFwdY[1] += pontosFwdY[2];
			pontosFwdY[2] += pontosFwdY[3];
                        
			pontosFwdZ[0] += pontosFwdZ[1];
			pontosFwdZ[1] += pontosFwdZ[2];
			pontosFwdZ[2] += pontosFwdZ[3];
                        
                        Coordenada* c = new Coordenada(pontosFwdX[0], pontosFwdY[0], pontosFwdZ[0]);
			this->coordenadas.push_back(c);
                        if (usingVectorsT) {
                            this->vectors_t[vector].push_back(c); 
                        } else {
                            this->vectors_s[vector].push_back(c);
                        }
                        
			xOld = pontosFwdX[0];
			yOld = pontosFwdY[0];
			zOld = pontosFwdZ[0];
                        
                    }
                    printf("%s\n\n", "Terminando foward differences");
                }
                
                void draw (Viewport viewport, Window window, cairo_t *cr, int clippingType) {
                    auxLines.clear();
                    
                    for (int i = 0; i < 6; i++){ //( ligando pontos da esquerda pra direita)
			for (int j= 0; j < 5; j++){			
                            vector <Coordenada*> points;
                            points.push_back(this->vectors_t[i].at(j));
                            points.push_back(this->vectors_t[i].at(j+1));
                            Line* line = new Line("", points);
                            line->draw(viewport, window, cr, clippingType);
                            auxLines.push_back(line);
                        }
                    }
                    
                    for (int i = 0; i < 6; i++){ //( ligando pontos da esquerda pra direita)
			for (int j= 0; j < 5; j++){			
                            vector <Coordenada*> points;
                            points.push_back(this->vectors_s[i].at(j));
                            points.push_back(this->vectors_s[i].at(j+1));
                            Line* line = new Line("", points);
                            line->draw(viewport, window, cr, clippingType);
                            auxLines.push_back(line);
                        }
                    }
                    
                    
                }
                
                void clipping (Window window, Viewport viewport) {
                    // clipping feito pelas retas
                }
                
                
                private:
                    Coordenada *p11, *p12, *p13, *p14, *p21, *p22, *p23, *p24, *p31, *p32, *p33, *p34, *p41, *p42, *p43, *p44;
                    std::vector<Line*> auxLines;
                    std::vector<Coordenada*> vectors_t[6];
                    std::vector<Coordenada*> vectors_s[6];
                    
                    
};

#endif /* SURFACESPLINEFD_H */

