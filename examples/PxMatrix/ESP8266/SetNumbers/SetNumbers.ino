/*******************************************************************
    Using a 64 * 32 RGB Matrix to display a mario image
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
// Can be installed from the library manager
// https://github.com/2dom/PxMatrix
// This library has a dependancy on the Adafruit GFX library

#include <TetrisMatrixDraw.h>


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

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(0, 255, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);

uint16_t myCOLORS[8] = {myRED, myGREEN, myBLUE, myWHITE, myYELLOW, myCYAN, myMAGENTA, myBLACK};

TetrisMatrixDraw tetris(display);

// ISR for display refresh
void display_updater()
{

  display.display(70);

}

void number_updater()
{
  display.clearDisplay();

  tetris.drawNumbers(0,16);
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
  display.begin(16);
  display.clearDisplay();

  display_ticker.attach(0.002, display_updater);
  yield();
  display.clearDisplay();

  drawIntro(10, 10);

  tetris.setNumbers(123456789);

  delay(2000);
  timer_ticker.attach(0.1, number_updater);

  delay(10000);

  // Scale will make each tetris block bigger
  // It needs to be called before you do tetris.setNumbers
  // It will persist for future setNumbers
  tetris.scale = 2; // Make blocks double the size

  tetris.setNumbers(1234);
}


void loop() {
}