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
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(BFS* search) {
  search_ = search;
  while (!search_->to_visit_.empty()) {
    search_->to_visit_.pop();
  }
  while (!search_->visiting_.empty()) {
    search_->visiting_.pop();
  }
  search_->push(start_);
}

ImageTraversal::Iterator::Iterator(DFS* search) {
  search_ = search;
  while (!search_->to_visit_.empty()) {
    search_->to_visit_.pop();
  }
  while (!search_->visiting_.empty()) {
    search_->visiting_.pop();
  }
  search_->push(start_);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point pt = pop();
  HSLAPixel& pixel1 = png_.getPixel(pt.x,pt.y);
  if (pt.x<png_.width()-1) {
    HSLAPixel& pixel2 = png_.getPixel(pt.x+1,pt.y);
    if (calculateDelta(pixel1,pixel2)>=tolerance_ && std::find(visited_.begin(),visited_.end(),pixel2)!=visited_.end()) {
      add(Point(pt.x+1,pt.y));
    }
  if (pt.y<png_.height()-1) {
    HSLAPixel& pixel2 = png_.getPixel(pt.x,pt.y+1);
    if (calculateDelta(pixel1,pixel2)>=tolerance_ && std::find(visited_.begin(),visited_.end(),pixel2)!=visited_.end()) {
      add(Point(pt.x,pt.y+1));
    }
  if (pt.x>0) {
    HSLAPixel& pixel2 = png_.getPixel(pt.x-1,pt.y);
    if (calculateDelta(pixel1,pixel2)>=tolerance_ && std::find(visited_.begin(),visited_.end(),pixel2)!=visited_.end()) {
      add(Point(pt.x-1,pt.y));
    }
  if (pt.y>0) {
    HSLAPixel& pixel2 = png_.getPixel(pt.x,pt.y-1);
    if (calculateDelta(pixel1,pixel2)>=tolerance_ && std::find(visited_.begin(),visited_.end(),pixel2)!=visited_.end()) {
      add(Point(pt.x,pt.y-1));
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
  return peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return empty_ != other.empty_;
}

