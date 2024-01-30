#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiply(double** a, double** b, double** c, int Brows, int Acolumns, int overlap) {

    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < columns; j++) {
    //         //printf("i: %d, j: %d, %d\n", i, j, A[0][0]); 
    //         for (int k = 0; k < columns; k++) {
    //     		printf("A: %f, B: %f, C: %f\n", a[i][k], b[k][j], c[i][j]);
    //         	c[i][j] = c[i][j] + (a[i][k] * b[k][i]);
    //         	//printf("i: %d, j: %d, k: %d, A[i][0]: %f, B[k][j]: %f, C[i][j]: %f\n", i, j, k, a[i][k], b[k][j], c[i][j]);
    //         }
    //         //printf("NEXT");
    //     }
    // }
	double sum;
	for (int i = 0; i < Brows; i++){
		for (int j = 0; j < Acolumns; j++){
			sum = 0;
			for (int k = 0; k < overlap; k++){
				//printf("B: %f, A: %f\n", b[i][k], a[k][j]);
				sum = sum + (b[i][k] * a[k][j]);
				//printf("%f * %f = SUM: %f |\n", b[i][k], a[k][j], sum);
			}
			c[i][j] = sum;
			//printf("\n\nC: %f\n\n", c[i][j]);
		} 
	}

}

//ONLY WORKS IF FIRST COLUMN CONTAINS ONLY 1s
double** inverse(double** d, double** e, int size){
	//simplifies matrix d to identity matrix
	for (int i = 0; i < size; i++){
		double first = d[i][i];

		for(int j = 0; j < size; j++){
			d[i][j] = d[i][j] / first;
			e[i][j] = e[i][j] / first;

			//check
			//printf("%f, %f\n", d[i][j], e[i][j]);
		}
		for (int k = i+1; k < size; k++){
			double next = d[k][i];
			for(int l = 0; l < size; l++){
				d[k][l] = d[k][l] - (d[i][l] * next);
				e[k][l] = e[k][l] - (e[i][l] * next);
			}
		}
	}
	//printf("FIRST HALF GOOD\n");
	//creates inverse of d into e
	for (int m = size - 1; m >= 0; m--){
		for (int n = m - 1; n >= 0; n--){
			double first2 = d[n][m];
			for(int o = size - 1; o >= 0; o--){
				d[n][o] = d[n][o] - (d[m][o] * first2);
				e[n][o] = e[n][o] - (e[m][o] * first2);
				//printf("%f, %f\n", d[m][o], e[m][o]);
			}
		}
	}

	return e;
}

void transpose(double** orig, double** transp, int rows, int columns){

	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			transp[i][j] = orig[j][i];
			// if(j == rows - 1){
            //     	printf("%f", transp[i][j]);
            // 	} else {
            //         printf("%f ", transp[i][j]);
            // 	}
		}
		//printf("\n");
	}
	// printf("END\n");
}

int main (int argc, char* argv[]){

	 // Open file 

	
    FILE* fptr = fopen(argv[1], "r");

	char* mode = (char*)malloc(5 * sizeof(char*)); 
	char* mode2 = (char*)malloc(5 * sizeof(char*)); 

	//Checks file type
	fscanf(fptr, "%5s", mode);
	//printf("mode: %d\n", mode);

	if(strcmp(mode, "train") != 0){
		printf("CORRUPT FILE\n");
		return 1;
	}

	// Read attributes and rows
	int attributes, columns, rows, size, size2;
	fscanf(fptr, "%d", &attributes);
	fscanf(fptr, "%d", &rows);
	// columns = attributes + 1
	columns = attributes + 1;
	size = rows*columns;
	size2 = columns*columns;
	//printf("SIZE: %d\n", size);


	double** X = (double**)malloc((size) * sizeof(double*));
	double** XT = (double**)malloc((size) * sizeof(double*));
	double** XT2 = (double**)malloc((size) * sizeof(double*));
	double** prod = (double**)malloc((size2) * sizeof(double*));
	double** iden = (double**)malloc((size2) * sizeof(double*));
	double** Y = (double**)malloc(rows * sizeof(double*));
	double** W = (double**)malloc(columns * sizeof(double*));

	double** TEST = (double**)malloc(rows * sizeof(double*));

	for (int i = 0; i < size; i++) {
		X[i] = (double*)malloc(size * sizeof(double)); 
		XT[i] = (double*)malloc(size * sizeof(double)); 
		XT2[i] = (double*)malloc((size) * sizeof(double*));
	}

	for (int i = 0; i < rows; i++){
		Y[i] = (double*)malloc(rows * sizeof(double));
		TEST[i] = (double*)malloc(rows * sizeof(double*));
	}

	for (int i = 0; i < columns; i++){
		W[i] = (double*)malloc(columns * sizeof(double));
	}

	for (int i = 0; i < size2; i++){
		prod[i] = (double*)malloc((size2) * sizeof(double*));
		iden[i] = (double*)malloc((size2) * sizeof(double*));
	}


	//READS MATRICES
	for (int i = 0; i < rows; i++) {
		X[i][0] = 1;
		for (int j = 1; j < columns; j++) {
			fscanf(fptr, "%lf", &X[i][j]);
			//printf("i: %d, j: %d, %f\n", i, j, X[i][j]);
		}
		fscanf(fptr, "%lf", &Y[i][0]);
	}


	transpose(X, XT, rows, columns);

	//PRINTS TRANSPOSE
	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < rows; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", XT[i][j]);
	// 		} else {
	// 			printf("%f ", XT[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("XT\n");
	//

	multiply(X, XT, prod, columns, columns, rows);

	// PRODUCT
	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < columns; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", prod[i][j]);
	// 		} else {
	// 			printf("%f ", prod[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("PROD\n");
	//

	// makes identity matrix
	for(int i = 0; i < columns; i++){
		for(int j = 0; j < columns; j++){
			if(i == j){
				iden[i][j] = 1;
			} else {
				iden[i][j] = 0; 
			}
		}
	}
	
	inverse(prod, iden, columns);

	//PRINTS INVERSE
	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < columns; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", iden[i][j]);
	// 		} else {
	// 			printf("%f ", iden[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("iden\n");
	//

	multiply(XT, iden, XT2, columns, rows, columns);

	//PRINTS (XT*X)^-1 * XT
	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < rows; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", XT2[i][j]);
	// 		} else {
	// 			printf("%f ", XT2[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("XT2\n");
	//

//FIX HERE
	multiply(Y, XT2, W, columns, 1, rows);

	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < 1; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", W[i][j]);
	// 		} else {
	// 			printf("%f ", W[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("W\n");


//CHECKING
	// multiply(W, X, TEST, rows, 1, columns);

	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < rows; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", TEST[i][j]);
	// 		} else {
	// 			printf("%f ", TEST[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("TEST\n");

	// for (int i = 0; i < columns; i++) {
	// 	for (int j = 0; j < rows; j++) {
	// 		if(j == rows - 1){
	// 			printf("%f", Y[i][j]);
	// 		} else {
	// 			printf("%f ", Y[i][j]);
	// 		}

	// 	}
	// 	//printf("%f", Y[i][0]);
	// 	printf("\n");
	// }
	// printf("Y\n");


	
	// Free memory
	for (int i = 0; i < size; i++) {
		free(X[i]);
		free(XT[i]);
		free(XT2[i]);
	}

	for (int i = 0; i < rows; i++){
		free(Y[i]);
	}

	for (int i = 0; i < size2; i++){
		free(prod[i]);
		free(iden[i]);
	}

	free(X);
	free(XT);
	free(XT2);
	free(Y);
	free(prod);
	free(iden);

	fclose(fptr);
	

	//printf("DONE 1\n");
	//END OF TRAINING

	FILE* fptr2 = fopen(argv[2], "r");

	//Checks file type
	fscanf(fptr2, "%5s", mode2);

	if(strcmp(mode2, "data") != 0){
		printf("CORRUPT FILE\n");
		return 1;
	}

	int attributes2;
	// Read attributes and rows
	fscanf(fptr2, "%d", &attributes2);

	if(attributes != attributes2){
		printf("error");
		return 1;
	}

	fscanf(fptr2, "%d", &rows);
	// columns = attributes + 1
	columns = attributes2 + 1;
	size = rows*columns;
	//printf("SIZE: %d\n", size);
	double** Xp = (double**)malloc((size) * sizeof(double*));
	double** Yp = (double**)malloc(rows * sizeof(double*));
	//double** W = (double**)malloc(columns * sizeof(double*));

	for (int i = 0; i < size; i++) {
		Xp[i] = (double*)malloc(size * sizeof(double)); 
	}

	for (int i = 0; i < rows; i++){
		Yp[i] = (double*)malloc(rows * sizeof(double));
	}

	// for (int i = 0; i < columns; i++){
	// 	W[i] = (double*)malloc(columns * sizeof(double));
	// }

	//READS DATA MATRIX
	for (int i = 0; i < rows; i++) {
		Xp[i][0] = 1;
		for (int j = 1; j < columns; j++) {
			fscanf(fptr2, "%lf", &Xp[i][j]);
			//printf("i: %d, j: %d, %f\n", i, j, A[i][j]);
		}
	}

	//PRINTS OUT DATA MATRIX (X[])
	// for (int i = 0; i < rows; i++) {
	// 	for (int j = 0; j < columns; j++) {
	// 		if(j == columns - 1){
	// 			printf("%f", X[i][j]);
	// 		} else {
	// 			printf("%f ", X[i][j]);
	// 		}
	// 	}
	// 	printf("\n");
	// }

	multiply(W, Xp, Yp, rows, 1, columns);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 1; j++) {
				printf("%.0f", Yp[i][j]);
		}
		printf("\n");
	}


	for (int i = 0; i < size; i++) {
		free(Xp[i]);
	}

	for (int i = 0; i < rows; i++){
		free(Yp[i]);
	}

	for (int i = 0; i < columns; i++){
		free(W[i]);
	}

	free(Xp);
	free(Yp);
	free(W);

	free(mode);
	free(mode2);

	return 0;
	
}