#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image back;
  Image bee1;
  Image bee2;
  Image bee3;
  
  back.readFromFile("attack_dog.png");
  bee1.readFromFile("bee1.png");
  bee2.readFromFile("bee2.png");
  bee3.readFromFile("bee3.png");

  StickerSheet main = StickerSheet(back, 50);
  main.addSticker(bee1, 100, 300);
  main.addSticker(bee1, 100, 400);
  main.addSticker(bee1, 100, 500);
  main.addSticker(bee1, 100, 600);
  main.addSticker(bee1, 100, 700);
  main.addSticker(bee1, 100, 800);
  main.addSticker(bee2, 1200, 600);
  main.addSticker(bee3, 50, 100);
  main.addSticker(bee3, 200, 100);
  main.addSticker(bee3, 350, 100);
  main.addSticker(bee3, 500, 100);
  main.addSticker(bee3, 700, 100);

  Image out = main.render();
  out.writeToFile("myImage.png");

  return 0;
}
