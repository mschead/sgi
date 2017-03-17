#include <iostream>
#include <stdio.h>
#include <list>
#include "formageometrica.h"
#include "viewport.h"

using namespace std;

class Window {

public:
	Window() {
	}

	void inserirFormaGeometrica(FormaGeometrica forma) {
		displayFile.push_back(forma);
	}

	

private:
	int xmin, ymin, xman, ymax;
	list<FormaGeometrica> displayFile;
	Viewport viewport;

};