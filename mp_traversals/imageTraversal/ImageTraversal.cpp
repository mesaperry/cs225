#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"
#include "DFS.h"

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
  traversal = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, const PNG png, double tolerance)
  :traversal(traversal), png(png), tolerance(tolerance) {
}

bool ImageTraversal::Iterator::isEmpty() const {
  if (traversal != NULL) { return traversal->empty(); }
  else { return true; }
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point pt = traversal->pop();
  while (std::find(seen.begin(), seen.end(), pt) != seen.end()) {
    pt = traversal->pop();
  }  
  seen.push_back(pt);
  const HSLAPixel& pix1 = png.getPixel(pt.x, pt.y);
  if (pt.x < png.width()-1) {
    Point pt2 = Point(pt.x+1, pt.y);
  	const HSLAPixel& pix2 = png.getPixel(pt2.x, pt2.y);
    if (calculateDelta(pix1, pix2) < tolerance) { traversal->add(pt2); }
  }
  if (pt.y < png.height()-1) {
    Point pt2 = Point(pt.x, pt.y+1);
  	const HSLAPixel& pix2 = png.getPixel(pt2.x, pt2.y);
    if (calculateDelta(pix1, pix2) < tolerance) { traversal->add(pt2); }
  }
  if (pt.x > 0) {
    Point pt2 = Point(pt.x-1, pt.y);
  	const HSLAPixel& pix2 = png.getPixel(pt2.x, pt2.y);
    if (calculateDelta(pix1, pix2) < tolerance) { traversal->add(pt2); }
  }
  if (pt.y > 0) {
    Point pt2 = Point(pt.x, pt.y-1);
  	const HSLAPixel& pix2 = png.getPixel(pt2.x, pt2.y);
    if (calculateDelta(pix1, pix2) < tolerance) { traversal->add(pt2); }
  }
  while (!traversal->empty()) {
    if (std::find(seen.begin(), seen.end(), traversal->peek()) == seen.end()) {
      break;
    }
    traversal->pop();
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
  return traversal->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool this_empty =  isEmpty();
  bool other_empty = other.isEmpty();

  if (this_empty && other_empty) { return false; }
  else if (!this_empty && !other_empty) { return false; }
  else { return true; }
}

