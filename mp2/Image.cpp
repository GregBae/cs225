#include "Image.h"
#include <cmath>
#include <iostream>
using namespace cs225;
using namespace std;

Image::Image() : PNG() {}
Image::Image(unsigned int w, unsigned int h) : PNG(w,h) {}
void Image::lighten(){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l += 0.1;

            if (pixel.l > 1)
                pixel.l =1;
        }
    }
}

void Image::lighten(double amount){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l += amount;

            if (pixel.l > 1)
                pixel.l =1;
        }
    }
}

void Image::darken(){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l -= 0.1;

            if (pixel.l < 0)
                pixel.l =0;
        }
    }
}

void Image::darken(double amount){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l -= amount;

            if (pixel.l <0)
                pixel.l =0;
        }
    }
}

void Image::saturate(){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s += 0.1;

            if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::saturate(double amount){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s += amount;

            if (pixel.s > 1)
                pixel.s = 1;
        }
    }
}

void Image::desaturate(){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s -= 0.1;

            if (pixel.s < 0)
                pixel.s = 0;
        }
    }
}

void Image::desaturate(double amount){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s -= amount;

            if (pixel.s < 0)
                pixel.s = 0;
        }
    }
}

void Image::grayscale(){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for(unsigned int x=0;x<width;x++){
        for(unsigned y=0;y<height;y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            double result = fmod((pixel.h + degrees), 360.0);
            if (result < 0){
                result += 360.0;
            }
            //cout << result << endl;

            pixel.h = result;
        }
    }
}

void Image::illinify(){
    unsigned int width = this->width();
    unsigned int height = this->height();

    for (unsigned int x = 0; x<width; x++){
        for (unsigned int y = 0; y<height; y++){
            HSLAPixel & pixel = this->getPixel(x,y);

            double blue_hue_diff;
            double orange_hue_diff;

            blue_hue_diff = abs(pixel.h - 216);
            if (blue_hue_diff >= 180){
                blue_hue_diff = 360 - blue_hue_diff;
            }

            orange_hue_diff = abs(pixel.h - 11);
            if (orange_hue_diff>=180){
                orange_hue_diff = 360 - orange_hue_diff;
            }

            if(orange_hue_diff > blue_hue_diff){
                pixel.h = 216;
            }
            else{
                pixel.h = 11;
            }
        }
    }
}

void shrink_new_val(double lower_x,double upper_x,double lower_y,double upper_y,Image &orig,
    Image  &copy, int x, int y){
    double new_h=0.0;
    double new_s=0.0;
    double new_l=0.0;
    double new_a=0.0;
    double count=0.0;

    for (int i = lower_x;i<upper_x;i++){
        for (int j = lower_y;j<upper_y;j++){
            HSLAPixel & orig_pix = orig.getPixel(i,j);
            new_h+=orig_pix.h;
            new_s+=orig_pix.s;
            new_l+=orig_pix.l;
            new_a+=orig_pix.a;
            count++;
        }
    }

    HSLAPixel & new_pix = copy.getPixel(x,y);
    new_pix.h = new_h/count;
    new_pix.s = new_s/count;
    new_pix.l = new_l/count;
    new_pix.a = new_a/count;
}

void exp_new_val(int lower_x,int upper_x,int lower_y,int upper_y,
    Image &orig,Image &copy,int x,int y){
    HSLAPixel & ref_pix = orig.getPixel(x,y);
    double ref_h = ref_pix.h;
    double ref_s = ref_pix.s;
    double ref_l = ref_pix.l;
    double ref_a = ref_pix.a;

    for(int i=lower_x;i<upper_x;i++){
        for(int j=lower_y;j<upper_y;j++){
            HSLAPixel & new_pix = copy.getPixel(i,j);
            new_pix.h = ref_h;
            new_pix.s = ref_s;
            new_pix.l = ref_l;
            new_pix.a = ref_a;
        }
    }
}
void Image::scale(double factor){
    if (factor < 1) {
        int orig_x = this->width();
        int orig_y = this->height();
        double scaled_x = this->width() * factor;
        double scaled_y = this->height() * factor;
        double actual_x, actual_y, lower_x, upper_x, lower_y, upper_y;
        Image &curr = *this;
        Image copy = Image((int)scaled_x,(int)scaled_y);
        Image &temp = copy;

        for (int i = 0;i < (int)scaled_x;i++){
            actual_x = i * (1/factor);
            for (int j =0;j < (int)scaled_y;j++){
                actual_y = j * (1/factor);

                lower_x = actual_x - ((1/factor)/2);
                lower_x = round(lower_x);
                if(lower_x < 0)
                    lower_x = 0;

                upper_x = actual_x + ((1/factor)/2);
                upper_x = round(upper_x);
                if(upper_x > orig_x-1)
                    upper_x = orig_x - 1;

                lower_y = actual_y - ((1/factor)/2);
                lower_y = round(lower_y);
                if(lower_y < 0)
                    lower_y = 0;

                upper_y = actual_y + ((1/factor)/2);
                upper_y = round(upper_y);
                if(upper_y > orig_y - 1)
                    upper_y = orig_y;

                shrink_new_val(lower_x,upper_x,lower_y,upper_y,curr,temp,i,j);
            }
        }
        *this = temp;
    }
    else if (factor > 1){
        int orig_x = this->width();
        int orig_y = this->height();
        int new_x = orig_x * factor;
        int new_y = orig_y * factor;
        Image &curr = *this;
        Image copy = Image(new_x,new_y);
        Image &temp = copy;

        for(int i=0;i<orig_x;i++){
            for(int j=0;j<orig_y;j++){
                int upper_x,upper_y,lower_x,lower_y;
                lower_x = round(i*factor);
                upper_x = round((i+1)*factor);
                lower_y = round(j*factor);
                upper_y = round((j+1)*factor);

                if (upper_x > new_x -1)
                    upper_x = new_x - 1;
                if (upper_y > new_y -1)
                    upper_y = new_y -1;

                exp_new_val(lower_x,upper_x,lower_y,upper_y,curr,temp,i,j);
            }
        }
        *this = temp;
    }
}

void Image::scale(unsigned w, unsigned h){
    double ratio_x = ((double)w)/((double)(this->width()));
    double ratio_y = ((double)h)/((double)(this->height()));

    if(ratio_x<ratio_y){
        this->scale(ratio_x);
    }
    else if (ratio_x>ratio_y){
        this->scale(ratio_y);
    }
    else{
        this->scale(ratio_x);
    }
}
