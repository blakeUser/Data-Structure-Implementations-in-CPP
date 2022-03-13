#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm> 
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include <vector>

#include "ImageTraversal.h"
using namespace std;

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
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  imagetraversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * imagetraversal, Point start, PNG picture, double tolerance) {
  imagetraversal_ = imagetraversal; //this is stack
  start_ = start;
  png_ = picture;
  tolerance_ = tolerance;
  current = start_;
  vect = vector< vector<int> > (png_.width(), vector <int> (png_.height(), 0));
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //Current is visited 
  int x = current.x;
  int y = current.y;
  vect[x][y] = 1;
  if (current.x + 1 < this->png_.width()) {
    imagetraversal_->add(Point(x + 1, y)); //right
  }
  if (current.y + 1 < this->png_.height()) {
    imagetraversal_->add(Point(x, y + 1)); //right
  }
  if (x - 1 >= 0) {
    imagetraversal_->add(Point(x - 1, y)); //left
  }
  if (y - 1 >= 0) {
    imagetraversal_->add(Point(x, y - 1));//down
  } 
  
  while (!imagetraversal_->empty()) {
    Point point = imagetraversal_->pop();
    HSLAPixel startPoint = png_.getPixel(start_.x, start_.y);
    HSLAPixel currentPixel = png_.getPixel(point.x, point.y);
    if (calculateDelta(currentPixel, startPoint) < tolerance_ && vect[point.x][point.y] != 1) {
      current = point;
      break;
    }
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

  //This part should be good. 
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
   bool thisEmpty = false; 
   bool otherEmpty = false;
   if (imagetraversal_ == NULL) { thisEmpty = true; }
   if (other.imagetraversal_ == NULL) { otherEmpty = true; }
   if (!thisEmpty)  { thisEmpty = imagetraversal_->empty(); }
   if (!otherEmpty) { otherEmpty = other.imagetraversal_->empty(); }
   if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
   else if ((!thisEmpty)&&(!otherEmpty)) return (imagetraversal_ != other.imagetraversal_);
   else return true;
}
