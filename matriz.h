class Matrix {

public:
	Matrix() {
		identity[0][0] = 1;
		identity[1][0] = 0;
		identity[2][0] = 0;

		identity[0][1] = 0;
		identity[1][1] = 1;
		identity[2][1] = 0;

		identity[0][2] = 0;
		identity[1][2] = 0;
		identity[2][2] = 1;
	}



	void setTranslate(int entryX, int entryY) {
		identity[2][0] = entryX;
		identity[2][1] = entryY;
	}

	void setScale(int entryX, int entryY) {
		identity[0][0] = entryX;
		identity[1][1] = entryY;
	}

	void multiplyPointToMatrix(int point[3], Matrix transform, int result[3]) {
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i ++) {
				result[j] += point[i] * transform.identity[i][j];
			}
		}
	}

	void multiplyMatrices(Matrix a, Matrix b, Matrix &result) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for(int k = 0; k < 3; k++) {
					result.identity[i][j] +=  a.identity[i][k] *  b.identity[k][j];
				}
			}
		}
	}

	void printMatrix3x3(Matrix a) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%d\t", a.identity[i][j]);
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
	int identity[3][3];

};