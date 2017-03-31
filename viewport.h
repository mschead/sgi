class Viewport {
	
public:
	Viewport() {
	}

	float obterXdaViewport(float wX, float wXmin, float wXmax) {
		float numerador = wX + 0;//- wXmin;
		float denominador = 1;//wXmax - wXmin;
		float diferencaViewport = xMax - xMin;

		return (numerador / denominador) * diferencaViewport; 
	}

	float obterYdaViewport(float wY, float wYmin, float wYmax) {
		float numerador = wY  + 0; //- wYmin;
		float denominador = 1;//wYmax - wYmin;
		float diferencaViewport = yMax - yMin;

		return (1 - (numerador / denominador))* diferencaViewport; 
	}

private:
	int xMin = 0, yMin = 0, xMax = 300, yMax = 300;

};