/*
Copyright (c) 2018 Tobias Blum . All right reserved.

Tetris Matrix Clock

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef TetrisMatrixDraw_h
#define TetrisMatrixDraw_h

#include <Arduino.h>
#include "Adafruit_GFX.h"

#define TETRIS_MAX_NUMBERS 9

#ifndef TETRIS_DISTANCE_BETWEEN_DIGITS
#define TETRIS_DISTANCE_BETWEEN_DIGITS 7
#endif

#ifndef TETRIS_Y_DROP_DEFAULT
#define TETRIS_Y_DROP_DEFAULT 16
#endif

// Type that describes the current state of a drawn number
typedef struct
{
  int num_to_draw; // Number to draw (0-9)
  int blockindex;  // The index of the brick (as defined in the falling instructions) that is currently falling
  int fallindex;   // y-position of the brick it already has (incrementing with each step)
  int x_shift;     // x-position of the number relative to the matrix where the number should be placed.
} numstate;

class TetrisMatrixDraw
{
    public:
        TetrisMatrixDraw (Adafruit_GFX  &display);
        Adafruit_GFX  *display;
        bool drawNumbers(int x = 0, int y = 0, bool displayColon = false);
        bool drawText(int x = 0, int y = 0);
        void drawChar(String letter, uint8_t x, uint8_t y, uint16_t color);
        void drawShape(int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot);
        void drawLargerShape(int scale, int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot);
        void setTime(String time, bool forceRefresh = false);
        void setNumbers(int value, bool forceRefresh = false);
        void setText(String txt, bool forceRefresh = false);
        void setNumState(int index, int value, int x_shift);
        void drawColon(int x, int y, uint16_t colonColour);
        int calculateWidth();
        bool _debug = false;
        int scale = 1;
        bool drawOutline = false;
        uint16_t outLineColour = 0x0000;

        static const uint16_t tetrisRED = 0xF800;
        static const uint16_t tetrisGREEN = 0x07E0;
        static const uint16_t tetrisBLUE = 0x325F;
        static const uint16_t tetrisWHITE = 0xFFFF;
        static const uint16_t tetrisYELLOW = 0xFFE0;
        static const uint16_t tetrisCYAN = 0x07FF;
        static const uint16_t tetrisMAGENTA = 0xF81F;
        static const uint16_t tetrisORANGE = 0xFB00;
        static const uint16_t tetrisBLACK = 0x0000;
        uint16_t tetrisColors[9] = {tetrisRED, tetrisGREEN, tetrisBLUE, tetrisWHITE, tetrisYELLOW, tetrisCYAN, tetrisMAGENTA, tetrisORANGE, tetrisBLACK};

    private:
        void intialiseColors();
        void resetNumStates();
        void drawLargerBlock(int x_pos, int y_pos, int scale, uint16_t color);
        numstate numstates[TETRIS_MAX_NUMBERS];
        int sizeOfValue;
};

#endif