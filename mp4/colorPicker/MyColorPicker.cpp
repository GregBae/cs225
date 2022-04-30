#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(HSLAPixel color1, HSLAPixel color2): c1(color1), c2(color2){}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
    /* @todo [Part 3] */
    HSLAPixel ret;
    if (x % 10 == 0 && y % 10 == 0){
        ret.h = (c1.h+c2.h)/2;
        ret.s = (c1.s+c2.s)/2;
        ret.l = (c1.l+c2.l)/2;
        ret.a = (c1.a+c2.a)/2;
    }
    else if (x % 5 == 0 && y % 5 == 0){
        ret = c1;
    }
    else{
        ret = c2;
    }
    return ret;
}
