# xGEMM_Halide

This project implements a BLAS (Basic Linear Algebra Subprograms) BLAS routine using C and Halide and comparing the results provided by each program.  
Basic Linear Algebra Subprograms (BLAS) is a specification that prescribes a set of low-level routines for performing common linear algebra operations such as vector addition, scalar multiplication, dot products, linear combinations, and matrix multiplication.

## The BLAS function choiced
This project implements the third level routine from BLAS : **General Matrix Multiply (GEMM)**.  
General Matrix Multiply (GEMM) is a common algorithm in linear algebra, machine learning, statistics, and many other domains.It provides a more interesting trade-off space. GEMMs (General Matrix Multiplications) are a fundamental building block for many operations in neural networks, for example fully-connected layers, recurrent layers such as RNNs, LSTMs or GRUs, and convolutional layers.  
GEMM is defined as the operation C = αAB+βC , with A and B as matrix inputs, α and β as scalar inputs, and C as a pre-existing matrix which is overwritten by the output.  

## Installation of Halide in Linux
I will give a detailed description of all the instructions that will allow you to install halide from sources.  
### Why installing Halide from sources ?
Installing a program "from source" means installing a program without using a package manager. You compile the source code and copy the binaries to your computer instead. 

***Advantages of installing from source :***
- You can install the latest version and can always stay updated, whether it be a security patch or a new feature.
- Allows you to trim down the features while installing so as to suit your needs.
- Similarly you can add some features which may not be provided in the binary.
- Install it in a location you wish.
- In case of some software you may provide your hardware specific info for a suitable installation.
