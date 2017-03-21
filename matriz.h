class MatrizUtil {

public:
	MatrizUtil() {

		for (int i = 0; i < 3; i++) {
			translate[i] = new int[3];
			for (int j = 0; j < 3; j++) {
				translate[j] = new int[3];
			}
		}

		translate[0][0] = 1;
		translate[1][0] = 0;
		translate[2][0] = 0;

		translate[0][1] = 0;
		translate[1][1] = 1;
		translate[2][1] = 0;

		translate[0][2] = 0;
		translate[1][2] = 0;
		translate[2][2] = 1;
	}


	int** getTranslate(int entryX, int entryY) {
		translate[2][0] = entryX;
		translate[2][1] = entryY;
		return translate;
	}

private:	
	int** translate;
	int** scale;
	int** rotate;


};