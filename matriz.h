class MatrizUtil {

public:
	MatrizUtil() {
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


	void setTranslate(int entryX, int entryY) {
		translate[2][0] = entryX;
		translate[2][1] = entryY;
		// return translate;
	}

	int** getTranslate(int entryX, int entryY) {
		int **t = new int*[3];
		for (int i = 0; i < 3; i++) {
			t[i] = new int[3];
		}

		
		t[2][0] = entryX;
		t[2][1] = entryY;
		return t;
	}

	void multiplyPointToMatrix(int point[3], int result[3]) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i ++) {
				result[j] += point[i] * translate[i][j];
			}
		}
	}

	void multiplyMatrices(int a[][3], int b[][3], int result[][3]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for(int k = 0; k < 3; k++) {
					result[i][j] +=  a[i][k] *  b[k][j];
				}
			}
		}
	}

	void printMatrix3x3(int** a/*[][3]*/) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%d\t", a[i][j]);
			}
			printf("\n");
		}
	}

	void printMatrix1x3(int a[3]) {
		for (int i = 0; i < 3; i++) {
			printf("%d ", a[i]);
		}
	}



private:	
	int translate[3][3];
	int scale[3][3];
	// int** rotate;


};