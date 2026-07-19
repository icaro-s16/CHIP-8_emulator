chip8_build(){
    if [[ $1 == [yY] ]]; then
        cmake -DCHIP8_TEST=ON ..
    else 
        cmake ..
    fi
}


echo "WARNING: If you choose a name other than "build/" for your CMake build directory, it will be ignored!"
echo "INFO: Starting build..."

BUILD_TEST=""

read -p "Would you like to enable unit tests? (Y/N):" BUILD_TEST && [[ $BUILD_TEST == [yY] || $BUILD_TEST == [nN] ]] || exit 1

if [ $PWD == build/ ]; then 
    if [ -f CMakeCache.txt ]; then 
        rm -f CMakeCache.txt
    fi 
    chip8_build $BUILD_TEST
elif [ -d build/ ] 
then
    cd build/ || exit 1
    if [ -f CMakeCache.txt ]; then 
        rm -f CMakeCache.txt
    fi 
    chip8_build $BUILD_TEST 
else
    mkdir build/
    cd build/ || exit 1
    chip8_build $BUILD_TEST  
fi 

make


echo "INFO: The binary file was successfully built in the build directory. Run it."