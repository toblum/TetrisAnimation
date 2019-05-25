/*******************************************************************
    Displaying a NTP driving clock with tetris blocks
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
// Search for PxMatrix on the Arduino library manager
// https://github.com/2dom/PxMatrix

#include <TetrisMatrixDraw.h>
// This library :)
// https://github.com/toblum/TetrisAnimation

#include <TimeLib.h>
// Required by NtpClientLib
// Has to be installed manually from github
// https://github.com/PaulStoffregen/Time

#include <NtpClientLib.h>     
// Library for getting NTP timer_ticker
// Search for NTPClient on library manager
// https://github.com/gmag11/NtpClient


Ticker display_ticker;
Ticker timer_ticker;

char ssid[] = "SSID";       // your network SSID (name)
char password[] = "password";  // your network key

int8_t timeZone = 0;            // Timezone for NTP client (-5 for EST)

//Scan rate for your LED Matrix Display
#define SCAN_RATE 16

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
String displayedTime;

// ISR for display refresh
void display_updater()
{

  display.display(70);

}

void number_updater()
{
  display.clearDisplay();
  // drawNumbers(x,y, showColon)
  // x = left Pixel for where 
  // y = where blocks land
  // showColon = (optional) wether to show the colon or not, defaults to false
  tetris.drawNumbers(16,24, showColon);
}

// This isn't tetris blocks (maybe shouldn't be in the library!)
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
  display.begin(SCAN_RATE);
  display.clearDisplay();
  
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);


  // NTP config
  NTP.begin("pool.ntp.org", timeZone, true, 0);
  NTP.setInterval(63);;

  display_ticker.attach(0.002, display_updater);
  yield();
  display.clearDisplay();

  drawIntro(14, 8);

  displayedTime = NTP.getTimeStr();
  tetris.setTime(displayedTime);

  delay(2000);
  timer_ticker.attach(0.1, number_updater);
}


void loop() {
  String currentTime = NTP.getTimeStr();
  
  // Time has changed
  if (displayedTime != currentTime)
  {
    Serial.print("Time changed: ");
    Serial.println(currentTime);
    tetris.setTime(currentTime);
    displayedTime = currentTime;

    String seconds = currentTime.substring(6, 8);
    
    // Alternating the colon visibility to give it a blinking effect
    showColon = (seconds.toInt() % 2 == 1);
  }
}