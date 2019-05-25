/*******************************************************************
    Showing basic use of the library, using static time values,
    on an LED Matrix display.
 *                                                                 *
    Written by Brian Lough
    https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA
 *******************************************************************/

// ----------------------------
// Standard Libraries - Already Installed if you have ESP8266 set up
// ----------------------------

#include <Ticker.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------


#include <PxMatrix.h>
// The library for controlling the LED Matrix
// Needs to be manually downloaded and installed
// https://github.com/2dom/PxMatrix

#include <TetrisMatrixDraw.h>
// This library :)
// https://github.com/toblum/TetrisAnimation


Ticker display_ticker;
Ticker timer_ticker;

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
#define P_D 12
#define P_E 0

// PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);
// PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);

TetrisMatrixDraw tetris(display);

bool showColon = true;

// ISR for display refresh
void display_updater()
{

  display.display(70);

}

void number_updater()
{
  display.clearDisplay();
  tetris.drawNumbers(10,26, showColon);
}

void drawIntro(int x = 0, int y = 0)
{
  tetris.drawChar("T", x, y, tetris.tetrisCYAN);
  tetris.drawChar("e", x + 5, y, tetris.tetrisMAGENTA);
  tetris.drawChar("t", x + 11, y, tetris.tetrisYELLOW);
  tetris.drawChar("r", x + 17, y, tetris.tetrisGREEN);
  tetris.drawChar("i", x + 22, y, tetris.tetrisBLUE);
  tetris.drawChar("s", x + 27, y, tetris.tetrisRED);

  tetris.drawChar("T", x + 6, y + 9, tetris.tetrisRED);
  tetris.drawChar("i", x + 11, y + 9, tetris.tetrisWHITE);
  tetris.drawChar("m", x + 16, y + 9, tetris.tetrisCYAN);
  tetris.drawChar("e", x + 22, y + 9, tetris.tetrisMAGENTA);
}

void setup() {
  Serial.begin(115200);
  display.begin(16);
  display.clearDisplay();

  display_ticker.attach(0.002, display_updater);
  yield();
  display.clearDisplay();

  drawIntro(10, 10);

  tetris.setTime("12:59");

  delay(2000);
  timer_ticker.attach(0.1, number_updater);

  // Showing how the colon can be flashed from the sketch
  delay(5000);
  showColon = false;
  delay(5000);
  showColon = true;
  delay(5000);

  // Shows how it only updates what it needs to update.
  tetris.setTime("12:56");
}


void loop() {
}