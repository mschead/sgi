class Viewport {
	
public:
	Viewport() {
	}

	float obterXdaViewport(float wX, float wXmin, float wXmax) {
		float numerador = wX + 1.0;//- wXmin;
		float denominador = 2.0;//wXmax - wXmin;
		float diferencaViewport = xMax - xMin;

		return (numerador / denominador) * diferencaViewport; 
	}

	float obterYdaViewport(float wY, float wYmin, float wYmax) {
		float numerador = wY + 1.0; //- wYmin;
		float denominador = 2.0;//wYmax - wYmin;
		float diferencaViewport = yMax - yMin;

		return (1.0 - (numerador / denominador)) * diferencaViewport; 
	}

private:
	float xMin = 0.0, yMin = 0.0, xMax = 300.0, yMax = 300.0;

};