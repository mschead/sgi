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
};