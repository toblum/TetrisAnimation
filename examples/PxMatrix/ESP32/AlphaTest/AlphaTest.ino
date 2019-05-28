/*******************************************************************
    Example showing writing text using the TetrisAnimation
    library for the ESP32.
 *                                                                 *
    Written by Brian Lough (witnessmenow on Github)

 *******************************************************************/

// ----------------------------
// Standard Libraries - Already Installed if you have ESP32 set up
// ----------------------------

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <PxMatrix.h>
// The library for controlling the LED Matrix
// Can be installed from the library manager
// https://github.com/2dom/PxMatrix

// Adafruit GFX library is a dependancy for the PxMatrix Library
// Can be installed from the library manager
// https://github.com/adafruit/Adafruit-GFX-Library

#include <TetrisMatrixDraw.h>
// This library!
// https://github.com/toblum/TetrisAnimation


portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t * displayTimer = NULL;
hw_timer_t * animationTimer = NULL;

// Pins for LED MATRIX to the ESP32
#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2

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

#define ANIMATION_TIME 50000    // Controls the speed in which the blocks update, 
                                // increase this number to make it slower

void IRAM_ATTR display_updater() {
    // Increment the counter and set the time of ISR
    portENTER_CRITICAL_ISR(&timerMux);
    display.display(70);
    portEXIT_CRITICAL_ISR(&timerMux);
}
  
void animationHandler()
{
    portENTER_CRITICAL_ISR(&timerMux);
    display.clearDisplay();
    tetris.drawText(5, 20);
    portEXIT_CRITICAL_ISR(&timerMux);
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

  displayTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(displayTimer, &display_updater, true);
  timerAlarmWrite(displayTimer, 2000, true);
  timerAlarmEnable(displayTimer);

  yield();
  display.clearDisplay();

  drawIntro(10, 10);
  
  delay(2000);

  // Must use upercase characters
  // See below for all supported chars 
  tetris.setText("HELLO!");
  
  animationTimer = timerBegin(1, 80, true);
  timerAttachInterrupt(animationTimer, &animationHandler, true);
  timerAlarmWrite(animationTimer, ANIMATION_TIME, true);
  timerAlarmEnable(animationTimer);


  delay(5000);
  tetris.setText("!#$%&'()");

  delay(5000);
  tetris.setText("*+,-./");

  delay(5000);
  tetris.setText("01234567");

  delay(5000);
  tetris.setText("89:;<=>?");

  delay(5000);
  tetris.setText("@ABCDEFG");

  delay(5000);
  tetris.setText("HIJKLMNO");

  delay(5000);
  tetris.setText("PQRSTUVW");

  delay(5000);
  tetris.setText("XYZ");


}


void loop() {
}