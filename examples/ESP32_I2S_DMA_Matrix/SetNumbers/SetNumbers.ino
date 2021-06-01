/*******************************************************************
    Example that displays numbers using an ESP32
 *                                                                 *
    Written by Brian Lough (witnessmenow)
    https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA
 *******************************************************************/

// ----------------------------
// Standard Libraries - Already Installed if you have ESP32 set up
// ----------------------------

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <ESP32-RGB64x32MatrixPanel-I2S-DMA.h>
// This is the library for interfacing with the display

// Can be installed from the library manager (Search for "ESP32 64x32 LED MATRIX")
// https://github.com/mrfaptastic/ESP32-RGB64x32MatrixPanel-I2S-DMA

// Adafruit GFX library is a dependancy for the matrix Library
// Can be installed from the library manager
// https://github.com/adafruit/Adafruit-GFX-Library

#include <TetrisMatrixDraw.h>
// This library!
// https://github.com/toblum/TetrisAnimation


unsigned long animationDue = 0;
unsigned long animationDelay = 100; // Smaller number == faster
bool finishedAnimating = false;

RGB64x32MatrixPanel_I2S_DMA dma_display(true); //true enables the double buffer

// Some standard colors
uint16_t myRED = dma_display.color565(255, 0, 0);
uint16_t myGREEN = dma_display.color565(0, 255, 0);
uint16_t myBLUE = dma_display.color565(0, 0, 255);
uint16_t myWHITE = dma_display.color565(255, 255, 255);
uint16_t myYELLOW = dma_display.color565(255, 255, 0);
uint16_t myCYAN = dma_display.color565(0, 255, 255);
uint16_t myMAGENTA = dma_display.color565(255, 0, 255);
uint16_t myBLACK = dma_display.color565(0, 0, 0);

uint16_t myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

TetrisMatrixDraw tetris(dma_display);

void animationHandler()
{
  // Not clearing the display and redrawing it when you
  // dont need to
  if (!finishedAnimating) {
    dma_display.flipDMABuffer();
    dma_display.fillScreen(myBLACK);
    finishedAnimating = tetris.drawNumbers(0, 24);
    //finishedAnimating = tetris.drawNumbers(0, 48, false, 32);
    dma_display.showDMABuffer();
  }

}

void drawIntro(int x = 0, int y = 0)
{
  tetris.drawChar("T", x, y, myCYAN);
  tetris.drawChar("e", x + 5, y, myMAGENTA);
  tetris.drawChar("t", x + 11, y, myYELLOW);
  tetris.drawChar("r", x + 17, y, myGREEN);
  tetris.drawChar("i", x + 22, y, myBLUE);
  tetris.drawChar("s", x + 27, y, myRED);

  tetris.drawChar("T", x + 6, y + 9, myRED);
  tetris.drawChar("i", x + 11, y + 9, myWHITE);
  tetris.drawChar("m", x + 16, y + 9, myCYAN);
  tetris.drawChar("e", x + 22, y + 9, myMAGENTA);
}

void setup() {
  Serial.begin(115200);
  // Intialise display library
  dma_display.begin();
  dma_display.fillScreen(myBLACK);

  dma_display.flipDMABuffer();
  dma_display.fillScreen(myBLACK);
  drawIntro(10, 10);
  dma_display.showDMABuffer();
  delay(2000);

  finishedAnimating = false;
  tetris.setNumbers(123456789);

}


void loop() {
  unsigned long now = millis();
  if (now > animationDue) {
    animationHandler();
    animationDue = now + animationDelay;
  }

  if (finishedAnimating) {
    delay(2000);
    if (tetris.scale == 1)
    {
      // Scale will make each tetris block bigger
      // It needs to be called before you do tetris.setNumbers
      // It will persist for future setNumbers
      tetris.scale = 2; // Make blocks double the size
      tetris.setNumbers(1234, true);
    } else {
      tetris.scale = 1;
      tetris.setNumbers(123456789, true);
    }
    finishedAnimating = false;
  }
}
