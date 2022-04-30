# xGEMM_Halide

This project implements a BLAS (Basic Linear Algebra Subprograms) BLAS routine using Halide and C and compares the results provided by each program.  
Basic Linear Algebra Subprograms (BLAS) is a specification that prescribes a set of low-level routines for performing common linear algebra operations such as vector addition, scalar multiplication, dot products, linear combinations, and matrix multiplication.

## The BLAS function choiced
This project implements the third level routine from BLAS : **General Matrix Multiply (GEMM)**.  
General Matrix Multiply (GEMM) is a common algorithm in linear algebra, machine learning, statistics, and many other domains. It provides a more interesting trade-off space. GEMMs (General Matrix Multiplications) are a fundamental building block for many operations in neural networks, for example fully-connected layers, recurrent layers such as RNNs, LSTMs or GRUs, and convolutional layers.  
GEMM is defined as the operation C = αAB+βC , with A and B as matrix inputs, α and β as scalar inputs, and C as a pre-existing matrix which is overwritten by the output.  

## Installation of Halide in Linux
I will give a detailed description of all the instructions that will allow the installation of halide from sources.  
### Why installing Halide from sources ?
Installing a program "from source" means installing a program without using a package manager. You compile the source code and copy the binaries to your computer instead. 

***Advantages of installing from sources :***
- You can install the latest version and can always stay updated, whether it be a security patch or a new feature.
- Allows you to trim down the features while installing so as to suit your needs.
- Similarly you can add some features which may not be provided in the binary.
- Install it in a location you wish.
- In case of some software you may provide your hardware specific info for a suitable installation.

### Acquiring and building LLVM 
Building Halide requires a stable version of LLVM.  
***Note:*** I first tried to build llvm15, llvm14, llvm13 and llvm12. But in the four installations, I always had the same error which is the following:
 ```
[ 44%] Linking CXX shared library ../../lib/libLTO.so
/usr/bin/ld : ../../lib/libLLVMARMCodeGen.a(ARMTargetMachine.cpp.o) : in the function "(anonymous namespace)::ARMPassConfig::addPreSched2()" :
ARMTargetMachine.cpp:(.text._ZN12_GLOBALN_113ARMPassConfig12addPreSched2Ev+0x2b8) : undefined reference to " llvm::createARMIndirectThunks() "
/usr/bin/ld : ARMTargetMachine.cpp:(.text._ZN12_GLOBALN_113ARMPassConfig12addPreSched2Ev+0x2cd) : undefined reference to " llvm::createARMSLSHardeningPass() "
/usr/bin/ld : ../../lib/libLLVMARMCodeGen.a(ARMTargetMachine.cpp.o) : in function "LLVMInitializeARMTarget" :
ARMTargetMachine.cpp:(.text.LLVMInitializeARMTarget+0x12d) : undefined reference to "llvm::initializeARMSLSHardeningPass(llvm::PassRegistry&)"
collect2: error: ld returned 1 exit status
make[2]:  [tools/lto/CMakeFiles/LTO.dir/build.make:191 : lib/libLTO.so.13] Error 1
make[1]:  [CMakeFiles/Makefile2:25555 : tools/lto/CMakeFiles/LTO.dir/all] Error 2
make: *** [Makefile:152: all] Error 2
 ```
I contacted a few contributors, they told me that these versions require a lot of memory (16 gb of RAM at least and 32gb is preferable) but I have a laptop with 8 gb of RAM.   
I then tried to install llvm 11.0.0 since this version does not require much memory space and is compatible with the capabilities of my computer. 
After installing llvm 11.0.0 no errors were detected and the installation was successful.

Below, the instructions that allowed me acquiring & building LLVM 11.0.0 :  
*  ```git clone --depth 1 --branch llvmorg-11.0.0 https://github.com/llvm/llvm-project.git```
* ``` 
  cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;lld;clang-tools-extra" \
        -DLLVM_TARGETS_TO_BUILD="X86;ARM;NVPTX;AArch64;Mips;Hexagon" -DLLVM_ENABLE_TERMINFO=OFF \
        -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_ENABLE_EH=ON -DLLVM_ENABLE_RTTI=ON -DLLVM_BUILD_32_BITS=OFF\
        -S llvm-project/llvm -B llvm-build  
   ```
* ```cmake --build llvm-build```
* ```cmake --install llvm-build --prefix llvm-install```
* ```export LLVM_ROOT=$PWD/llvm-install```
* ```export LLVM_CONFIG=$LLVM_ROOT/bin/llvm-config```

### Acquiring and building Halide
I'll provide the instructions to acquire and build halide 11.0.1 since I have installed before the version 11.0.0 of llvm.  
* ```git clone --branch v11.0.1 https://github.com/halide/Halide.git```
* ```cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_DIR=$LLVM_ROOT/lib/cmake/llvm -S . -B buill```
* ```cmake --build build```

## The execution of the script
Follow the instructions below to run the script provided in this project :
* ```git clone https://github.com/Sofianebouaziz1/xGEMM_Halide.git```
* ```cd xGEMM_Halide```
* ```chmod +x script.sh```    

To run script.h you just need to execute the following instruction : 
* ```./script.sh```

***Note:*** You'll have to provide  the absolute or a relative path to the halide folder that contains include and lib folders :
* I have build Halide in ./Halide/build, (I had to change the name of the src folder to lib) so I'll provide the following absolute path : ```/home/sofiane/HALIDE-11/Halide/build```
* If I want to execute this script using the latest version of Halide (using binaries, for the reasons mentioned above) I'll provide the following absolute path : ```/home/sofiane/Halide-14.0.0-x86-64-linux```

If everything goes well, you should obtain the following result :   
```
Please provide the absolute or a relative path to the halide folder that contains include and bin/src folders: /home/sofiane/HALIDE-11/Halide/build
Deleting ./data/result.txt if it exists
[sudo] Mot de passe de sofiane : 
***********************************
Compiling ./code/gemm_halide.cpp...
***********************************
Compiling ./code/gemm_c.c...
***********************************
Executing ./bin/gemm_halide...
Matrix calculation with Halide
Matrix calculation with Halide completed successfully
Saving the result matrix into : ./data/result_matrix.txt 
Saving process completed successfully
***********************************
Executing ./bin/gemm_c...
Cechking process using C program
Cechking process completed successfully
The GEMM function implemented in Halide works correctly !
***********************************
```

