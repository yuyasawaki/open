 g++ src/pcolor.cpp -o build/pcolor.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
 ./build/pcolor.out -i image/Lenna256x256.bmp
