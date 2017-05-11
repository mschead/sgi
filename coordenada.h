class Coordenada {
	
public:
	Coordenada(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	void setX(float x) {
		this->x = x;
	}

	void setY(float y) {
		this->y = y;
	}

	void setZ(float z) {
		this->z = z;
	}

	void setCoordenada(float* coordenada) {
		x = coordenada[0];
		y = coordenada[1];
		z = coordenada[2];
	}

private:
	float x;
	float y;
	float z;

};