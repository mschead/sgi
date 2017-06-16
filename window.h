#include <iostream>
#include <stdio.h>

using namespace std;

class Window {
    
public:
    Window() {
    }
    
    Window(float xmin, float ymin, float xmax, float ymax) {
        this->xmin = xmin;
        this->ymin = ymin;
        this->xmax = xmax;
        this->ymax = ymax;
        this->xCenter = (xmin + xmax) / 2.0;
        this->yCenter = (ymin + ymax) / 2.0;
        this->wPos = 0.0;
        printf("%f, %f\n", xCenter, yCenter);
        printf("%f, %f, %f, %f\n", xmin, xmax, ymin, ymax);
    }
    
    float getXmin() {
        return xmin;
    }
    
    float getYmin() {
        return ymin;
    }
    
    float getXmax() {
        return xmax;
    }
    
    float getYmax() {
        return ymax;
    }
    
    float getXCenter() {
        return xCenter;
    }
    
    float getYCenter() {
        return yCenter;
    }
    
    float getZCenter() {
        return 0;
    }
    
    void setAngleZ(float angleZ) {
        this->angleZ += angleZ;
    }
    
    float getAngleZ() {
        return angleZ;
    }
    
    void setAngleY(float angleY) {
        this->angleY += angleY;
    }
    
    float getAngleY() {
        return angleY;
    }
    
    void setAngleX(float angleX) {
        this->angleX += angleX;
    }
    
    float getAngleX() {
        return angleX;
    }
    
    void refreshCenter() {
        xCenter = (xmin + xmax) / 2.0;
        yCenter = (ymin + ymax) / 2.0;
    }
    
    void setZPos(float zPos) {
        this->wPos = zPos;
    }
    
    float getZPos() {
        return this->wPos;
    }
    
    void setXmin(float xmin) {
        this->xmin += xmin;
    }
    
    void setYmin(float ymin) {
        this->ymin += ymin;
    }
    
    void setXmax(float xmax) {
        this->xmax += xmax;
    }
    
    void setYmax(float ymax) {
        this->ymax += ymax;
    }
    
    float getXSize() {
        return this->xmax - this->xmin;
    }
    
    float getYSize() {
        return this->ymax - this->ymin;
    }
    
    void setProjecaoType(int type) {
        this->projecaoType = type;
    }
    
    int getProjecaoType() {
        return projecaoType;
    }
    
private:
    float xmin, ymin, xmax, ymax;
    float xCenter, yCenter, zCenter, wPos;
    float angleZ = 0, angleY = 0, angleX = 0;
    int projecaoType = 0;
};