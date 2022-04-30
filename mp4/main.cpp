
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
  PNG png;
  png.readFromFile("Illinois.png");

  FloodFilledImage image(png);
  DFS dfs(png, Point(50.0,50.0),0.2);
  BFS bfs(png, Point(0.0,0.0),0.3);
  HSLAPixel colorblue(234,0.87,0.50,1);
  HSLAPixel colorred(8,0.87,0.50,1);
  HSLAPixel colorgreen(126,0.72,0.5,1);

  MyColorPicker first(colorblue,colorred);
  MyColorPicker second(colorgreen,colorblue);
  image.addFloodFill(bfs,first);
  image.addFloodFill(dfs,second);
  Animation animation = image.animate(500);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
