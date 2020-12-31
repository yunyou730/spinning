#include <iostream>
#include "../source/tgaimage.h"

const TGAColor whilte = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);

int main(int argc, const char * argv[]) {
    
    TGAImage img(100,100,TGAImage::RGB);
    img.set(52,41,red);
    img.flip_vertically();
    img.write_tga_file("output.tga");

    return 0;
}
