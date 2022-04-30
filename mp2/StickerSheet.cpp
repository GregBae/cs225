#include "StickerSheet.h"
#include <iostream>

using namespace std;

void StickerSheet::copy_(const StickerSheet & other){
    stickers = new Image*[other.max_stickers];
    x_ = new unsigned[other.max_stickers];
    y_ = new unsigned[other.max_stickers];

    for (unsigned i=0; i<other.n_layers; i++){
        stickers[i] = new Image(other.stickers[i]->width(),other.stickers[i]->height());
        for (unsigned x=0;x<other.stickers[i]->width();x++){
            for (unsigned y=0;y<other.stickers[i]->height();y++){
                HSLAPixel & pixel1 = stickers[i]->getPixel(x,y);
                HSLAPixel & pixel2 = other.stickers[i]->getPixel(x,y);

                pixel1.h = pixel2.h;
                pixel1.s = pixel2.s;
                pixel1.l = pixel2.l;
                pixel1.a = pixel2.a;
            }
        }
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
    }

    base = other.base;
    max_stickers = other.max_stickers;
    n_layers = other.n_layers;
}

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    base = picture;
    stickers = new Image*[max];
    x_ = new unsigned[max];
    y_ = new unsigned[max];
    max_stickers = max;
    n_layers = 0;
}

StickerSheet::~StickerSheet(){
    delete [] x_;
    delete [] y_;

    for (unsigned i=0; i<n_layers; i++){
        if (stickers[i]!=NULL)
            delete stickers[i];
    }
    delete [] stickers;
}

StickerSheet::StickerSheet(const StickerSheet &other){
    copy_(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    if  (this != &other){
        copy_(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){

    if (max_stickers == max) return;

    Image ** temp = new Image*[max];
    unsigned * x_temp = new unsigned[max];
    unsigned * y_temp = new unsigned[max];

    if (max < max_stickers){
        for (unsigned i=0; i<max; i++){
            temp[i] = stickers[i];
            x_temp[i] = x_[i];
            y_temp[i] = y_[i];
        }
        if(n_layers>max){
            for (unsigned i=max; i<n_layers; i++){
                if (stickers[i] != NULL)
                    delete stickers[i];    
                stickers[i] = NULL;
            }
            n_layers = max;
        }
    }
    else{
        for (unsigned i=0; i<n_layers; i++){
            temp[i] = stickers[i];
            x_temp[i] = x_[i];
            y_temp[i] = y_[i];
        }
    }

    max_stickers = max;
    delete [] stickers;
    delete [] x_;
    delete [] y_;
    stickers = temp;
    x_ = x_temp;
    y_ = y_temp;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if (n_layers >= max_stickers){
        return -1;
    }
    else{
        Image * newImage = new Image(sticker.width(),sticker.height());
        for (unsigned i=0;i<sticker.width();i++){
            for (unsigned j=0;j<sticker.height();j++){
                HSLAPixel & pixel_1 = sticker.getPixel(i,j);
                HSLAPixel & pixel_2 = newImage->getPixel(i,j);

                pixel_2.a = pixel_1.a;
                pixel_2.l = pixel_1.l;
                pixel_2.s = pixel_1.s;
                pixel_2.h = pixel_1.h;
            }
        }
        stickers[n_layers] = newImage;
        x_[n_layers] = x;
        y_[n_layers] = y;
        n_layers++;
        return n_layers-1;
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (n_layers > index){
        x_[index] = x;
        y_[index] = y;
        return true;
    }
    return false;
}

void StickerSheet::removeSticker(unsigned index){
    if (n_layers > index){
        if (index == n_layers-1){
            if(stickers[index] != NULL)
                delete stickers[index];
            stickers[index] = NULL;
            n_layers--;
        }
        else{
            if (stickers[index] != NULL){
                delete stickers[index];
                stickers[index] = NULL;
            }
            for (unsigned i=index; i<n_layers-1; i++){
                stickers[i] = stickers[i+1];
                x_[i] = x_[i+1];
                y_[i] = y_[i+1];
            }
            stickers[n_layers] = NULL;
            n_layers--;
        }
    }
}

Image * StickerSheet::getSticker(unsigned index) const{
    if (n_layers > index){
        return stickers[index];
    }
    return NULL;
}

Image StickerSheet::render() const {

    Image result = base;

    unsigned int base_w = result.width();
    unsigned int base_h = result.height();

    for (unsigned i=0; i<n_layers; i++){
        unsigned stick_w = stickers[i]->width();
        unsigned stick_h = stickers[i]->height();

        if (base_w < x_[i]+stick_w+1)
            base_w = x_[i]+stick_w+1;
        if (base_h < y_[i]+stick_h+1)
            base_h = y_[i]+stick_h+1;

        result.resize(base_w,base_h);

        for (unsigned w = x_[i]; w<x_[i]+stick_w; w++){
            for (unsigned h = y_[i]; h<y_[i]+stick_h; h++){
                HSLAPixel & pixel1 = result.getPixel(w,h);
                HSLAPixel & pixel2 = stickers[i]->getPixel(w-x_[i],h-y_[i]);

                if (pixel2.a != 0){
                    pixel1.a = pixel2.a;
                    pixel1.h = pixel2.h;
                    pixel1.l = pixel2.l;
                    pixel1.s = pixel2.s;
                }
            }
        }
    }
    return result;
}
