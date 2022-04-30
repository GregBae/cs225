#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <cmath>
#include <string>



void rotate(std::string inputFile, std::string outputFile) {
    // TODO: Part 2
    PNG image;
    bool success = image.readFromFile(inputFile);

    unsigned int width = image.width();
    unsigned int height = image.height();
    int flag_1 = 0;
    int flag_2;
    if (image.width()%2 == 1){
        width = (image.width()/2)+1;
        flag_1 = 1;
    }
    else{
        width = image.width()/2;
    }
   
    for (unsigned int x=0;x<width;x++){
        flag_2 = 0;
        for (unsigned int y=0;y<height;y++){
            if (flag_1 == 1 && x == width-1 && y == height/2){
                flag_2 = 1;
                break;
            }
            
            HSLAPixel & pixel_1 = image.getPixel(x,y);
            HSLAPixel & pixel_2 = image.getPixel(image.width()-x-1,height-y-1);
            
            double temp_h = pixel_1.h;
            double temp_s = pixel_1.s;
            double temp_a = pixel_1.a;
            double temp_l = pixel_1.l;

            pixel_1.h = pixel_2.h;
            pixel_1.s = pixel_2.s;
            pixel_1.a = pixel_2.a;
            pixel_1.l = pixel_2.l;

            pixel_2.h = temp_h;
            pixel_2.s = temp_s;
            pixel_2.a = temp_a;
            pixel_2.l = temp_l;
        }
        if (flag_2 == 1){
            break;
        }
    }
    success = image.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
    PNG png(width, height);
    // TODO: Part 3
    for (unsigned int x=0;x<width;x++){
        for(unsigned int y=0;y<height;y++){
            HSLAPixel & pixel = png.getPixel(x,y);
            
            pixel.h = 0;
            pixel.s = 0.8;
            pixel.l = 0.5;
            pixel.a = 0.5;

            if(x<width/2 && y<height/2) {pixel.h = 45;}
            else if (x>=width/2 && y<height/2)  {pixel.h = 135;}
            else if (x>=width/2 && y>=height/2) {pixel.h = 0;}
            else    {pixel.h = 225;}
        } 
    }
    return png;
}
