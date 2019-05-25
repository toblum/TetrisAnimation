/*******************************************************************
    Showing how you can use multiple instances of the library
    on the one LED Matrix display.
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
TetrisMatrixDraw tetrisTwo(display);
TetrisMatrixDraw tetrisThree(display);
TetrisMatrixDraw tetrisFour(display);


bool finishedAnimating = false;
bool showColon = true;

// ISR for display refresh
void display_updater()
{

  display.display(70);

}

// Having lots of things on the screen can cause the screen to flicker
// You can reduce this by only drawing when pieces are still falling
// You would manually set finishedAnimating to be false when you 
// you populate the tetris object with new data.
void number_updater()
{
  if(!finishedAnimating) {
    display.clearDisplay();
    bool first = tetris.drawNumbers(0,16, showColon);
    bool second = tetrisTwo.drawNumbers(0,32, showColon);
    bool third = tetrisThree.drawNumbers(32,16, showColon);
    bool fourth = tetrisFour.drawNumbers(32,32, showColon);
    finishedAnimating = first && second && third && fourth;
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
  display.begin(16);
  display.clearDisplay();

  display_ticker.attach(0.002, display_updater);
  yield();
  display.clearDisplay();

  drawIntro(10, 10);

  tetris.setTime("12:59");
  tetrisTwo.setTime("23:59");
  tetrisThree.setTime("03:59");
  tetrisFour.setTime("09:59");

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