 g++ src/Chroma-Key.cpp -o build/Chroma-Key.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
 ./build/Chroma-Key.out -i1 image/rila.bmp -i2 image/galaxy.jpg -color
