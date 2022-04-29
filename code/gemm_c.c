// BLAS is an acronym for Basic Linear Algebra Subroutines. As the name indicates, it contains subprograms for basic operations on vectors and matrices
// In this program we will implement the level 3 function from the BLAS library : general matrix multiplication (GEMM) using the programming language "Halide"
// this function computes : alpha*A*B + betha*C such as :
// A is a matrix of (n,m) dimension
// B is a matrix of (m,k) dimension
// C is a matrix of (n,k) dimension


// General Matrix Multiply (GEMM) is a common algorithm in linear algebra, machine learning, statistics, and many other domains.  
// It provides a more interesting trade-off space
// GEMMs (General Matrix Multiplications) are a fundamental building block for many operations in neural networks, 
// for example fully-connected layers, recurrent layers such as RNNs, LSTMs or GRUs, and convolutional layers. 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    
    // Initialization of matrices A, B and C.
 
    int A[5][3] = {
        {4, 12, 8},
        {9, 6, 9},
        {11, 5, 1},
        {1, 13, 4},
        {6, 4, 16},
    };

    int B[3][4] = {
        {3, 1, 5, 6},
        {5, 13, 7, 3},
        {8, 15, 8, 2},
    };

    int C[5][4] = {
        {4, 15, 7, 8},
        {6, 2, 3, 4},
        {8, 16, 1, 2},
        {1, 2, 5, 11},
        {6, 14, 3, 3},
    };

    // Calucating the dimensions of matrix
    int A_height = sizeof(A) / sizeof(A[0]);
    int A_width = sizeof(A[0]) / sizeof(int);
    int B_height = sizeof(B) / sizeof(B[0]);
    int B_width = sizeof(B[0]) / sizeof(int);
    int C_height= sizeof(C) / sizeof(C[0]);
    int C_width = sizeof(C[0]) / sizeof(int);

    // First check if the dimensions are consistent otherwise display an error 
    if ((A_width != B_height) && (A_height != C_height) && (B_width != C_width)){
        printf("Error in the dimension of the matrix\n");
        exit(1);
    }

    // Initialization of real numbers 
    int alpha = 4, beta = 3;

    // Declaration of the variables
    char result_string[256];
    int c_result, result_int;
    int failure = 0;
    
    
    // Openning the result file
    FILE *file;
    if ((file = fopen("./data/result_matrix.txt", "r")) == NULL)
    {
        printf("Error when trying to open the result file !\n");
        exit(1);
    }
    
    
    // Check the dimension of the result matrix stored 
    int matrix_result_height = atoi(fgets(result_string, 256, file));
    int matrix_result_width = atoi(fgets(result_string, 256, file));
    
    if ((A_height != matrix_result_height) && (B_width != matrix_result_width)) {
        printf("Incorrect matrix dimension with the matrix stored \n");
        exit(1);
    }
    
    // Calculate each element of the resulting matrix and comparing the result with the matrix stored
    printf("Cechking process using C program\n");
    for (int i = 0; i < A_height; i++){
        for (int j = 0; j < B_width; j++){
            c_result = 0;
            
            for (int k = 0; k < A_width; ++k)
                c_result += A[i][k] * B[k][j];
                
            c_result = alpha * c_result + beta * C[i][j];
            
            result_int = atoi(fgets(result_string, 256, file));
            
            if (c_result != result_int){
                printf("The line result_matrix[%d, %d] of the result matrix should have the value %d not %d\n", i+1, j+1, c_result, result_int);
                failure = 1;
            }
        }
    }

    printf("Cechking process completed successfully\n");
    // Printing the result
    if (failure == 0) printf("The GEMM function implemented in Halide works correctly !\n");
    else printf("There are some problems with the Halid implementation because the resulting matrix is not the same in the two programs !\n");
    fclose(file);
    
    return 0;
}

