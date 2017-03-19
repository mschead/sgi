class Viewport {
	
public:
	Viewport() {
	}

	float obterXdaViewport(float wX, float wXmin, float wXmax) {
		float numerador = wX - wXmin;
		float denominador = wXmax - wXmin;
		float diferencaViewport = xMax - xMin;

		printf("%s%f\n", "Numerador x: ", numerador);
		printf("%s%f\n", "Denominador x: ", denominador);
		printf("%s%f\n", "Diferença viewport x: ", diferencaViewport);

		return (numerador / denominador) * diferencaViewport; 
	}

	float obterYdaViewport(float wY, float wYmin, float wYmax) {
		float numerador = wY - wYmin;
		float denominador = wYmax - wYmin;
		float diferencaViewport = yMax - yMin;

		printf("%s%f\n", "Numerador y: ", numerador);
		printf("%s%f\n", "Denominador y: ", denominador);
		printf("%s%f\n", "Diferença viewport y: ", diferencaViewport);
		return (1 - (numerador / denominador))* diferencaViewport; 
	}

private:
	int xMin = 0, yMin = 0, xMax = 300, yMax = 300;

};