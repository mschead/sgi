#include <math.h>
#define PI 3.14159265

class Matrix3D {
	
public:
	Matrix3D() {
		identity[0][0] = 1;
		identity[1][0] = 0;
		identity[2][0] = 0;
		identity[3][0] = 0;

		identity[0][1] = 0;
		identity[1][1] = 1;
		identity[2][1] = 0;
		identity[3][1] = 0;

		identity[0][2] = 0;
		identity[1][2] = 0;
		identity[2][2] = 1;
		identity[3][2] = 0;

		identity[0][3] = 0;
		identity[1][3] = 0;
		identity[2][3] = 0;
		identity[3][3] = 1;
	}

	void setTranslate(float entryX, float entryY, float entryZ) {
		identity[3][0] = entryX;
		identity[3][1] = entryY;
		identity[3][2] = entryZ;
	}

	void setScale(float entryX, float entryY, float entryZ) {
		identity[0][0] = entryX;
		identity[1][1] = entryY;
		identity[2][2] = entryZ;
	}

	void setRotateX(int ang) {
		float angleRad = ang * PI / 180;

		identity[1][1] = cos (angleRad);
		identity[1][2] = -1.0 * sin (angleRad);
		identity[2][1] = sin (angleRad);
		identity[2][2] = cos (angleRad);
	}

	void setRotateY(int ang) {
		float angleRad = ang * PI / 180;

		identity[0][0] = cos (angleRad);
		identity[0][2] = -1.0 * sin (angleRad);
		identity[2][0] = sin (angleRad);
		identity[2][2] = cos (angleRad);
	}

	void setRotateZ(int ang) {
		float angleRad = ang * PI / 180;

		identity[0][0] = cos (angleRad);
		identity[0][1] = sin (angleRad);
		identity[1][0] = -1.0 * sin (angleRad);
		identity[1][1] = cos (angleRad);
	}


	void setZero() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				identity[i][j] = 0;
			}
		}
	}

	void multiplyPointToMatrix(float point[4], Matrix3D transform, float result[4]) {
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i ++) {
				result[j] += point[i] * transform.identity[i][j];
			}
		}
	}

	void multiplyMatrices(Matrix3D a, Matrix3D b, Matrix3D &result) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for(int k = 0; k < 4; k++) {
					result.identity[i][j] +=  a.identity[i][k] *  b.identity[k][j];
				}
			}
		}
	}

	void printMatrix4x4(Matrix3D a) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				printf("%f\t", a.identity[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	void printMatrix1x4(int a[4]) {
		for (int i = 0; i < 4; i++) {
			printf("%d ", a[i]);
		}
	}

private:	
	float identity[4][4];


};