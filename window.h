#include <iostream>
#include <stdio.h>

using namespace std;

class Window {

public:
	Window() {
	}

	Window(int xmin, int ymin, int xmax, int ymax) {
		this->xmin = xmin;
		this->ymin = ymin;
		this->xmax = xmax;
		this->ymax = ymax;
	}

	int getXmin() {
		return xmin;
	}

	int getYmin() {
		return ymin;
	}

	int getXmax() {
		return xmax;
	}

	int getYmax() {
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
		xCenter = xmin + xmax / 2;
		yCenter = ymin + ymax / 2;
	}

	void setXmin(int xmin) {
		this->xmin += xmin;
	}

	void setYmin(int ymin) {
		this->ymin += ymin;
	}

	void setXmax(int xmax) {
		this->xmax += xmax;
	}

	void setYmax(int ymax) {
		this->ymax += ymax;
	}


private:
	int xmin, ymin, xmax, ymax;
	int xCenter = 150, yCenter = 150;
	float angle = 0;
};