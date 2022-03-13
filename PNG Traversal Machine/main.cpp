
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;      png.readFromFile("Yoshi.png");
  FloodFilledImage image(png);
  
  BFS bfs(png, Point(70, 94), 0.2);
  DFS dfs(png, Point(1, 10), 0.2);
  DFS dfs2(png, Point(160, 20), 0.2);
  DFS dfs3(png, Point(1, 160), 0.2);

  HSLAPixel color(113, 1, 0.5);
  HSLAPixel c1(10, 14, 0.6);
  HSLAPixel c2(10, 14, 0.2);

  GridColorPicker grid(c1, c2 , 1);
  MyColorPicker my(color);
  RainbowColorPicker rainbow(0.2);

  image.addFloodFill( bfs, grid );
  image.addFloodFill( dfs2, my);
  image.addFloodFill( dfs, my);
  image.addFloodFill( dfs3, my);
  
  Animation animation = image.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}
