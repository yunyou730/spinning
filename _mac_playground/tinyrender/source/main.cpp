#include <iostream>
#include "../source/tgaimage.h"
#include "renderer.hpp"

const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);

int main(int argc, const char * argv[]) {
    
    TGAImage image(100,100,TGAImage::RGB);
    image.set(52,41,red);
    
    
    line(image,red,0,0,80,30);
    line(image,white,80,30,0,0);
    
    line(image,white,0,0,20,100);
    line(image,red,20,100,0,0);
    
//    img.flip_vertically();
    image.write_tga_file("output.tga");

    return 0;
}
