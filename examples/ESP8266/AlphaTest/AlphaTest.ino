/*******************************************************************
    Example showing writing text using the TetrisAnimation
    library.
 *                                                                 *
    Written by Mike Swan (n00dles101 on Github)

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

bool showColon = true;

// ISR for display refresh
void display_updater()
{

  display.display(70);

}

void number_updater()
{
  display.clearDisplay();
  tetris.drawText(5,5);
}

void drawIntro(int x = 0, int y = 0)
{
  tetris.drawChar("T", x, y, myCYAN);
  tetris.drawChar("e", x + 5, y, myMAGENTA);
  tetris.drawChar("t", x + 11, y, myYELLOW);
  tetris.drawChar("r", x + 17, y, myGREEN);
  tetris.drawChar("i", x + 22, y, myBLUE);
  tetris.drawChar("s", x + 27, y, myRED);

  tetris.drawChar("L", x - 2, y + 9, myRED);
  tetris.drawChar("e", x + 5, y + 9, myMAGENTA);
  tetris.drawChar("t", x + 11, y + 9, myYELLOW);
  tetris.drawChar("t", x + 17, y + 9, myGREEN);
  tetris.drawChar("e", x + 23, y + 9, myBLUE);
  tetris.drawChar("r", x + 29, y + 9, myRED);
  tetris.drawChar("s", x + 37, y + 9, myMAGENTA);
}

void setup() {
  Serial.begin(115200);
  display.begin(16);
  display.clearDisplay();

  display_ticker.attach(0.002, display_updater);
  yield();
  display.clearDisplay();

  drawIntro(10, 10);

  tetris.setText("!#$%&'()");
  
  delay(2000);
  timer_ticker.attach(0.05, number_updater);

  delay(15000);
  tetris.setText("*+,-./");

  delay(15000);
  tetris.setText("01234567");

  delay(15000);
  tetris.setText("89:;<=>?");

  delay(15000);
  tetris.setText("@ABCDEFG");

  delay(15000);
  tetris.setText("HIJKLMNO");

  delay(15000);
  tetris.setText("PQRSTUVW");

  delay(15000);
  tetris.setText("XYZ");


}


void loop() {
}