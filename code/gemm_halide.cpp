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

// The only Halide header file we need is Halide.h. It includes all of Halide.
#include "Halide.h"

// To save the result in a file
#include <fstream>
#include <iostream>

// We'll also include stdio for printf.
#include <stdio.h>

// Avoid writing the namespace
using namespace std;
using namespace Halide;

int main(int argc, char **argv)
{
    
    // Initialization of matrices A, B and C.
 
    int a[5][3] = {
        {4, 12, 8},
        {9, 6, 9},
        {11, 5, 1},
        {1, 13, 4},
        {6, 4, 16},
    };

    int b[3][4] = {
        {3, 1, 5, 6},
        {5, 13, 7, 3},
        {8, 15, 8, 2},
    };

    int c[5][4] = {
        {4, 15, 7, 8},
        {6, 2, 3, 4},
        {8, 16, 1, 2},
        {1, 2, 5, 11},
        {6, 14, 3, 3},
    };

    // Declaration of the buffers to store the matrices initialized beforehand
    Buffer<int> A(a);  //A(n,m)
    Buffer<int> B(b);  //B(m,k) 
    Buffer<int> C(c);  //C(n,k)

    // First check if the dimensions are consistent otherwise display an error 
    if ((A.width() != B.height()) && (A.height() != C.height()) && (B.width() != C.width())){
        printf("Error in the dimension of the matrix\n");
        exit(1);
    }

    // Initialization of real numbers 
    int alpha = 4, beta = 3;

    // Declaration of the gemm function. It's a pure function that defines what value each element of the resultant matrix
    Func gemm;

    // Declaration of two var objects to use as variables in the definition of our Func gemv (x represent the lines and y represent the columns)
    Var x,y;

    // Declaration of a reduction domain (i takes the values from 0 to the number of columns of the matrix B - 1 (k-1))
    RDom k(0, A.width());

    //Now we'll add a definition for our Func object. Each element (x,y) of the result matrix recieve : alpha * sum(A(x, d) * B(d,k)) + beta * C(x,y);  
    gemm(x,y) = alpha * sum(A(k, y) * B(x,k)) + beta * C(x,y);

    printf("Matrix calculation with Halid\n");
    // Realizing the function
    Buffer<int> result_matrix = gemm.realize({B.width(), A.height()});

    printf("Matrix calculation with Halid completed successfully\n");

    // Save the result in a file to verify its correctness with a C program 
    printf("Saving the result matrix into : ./data/result_matrix.txt \n");

    ofstream output_file("./data/result_matrix.txt");

    // Storing the dimensions of the result matrix
    output_file << result_matrix.height() << "\n";
    output_file << result_matrix.width() << "\n";

    // Saving each element of the resulting matrix in the file
    for (int l = 0; l < result_matrix.height(); l++)
    {
	for (int m = 0; m < result_matrix.width(); m++)
	{
	     output_file << result_matrix(m, l) << "\n";
	}
    }

    output_file.close();

    printf("Saving process completed successfully\n");

    return 0;
}

