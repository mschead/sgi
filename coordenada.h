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

private:
	int x;
	int y;

};