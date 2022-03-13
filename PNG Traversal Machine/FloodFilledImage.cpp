#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>
#include <queue>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  pngInFloodFill = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) { //why reference?  I can have a reference to virtual class, but I cannot create one based on that. 
  /** @todo [Part 2] */
  theColorPickerVector.push_back(&colorPicker);
  theTraversalVector.push_back(&traversal);

  //why don't make them as the objects of the class?
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.

 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  int size = theColorPickerVector.size();
  PNG picture =  pngInFloodFill; //why this work?
  for (int i = 0; i < size; i++) {
    int j = 0;
    ImageTraversal * thisTravsersal = theTraversalVector[i];
    ColorPicker * thisColorPicker = theColorPickerVector[i];
    animation.addFrame(picture);

    //for (ImageTraversal::Iterator i = thisTravsersal->begin(); i != thisTravsersal->end(); ++i) {
    for (auto point : (*thisTravsersal)) { //为什么他可以把自己变成dfs，好吧他就是能变因为begin和end都是virtual，说明肯定也是调用了的
      //picture.getPixel((*i).x, (*i).y) = thisColorPicker->getColor((*i).x, (*i).y); //color is all set
      picture.getPixel(point.x, point.y) = thisColorPicker->getColor(point.x, point.y);
        j = j + 1;
        if (j % frameInterval == 0) {
          animation.addFrame(picture);
        }
    }
    if (j % frameInterval != 0) {
      animation.addFrame(picture);
    }
  }
  return animation;
}