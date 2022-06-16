 g++ src/labeling.cpp -o build/labeling.out `pkg-config --cflags opencv` `pkg-config --libs opencv`
 ./build/labeling.out -i image/spiral-003.bmp
