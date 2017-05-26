#include <iostream>
#include <stdio.h>
#include <math.h>

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
		this->angleZ = fmod((this->angleZ + angleZ), 360);
	}

	float getAngleZ() {
		return angleZ;
	}

	void setAngleY(float angleY) {
		this->angleY = fmod((this->angleY + angleY), 360);
	}

	float getAngleY() {
		return angleY;
	}

	void setAngleX(float angleX) {
		this->angleX = fmod((this->angleX + angleX), 360);
	}

	float getAngleX() {
		return angleX;
	}

	void refreshCenter() {
		xCenter = (xmin + xmax) / 2.0;
		yCenter = (ymin + ymax) / 2.0;
		// zCenter = ()
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


private:
	float xmin, ymin, xmax, ymax;
	float xCenter, yCenter, zCenter;
	float angleZ = 0, angleY = 0, angleX = 0;
};