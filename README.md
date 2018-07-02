# TetrisAnimation
Library to draw numbers using a tetris style

[![alt text](https://j.gifs.com/6RvBDl.gif "Tetris clock animation")](https://youtu.be/BGmjvfqf_0U)

Tested using ESP8266 on RGB Led matrixes (using the [PxMatrix library](https://github.com/2dom/PxMatrix/)), but potentially works on any display that uses Adafruit GFX library

## Basic Usage

See examples for more details.

```
//Intialise library by passing in a display
PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);
TetrisMatrixDraw tetris(display);

// Set the value of the library by using setTime, setNumbers or setText

// Usage: setTime(time_string)
// time_string = time in the format "21:23"
tetris.setTime("12:34");

// Usage: setNumbers(num)
// num = Integer value. Max: 999999999 (9 digits long) Min: 0 (negative not currently supported).
tetris.setNumbers(1234);

// Usage: setText(string)
// string = regular text string, most ascii chars supported.
tetris.setNumbers("HOWDY");


// Draw the value

// Usage: drawNumbers(x, y, showColon) (for use with setTime or setNumber)
// x = most left Pixel of the text 
// y = where blocks start falling from (will land y + 16)
// showColon = (optional) show the colon or not, defaults to false (only applicaple when using setTime)
tetris.drawNumbers(16,8, true);

// Usage: drawText(x, y) (for use with setText)
// x = most left Pixel of the text 
// y = where blocks start falling from (will land y + 16)
tetris.drawText(16,8);

```
