read -p "Please provide the absolute or a relative path to the halide folder that contains include and bin/src folders: " path
echo "Deleting ./data/result.txt if it exists"
sudo rm -f ./result/result.txt

echo "***********************************"

echo "Compiling ./code/gemm_halide.cpp..."
g++ ./code/gemm_halide.cpp -g -I ${path}/include -L ${path}/src -I ${path}/tools  -lHalide -o ./bin/gemm_halide -std=c++17

echo "***********************************"

echo "Compiling ./code/gemm_c.c..."
gcc ./code/gemm_c.c -o ./bin/gemm_c

echo "***********************************"

echo "Executing ./bin/gemm_halide..."
LD_LIBRARY_PATH=${path}/src  ./bin/gemm_halide


echo "***********************************"

echo "Executing./bin/gemm_c..."
./bin/gemm_c

echo "***********************************"
