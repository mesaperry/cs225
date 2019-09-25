
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;
using std::abs;
using std::cout;
using std::endl;


StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  picture_ = picture;
  max_ = max;
  stickers_ = new Image[max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  exist_ = new bool[max_];
  for (unsigned i = 0; i < max; i++) { exist_[i] = false; }
}

StickerSheet::~StickerSheet() {
  _clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  if (this != &other) { _copy(other); }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
  if (this != &other) { _copy(other); }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  Image* new_stickers = new Image[max];
  unsigned* new_x = new unsigned[max];
  unsigned* new_y = new unsigned[max];
  bool* new_exist = new bool[max];
  for (unsigned i = 0; i < fmin(max, max_); i++) {
    new_stickers[i] = stickers_[i];
    new_x[i] = x_[i];
    new_y[i] = y_[i];
    new_exist[i] = exist_[i];
  }
  _clear();

  max_ = max;
  stickers_ = new_stickers;
  x_ = new_x;
  y_ = new_y;
  exist_ = new_exist;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  for (unsigned i = 0; i < max_; i++) {
    if (!exist_[i]) {
      stickers_[i] = sticker;
      x_[i] = x;
      y_[i] = y;
      exist_[i] = true;
      return i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (!exist_[index]) { return false; }

  x_[index] = x;
  y_[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  exist_[index] = false;
}

Image* StickerSheet::getSticker(unsigned index) {
  if (!exist_[index]) { return NULL; }
  return &stickers_[index];
}

Image StickerSheet::render() const {
  Image master = Image(picture_);
  for (unsigned i = 0; i < max_; i++) {
    if (!exist_[i]) { continue; }

    if (stickers_[i].width()+x_[i]>master.width()) { master.scale(float(stickers_[i].width()+x_[i]+1)/float(master.width())); }
    if (stickers_[i].height()+y_[i]>master.height()) { master.scale(float(stickers_[i].height()+y_[i]+1)/float(master.height())); }

    for (unsigned x = 0; x < stickers_[i].width(); x++) {
      for (unsigned y = 0; y < stickers_[i].height(); y++) {
        unsigned abs_x = x + x_[i];
        unsigned abs_y = y + y_[i];
        HSLAPixel &sticker_pixel = stickers_[i].getPixel(x, y);
        if (sticker_pixel.a!=0) {
          HSLAPixel &master_pixel = master.getPixel(abs_x, abs_y);
          master_pixel = sticker_pixel;
        }
      }
    }
  }
  return master;
}

void StickerSheet::_clear() {
  delete[] stickers_;
  delete[] x_;
  delete[] y_;
  delete[] exist_;
}

void StickerSheet::_copy(StickerSheet const & other) {
  _clear();
  picture_ = other.picture_;
  max_ = other.max_;
  stickers_ = new Image[max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  exist_ = new bool[max_];
  for (unsigned i = 0; i < max_; i++) {
    stickers_[i] = other.stickers_[i];
    x_[i] = other.x_[i];
    y_[i] = other.y_[i];
    exist_[i] = other.exist_[i];
  }
}
