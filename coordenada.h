class Coordenada {
	
public:
	Coordenada(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void setCoordenada(int* coordenada) {
		x = coordenada[0];
		y = coordenada[1];
	}

private:
	int x;
	int y;

};