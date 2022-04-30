#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal * obj){
    image = PNG();
    this->obj = obj;
    img_w = 0;
    img_h =0;
}
ImageTraversal::Iterator::Iterator(ImageTraversal * obj, const Point & start,
double tolerance, const PNG & image){
    /** @todo [Part 1] */
    this->obj = obj;
    this->start = start;
    this->curr = start;
    this->tolerance = tolerance;
    this->image = image;
    img_w = this->image.width();
    img_h = this->image.height();
    track = new bool*[img_w];
    for (unsigned int i=0;i<img_w;i++){
        track[i] = new bool[img_h];
        for (unsigned int j=0;j<img_h;j++){
            track[i][j] = false;
        }
    }
    track[this->start.x][this->start.y] = true;
}

/*virtual ImageTraversal::Iterator::~Iterator(){
    for (unsigned int i=0;i<img_h;i++){
        delete [] track[i];
    }
    delete [] track;
    delete obj;
}
*/
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */

    HSLAPixel & pixel = image.getPixel(start.x,start.y);
    if(curr.x+1 < img_w && calculateDelta(pixel,image.getPixel(curr.x+1,curr.y)) < tolerance){
        obj->add(Point(curr.x+1,curr.y));
    }
    if(curr.y+1 < img_h && calculateDelta(pixel,image.getPixel(curr.x,curr.y+1)) < tolerance) {
        obj->add(Point(curr.x,curr.y+1));
    }
    if(curr.x >= 1 && calculateDelta(pixel,image.getPixel(curr.x-1,curr.y)) < tolerance){
        obj->add(Point(curr.x-1,curr.y));
    }
    if(curr.y >= 1 && calculateDelta(pixel,image.getPixel(curr.x,curr.y-1)) < tolerance){
        obj->add(Point(curr.x,curr.y-1));
    }

    if (this->obj->empty()){
        obj = NULL;
        return *this;
    }
    curr = this->obj->pop();
    while (track[curr.x][curr.y] == true){
        if (this->obj->empty()){
            obj = NULL;
            return *this;
        }
        curr = this->obj->pop();
    }
    track[curr.x][curr.y] = true;
    if (this->obj->empty()){
        obj = NULL;
    }
    return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return obj!=nullptr;
}
