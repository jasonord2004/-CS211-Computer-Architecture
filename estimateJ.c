#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void freeMatrix(double **matrix, int rows){
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}


void invert(int rows, int cols, double **matrix, double **identity){

/*Assign our identity matrix its identity values*/
for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
        if (i == j){
            identity[i][j] = 1;
        }else{
            identity[i][j] = 0;
        }
    }
}

double **copy = malloc(rows*sizeof(double *));
for (int i = 0; i < rows; i++){
    copy[i] = malloc(cols*sizeof(double));
}

/*Assign copy the same values as matrix*/
for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
        copy[i][j] = matrix[i][j];
    }
}

/*Run Gauss-Jordan*/
for (int i = 0; i < rows; i++){
    double pivot = matrix[i][i];
    for (int j = 0; j < cols; j++){
        copy[i][j] /= pivot;
        identity[i][j] /= pivot;
    }
        for (int r = 0; r < rows; r++){
                 if (r != i){
                    double scalar = matrix[r][i];
                    for (int c = 0; c < cols; c++){
                    copy[r][c] = copy[r][c] - (scalar * copy[i][c]);
                    identity[r][c] = identity[r][c] - (scalar * identity[i][c]);
                    }
                }
            }
        }
        freeMatrix(copy,rows);
}




void transpose(int rows, int cols, double **matrix){

double **copy = malloc(cols*sizeof(double*));
for (int i = 0; i < cols; i++){
    copy[i] = malloc(rows*sizeof(double));
}


for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      copy[j][i] = matrix[i][j];
    }
}

for (int i = 0; i < cols; i++){
    for (int j = 0; j < rows; j++){
        matrix[i][j] = copy[i][j];
    }
}

freeMatrix(copy,cols);
}


void multiplyMatrices(double **matrix, double **output, double **multiple, int rows, int cols, int cols1) { 
int i,j,c;
for (i = 0; i < rows; i++){
    for (j = 0; j < cols1; j++){
        output[i][j] = 0;
    for (c = 0; c < cols; c++){
        output[i][j] += matrix[i][c] * multiple[c][j]; 
    }
    }
}
}


int main(int argc, char *argv[]) {


    FILE* file1 = fopen(argv[1], "r");
    FILE* file2 = fopen(argv[2], "r");

    char word[100]; /*Contains the word train*/
    fscanf(file1, "%s", word);
    char word2[100]; /*Contains the word data*/
    fscanf(file2,"%s",word2);

        int k,n; 
        fscanf(file1, "%d", &k); /*Contains the number of attributes. X matrix will have this number of cols+1*/
        fscanf(file1, "%d", &n); /*Contains the number of houses*/

    int rows = n;
    int cols = k+1;

    double **X = malloc(rows*sizeof(double *));
    for (int i = 0; i < rows; i++){
        X[i] = malloc(cols*sizeof(double));
    }
    
    double **Y = malloc(rows*sizeof(double *));
    for (int i = 0; i < rows; i++){
        Y[i] = malloc(sizeof(double));
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (j == 0){
                X[i][j] = 1;
            }else if(j == cols-1){
                double number;
                fscanf(file1, "%lf", &number);
                printf("%f", number);
                Y[j][0] = number;
            }else {
                double number;
                fscanf(file1, "%lf", &number);
                printf("%f", number);
                X[i][j] = number;
            }
        }
    }


    for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if(j == rows - 1){
				printf("%f", X[i][j]);
			} else {
				printf("%f ", X[i][j]);
			}

		}
		//printf("%f", Y[i][0]);
		printf("\n");
	}
	printf("XT\n");


double **W = malloc((k+1)*sizeof(double *));
 for (int i = 0; i < k+1; i++){
        W[i] = malloc(sizeof(double));
    }

double **copyX = malloc(rows*sizeof(double *));
for (int i = 0; i < rows; i++){
    copyX[i] = malloc(cols*sizeof(double));
}

for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
        copyX[i][j] = X[i][j];
    }
}

/*Transpose the copy of X*/
transpose(rows, cols, copyX); /*copyX is now x Transposed, so copyX rows = cols and cols = rows*/

/*Multiply the transpose of X with X*/
double **productXsubT = malloc(cols*sizeof(double *));
for (int i = 0; i < cols; i++){
    productXsubT[i] = malloc(cols * sizeof(double));
}
multiplyMatrices(X,productXsubT,copyX,rows,cols,rows);

/*Invert this new product*/
double **identity = malloc(cols * sizeof(double *));
for (int i = 0; i < cols; i++){
    identity[i] = malloc(cols *sizeof(double));
}

invert(rows,rows,productXsubT,identity);

/*Multiply the inverse by the transpose of X*/
double **productInTrans = malloc(cols*sizeof(double *));
for (int i = 0; i < cols; i++){
    productInTrans[i] = malloc(rows * sizeof(double));
}
multiplyMatrices(identity,productInTrans,copyX,rows,rows,rows);

/*Finally, multiply the result by Y*/
double **outputY = malloc(cols * sizeof(double *));
for (int i = 0; i < cols; i++){
    outputY[i] = malloc(sizeof(double));
}

multiplyMatrices(productInTrans,outputY,Y,rows,cols,1);


freeMatrix(X,rows);
freeMatrix(Y,rows);
freeMatrix(W,k+1);
freeMatrix(copyX,cols);


    int s,m;
    fscanf(file2,"%d",&s);
    fscanf(file2,"%d",&m);

    double **Xprime = malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++){
        Xprime[i] = malloc((s+1)*sizeof(double));
    }

   for (int i = 0; i < m; i++){
        for (int j = 0; j < s+1; j++){
            if (j == 0){
                Xprime[i][j] = 1;
            }else{
                double number;
                fscanf(file2, "%lf", &number);
                Xprime[i][j] = number;
            }
        }
    }


double **Yprime = malloc(m*sizeof(double *));
for (int i = 0; i < m; i++){
    Yprime[i] = malloc(sizeof(double));
}

multiplyMatrices(Xprime, Yprime, outputY, m, s+1, 1);

for (int i = 0; i < m; i++){
    double price = Yprime[i][0];
    printf("%.0f\n", price);
}


freeMatrix(Xprime,m);
freeMatrix(Yprime,m);
freeMatrix(productXsubT,rows);


fclose(file1);
fclose(file2);

return 0;
}
