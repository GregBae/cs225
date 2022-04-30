#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma; alma.readFromFile("alma.png");
  Image s1; s1.readFromFile("i.png");
  Image s2; s2.readFromFile("i.png");
  Image s3; s3.readFromFile("i.png");

  s1.scale(0.5);
  s2.scale(0.5);
  s3.scale(0.5);

  StickerSheet base(alma, 3);

  base.addSticker(s1,0,0);
  base.addSticker(s2,alma.width()/2-1,alma.height()/2-1);
  base.addSticker(s3,alma.width()-1,alma.height()-1);

  base.render().writeToFile("myImage.png");

  return 0;
}
