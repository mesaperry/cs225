/**
 * @file Image.cpp
 *
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/HSLAPixel.h"
#include "Image.h"

using std::abs;
using cs225::HSLAPixel;
using std::cout;
using std::endl;

void Image::lighten(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = pixel.l + .1;
      pixel.l = fmin(pixel.l, 1);
    }
  }
}

void Image::lighten(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = pixel.l + amount;
      pixel.l = fmin(pixel.l, 1);
    }
  }
}

void Image::darken(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = pixel.l - .1;
      pixel.l = fmax(pixel.l, 0);
    }
  }
}

void Image::darken(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l = pixel.l - amount;
      pixel.l = fmax(pixel.l, 0);
    }
  }
}

void Image::saturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = pixel.s + .1;
      pixel.s = fmin(pixel.s, 1);
    }
  }
}

void Image::saturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = pixel.s + amount;
      pixel.s = fmin(pixel.s, 1);
    }
  }
}

void Image::desaturate(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = pixel.s - .1;
      pixel.s = fmax(pixel.s, 0);
    }
  }
}

void Image::desaturate(double amount){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = pixel.s - amount;
      pixel.s = fmax(pixel.s, 0);
    }
  }
}

void Image::grayscale(){
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.h += degrees;
      if (pixel.h > 360){
        pixel.h -= 360;
      }
      else if (pixel.h < 0){
        pixel.h += 360;
      }
    }
  }
}

void Image::illinify() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      double orange = 11;
      double blue = 216; 
      double o_dist = fmin(abs(orange-pixel.h), 360-abs(orange-pixel.h));
      double b_dist = fmin(abs(blue-pixel.h), 360-abs(blue-pixel.h));
      if (o_dist <= b_dist) {
        pixel.h = orange;
      }
      else if (b_dist < o_dist) {
        pixel.h = blue;
      }
    }
  }
}

void Image::scale(double factor){
  double o_width = width();
  double o_height = height();

  if (factor > 1) {
    resize(width()*factor, height()*factor);
    for (unsigned x = width()-1; x < width(); x--) {
	    for (unsigned y = height()-1; y < height(); y--) {
	      HSLAPixel & s_pixel = getPixel(x, y);
	      HSLAPixel & o_pixel = getPixel(x/factor, y/factor);
	      s_pixel = o_pixel;
	    }
    }
  }
  else if (factor < 1) {
    for (unsigned x = 0; x < width()*factor; x++) {
      for (unsigned y = 0; y < height()*factor; y++) {
	      HSLAPixel & s_pixel = getPixel(x, y);
	      HSLAPixel & o_pixel = getPixel(x/factor, y/factor);
	      s_pixel = o_pixel;
	    }
    }
    resize(width()*factor, height()*factor);
  }
}

void Image::scale(unsigned w, unsigned h){
  double factor_w = w / width();
  double factor_h = h / height();
  double factor = fmin(factor_w, factor_h);
  scale(factor);
}
