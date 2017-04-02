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

	void setAngle(float angle) {
		this->angle += angle;
	}

	float getAngle() {
		return angle;
	}

	void refreshCenter() {
		xCenter = (xmin + xmax) / 2.0;
		yCenter = (ymin + ymax) / 2.0;
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


private:
	float xmin, ymin, xmax, ymax;
	float xCenter, yCenter;
	float angle = 0;
};