class Coordenada {
	
public:
	Coordenada(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}

	void setCoordenada(float* coordenada) {
		x = coordenada[0];
		y = coordenada[1];
	}

private:
	float x;
	float y;

};