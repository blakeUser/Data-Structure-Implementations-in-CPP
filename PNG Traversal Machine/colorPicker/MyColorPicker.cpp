#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

MyColorPicker::MyColorPicker(HSLAPixel color) : color(color) { }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  color.h = color.h - 28;
  color.l = color.l - y;
  color.s = color.l + y;
  if (color.l > 100) {
    color.l -= 100;
  }
  return color;
}