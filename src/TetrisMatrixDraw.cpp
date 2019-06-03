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


#include "TetrisMatrixDraw.h"
#include "TetrisNumbers.h"
#include "TetrisLetters.h"

TetrisMatrixDraw::TetrisMatrixDraw(Adafruit_GFX &display)	{
    this->display = &display;
    intialiseColors();
    resetNumStates();
}

void TetrisMatrixDraw::drawChar(String letter, uint8_t x, uint8_t y, uint16_t color)
{
    this->display->setTextColor(color);
    this->display->setCursor(x, y);
    this->display->print(letter);
}

// *********************************************************************
// Draws a brick shape at a given position
// *********************************************************************
void TetrisMatrixDraw::drawShape(int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot)
{
  // Square
  if (blocktype == 0)
  {
    this->display->drawPixel(x_pos, y_pos, color);
    this->display->drawPixel(x_pos + 1, y_pos, color);
    this->display->drawPixel(x_pos, y_pos - 1, color);
    this->display->drawPixel(x_pos + 1, y_pos - 1, color);
  }

  // L-Shape
  if (blocktype == 1)
  {
    if (num_rot == 0)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos, y_pos - 2, color);
    }
    if (num_rot == 1)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 2, y_pos - 1, color);
    }
    if (num_rot == 2)
    {
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 2, color);
      this->display->drawPixel(x_pos, y_pos - 2, color);
    }
    if (num_rot == 3)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 2, y_pos, color);
      this->display->drawPixel(x_pos + 2, y_pos - 1, color);
    }
  }

  // L-Shape (reverse)
  if (blocktype == 2)
  {
    if (num_rot == 0)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 2, color);
    }
    if (num_rot == 1)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 2, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
    }
    if (num_rot == 2)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos, y_pos - 2, color);
      this->display->drawPixel(x_pos + 1, y_pos - 2, color);
    }
    if (num_rot == 3)
    {
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 2, y_pos - 1, color);
      this->display->drawPixel(x_pos + 2, y_pos, color);
    }
  }

  // I-Shape
  if (blocktype == 3)
  {
    if (num_rot == 0 || num_rot == 2)
    { // Horizontal
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 2, y_pos, color);
      this->display->drawPixel(x_pos + 3, y_pos, color);
    }
    if (num_rot == 1 || num_rot == 3)
    { // Vertical
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos, y_pos - 2, color);
      this->display->drawPixel(x_pos, y_pos - 3, color);
    }
  }

  // S-Shape
  if (blocktype == 4)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos, y_pos - 2, color);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 2, y_pos - 1, color);
    }
  }

  // S-Shape (reversed)
  if (blocktype == 5)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 2, color);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 2, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
    }
  }

  // Half cross
  if (blocktype == 6)
  {
    if (num_rot == 0)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos + 2, y_pos, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
    }
    if (num_rot == 1)
    {
      this->display->drawPixel(x_pos, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos, y_pos - 2, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
    }
    if (num_rot == 2)
    {
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 2, y_pos - 1, color);
    }
    if (num_rot == 3)
    {
      this->display->drawPixel(x_pos + 1, y_pos, color);
      this->display->drawPixel(x_pos, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 1, color);
      this->display->drawPixel(x_pos + 1, y_pos - 2, color);
    }
  }

   // Corner-Shape 
   if (blocktype == 7)
   {
     if (num_rot == 0)
     {
       this->display->drawPixel(x_pos, y_pos, color);
       this->display->drawPixel(x_pos + 1, y_pos, color);
       this->display->drawPixel(x_pos, y_pos - 1, color);
     }
     if (num_rot == 1)
     {
       this->display->drawPixel(x_pos, y_pos, color);
       this->display->drawPixel(x_pos, y_pos - 1, color);
       this->display->drawPixel(x_pos + 1, y_pos - 1, color);
     }
     if (num_rot == 2)
     {
       this->display->drawPixel(x_pos + 1 , y_pos, color);
       this->display->drawPixel(x_pos + 1 , y_pos - 1, color);
       this->display->drawPixel(x_pos, y_pos - 1, color);
     }
     if (num_rot == 3)
     {
       this->display->drawPixel(x_pos, y_pos, color);
       this->display->drawPixel(x_pos + 1, y_pos , color);
       this->display->drawPixel(x_pos + 1, y_pos - 1, color);
     }
   }
}

void TetrisMatrixDraw::drawLargerBlock(int x_pos, int y_pos, int scale, uint16_t color){
  this->display->fillRect(x_pos, y_pos, scale, scale, color);
  if(drawOutline){
    this->display->drawRect(x_pos, y_pos, scale, scale, this->outLineColour);
  }
}

void TetrisMatrixDraw::drawLargerShape(int scale, int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot)
{
  int offset1 = 1 * scale;
  int offset2 = 2 * scale;
  int offset3 = 3 * scale;

  // Square
  if (blocktype == 0)
  {
    this->drawLargerBlock(x_pos, y_pos, scale, color);
    this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
    this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
    this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
  }

  // L-Shape
  if (blocktype == 1)
  {
    if (num_rot == 0)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);

    }
    if (num_rot == 1)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);

    }
    if (num_rot == 2)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);

    }
    if (num_rot == 3)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
    }
  }

  // L-Shape (reverse)
  if (blocktype == 2)
  {
    if (num_rot == 0)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
    if (num_rot == 1)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
    }
    if (num_rot == 2)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
    if (num_rot == 3)
    {
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
    }
  }

  // I-Shape
  if (blocktype == 3)
  {
    if (num_rot == 0 || num_rot == 2)
    { // Horizontal
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset3, y_pos, scale, color);
    }
    if (num_rot == 1 || num_rot == 3)
    { // Vertical
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset3, scale, color);
    }
  }

  // S-Shape
  if (blocktype == 4)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
    }
  }

  // S-Shape (reversed)
  if (blocktype == 5)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
    }
  }

  // Half cross
  if (blocktype == 6)
  {
    if (num_rot == 0)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
    }
    if (num_rot == 1)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
    }
    if (num_rot == 2)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
    }
    if (num_rot == 3)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
  }

   // Corner-Shape 
   if (blocktype == 7)
   {
     if (num_rot == 0)
     {
       this->drawLargerBlock(x_pos, y_pos, scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
       this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
     }
     if (num_rot == 1)
     {
       this->drawLargerBlock(x_pos, y_pos, scale, color);
       this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
     }
     if (num_rot == 2)
     {
       this->drawLargerBlock(x_pos + offset1 , y_pos, scale, color);
       this->drawLargerBlock(x_pos + offset1 , y_pos - offset1, scale, color);
       this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
     }
     if (num_rot == 3)
     {
       this->drawLargerBlock(x_pos, y_pos, scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos , scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
     }
   }
}

void TetrisMatrixDraw::setNumState(int index, int value, int x_shift)
{
    if(index < TETRIS_MAX_NUMBERS) {
      Serial.println(value);
        this->numstates[index].num_to_draw = value;
        this->numstates[index].x_shift = x_shift;
        this->numstates[index].fallindex = 0;
        this->numstates[index].blockindex = 0;
    }
}

void TetrisMatrixDraw::setTime(String time, bool forceRefresh)
{
    this->sizeOfValue = 4;
    time.replace(":", "");
    for (uint8_t pos = 0; pos < 4; pos++)
    {
      int xOffset = pos * TETRIS_DISTANCE_BETWEEN_DIGITS * this->scale;
      if(pos >= 2){
        xOffset += (3 * this->scale);
      }
      String individualNumber = time.substring(pos, pos + 1);
      int number = (individualNumber != " ") ? individualNumber.toInt() : -1;
      // Only change the number if its different or being forced
      if (forceRefresh || number != this->numstates[pos].num_to_draw)
      {
        setNumState(pos, number, xOffset);
      }
    }
}

void TetrisMatrixDraw::setNumbers(int value, bool forceRefresh)
{
  String strValue = String(value);
  if(strValue.length() <= TETRIS_MAX_NUMBERS){
    this->sizeOfValue = strValue.length();
    int currentXShift = 0;
    for (uint8_t pos = 0; pos < this->sizeOfValue; pos++)
    {
      currentXShift = TETRIS_DISTANCE_BETWEEN_DIGITS * this->scale * pos;
      int number = strValue.substring(pos, pos + 1).toInt();
      // Only change the number if its different or being forced
      if (forceRefresh || number != this->numstates[pos].num_to_draw)
      {
        setNumState(pos, number, currentXShift);
      } else {
        this->numstates[pos].x_shift = currentXShift;
      }
    }
  } else {
    Serial.println("Number too long");
  }
}

void TetrisMatrixDraw::setText(String txt, bool forceRefresh)
{
    this->sizeOfValue = txt.length();
    int currentXShift = 0;
    for (uint8_t pos = 0; pos < this->sizeOfValue; pos++)
    {
      currentXShift = TETRIS_DISTANCE_BETWEEN_DIGITS * this->scale * pos;
      char letter = txt.charAt(pos);
      if (forceRefresh || (int)letter != this->numstates[pos].num_to_draw)
      {
        setNumState(pos, (int)letter, currentXShift);
      } else {
        this->numstates[pos].x_shift = currentXShift;
      }
    }
}

bool TetrisMatrixDraw::drawText(int x, int yFinish)
{
  // For each number position
  bool finishedAnimating = true;

  int scaledYOffset = (this->scale > 1) ? this->scale : 1;
  int y = yFinish - (TETRIS_Y_DROP_DEFAULT * this->scale);

  // For each number position
  for (int numpos = 0; numpos < this->sizeOfValue; numpos++)
  {

    if(numstates[numpos].num_to_draw >= 33)
    {
      // Draw falling shape
      //if (numstates[numpos].blockindex < blocksPerNumber[numstates[numpos].num_to_draw])
      if (numstates[numpos].blockindex < blocksPerChar[numstates[numpos].num_to_draw-33])
      {
        finishedAnimating = false;
        fall_instr_let current_fall = getFallinstrByAscii(numstates[numpos].num_to_draw, numstates[numpos].blockindex);

        // Handle variations of rotations
        uint8_t rotations = current_fall.num_rot;
        if (rotations == 1)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 2))
          {
            rotations = 0;
          }
        }
        if (rotations == 2)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3 * 2))
          {
            rotations = 1;
          }
        }
        if (rotations == 3)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 2))
          {
            rotations = 1;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 3))
          {
            rotations = 2;
          }
        }
        if(this->scale <= 1){
          drawShape(current_fall.blocktype, 
                    this->tetrisColors[current_fall.color],
                    x + current_fall.x_pos + numstates[numpos].x_shift, 
                    y + numstates[numpos].fallindex - scaledYOffset, 
                    rotations);
        } else {
          drawLargerShape(this->scale, 
                          current_fall.blocktype, 
                          this->tetrisColors[current_fall.color], 
                          x + (current_fall.x_pos * this->scale) + numstates[numpos].x_shift, 
                          y + (numstates[numpos].fallindex * scaledYOffset) - scaledYOffset, 
                          rotations);
        }
        //drawShape(current_fall.blocktype, this->tetrisColors[current_fall.color], x + current_fall.x_pos + numstates[numpos].x_shift, y + numstates[numpos].fallindex - 1, rotations);
        numstates[numpos].fallindex++;

        if (numstates[numpos].fallindex > current_fall.y_stop)
        {
          numstates[numpos].fallindex = 0;
          numstates[numpos].blockindex++;
        }
      }

      // Draw already dropped shapes
      if (numstates[numpos].blockindex > 0)
      {
        for (int i = 0; i < numstates[numpos].blockindex; i++)
        {
          fall_instr_let fallen_block = getFallinstrByAscii(numstates[numpos].num_to_draw, i);
          if(this->scale <= 1){
            drawShape(fallen_block.blocktype, 
                      this->tetrisColors[fallen_block.color], 
                      x + fallen_block.x_pos + numstates[numpos].x_shift, 
                      y + fallen_block.y_stop - 1, 
                      fallen_block.num_rot);
          } else {
            drawLargerShape(this->scale, 
                            fallen_block.blocktype, 
                            this->tetrisColors[fallen_block.color], 
                            x + (fallen_block.x_pos * this->scale) + numstates[numpos].x_shift, 
                            y + (fallen_block.y_stop * scaledYOffset) - scaledYOffset, 
                            fallen_block.num_rot);
          }
          //drawShape(fallen_block.blocktype, this->tetrisColors[fallen_block.color], x + fallen_block.x_pos + numstates[numpos].x_shift, y + fallen_block.y_stop - 1, fallen_block.num_rot);
        }
      }
    }
    
  }

  return finishedAnimating;
}

bool TetrisMatrixDraw::drawNumbers(int x, int yFinish, bool displayColon)
{
  // For each number position
  bool finishedAnimating = true;

  int scaledYOffset = (this->scale > 1) ? this->scale : 1;
  int y = yFinish - (TETRIS_Y_DROP_DEFAULT * this->scale);

  for (int numpos = 0; numpos < this->sizeOfValue; numpos++)
  {
    if(numstates[numpos].num_to_draw >= 0) 
    {
      // Draw falling shape
      if (numstates[numpos].blockindex < blocksPerNumber[numstates[numpos].num_to_draw])
      {
        finishedAnimating = false;
        fall_instr current_fall = getFallinstrByNum(numstates[numpos].num_to_draw, numstates[numpos].blockindex);

        // Handle variations of rotations
        uint8_t rotations = current_fall.num_rot;
        if (rotations == 1)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 2))
          {
            rotations = 0;
          }
        }
        if (rotations == 2)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3 * 2))
          {
            rotations = 1;
          }
        }
        if (rotations == 3)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 2))
          {
            rotations = 1;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 3))
          {
            rotations = 2;
          }
        }

        if(this->scale <= 1){
          drawShape(current_fall.blocktype, 
                    this->tetrisColors[current_fall.color],
                    x + current_fall.x_pos + numstates[numpos].x_shift, 
                    y + numstates[numpos].fallindex - scaledYOffset, 
                    rotations);
        } else {
          drawLargerShape(this->scale, 
                          current_fall.blocktype, 
                          this->tetrisColors[current_fall.color], 
                          x + (current_fall.x_pos * this->scale) + numstates[numpos].x_shift, 
                          y + (numstates[numpos].fallindex * scaledYOffset) - scaledYOffset, 
                          rotations);
        }
        numstates[numpos].fallindex++;

        if (numstates[numpos].fallindex > current_fall.y_stop)
        {
          numstates[numpos].fallindex = 0;
          numstates[numpos].blockindex++;
        }
      }

      // Draw already dropped shapes
      if (numstates[numpos].blockindex > 0)
      {
        for (int i = 0; i < numstates[numpos].blockindex; i++)
        {
          fall_instr fallen_block = getFallinstrByNum(numstates[numpos].num_to_draw, i);
          if(this->scale <= 1){
            drawShape(fallen_block.blocktype, 
                      this->tetrisColors[fallen_block.color], 
                      x + fallen_block.x_pos + numstates[numpos].x_shift, 
                      y + fallen_block.y_stop - 1, 
                      fallen_block.num_rot);
          } else {
            drawLargerShape(this->scale, 
                            fallen_block.blocktype, 
                            this->tetrisColors[fallen_block.color], 
                            x + (fallen_block.x_pos * this->scale) + numstates[numpos].x_shift, 
                            y + (fallen_block.y_stop * scaledYOffset) - scaledYOffset, 
                            fallen_block.num_rot);
          }
        }
      }
    }
  }

  if (displayColon)
  {
    this->drawColon(x, y, this->tetrisWHITE);
  }

  return finishedAnimating;
}

void TetrisMatrixDraw::drawColon(int x, int y, uint16_t colonColour){
  int colonSize = 2 * this->scale;
  int xColonPos = x + (TETRIS_DISTANCE_BETWEEN_DIGITS * 2 * this->scale);  
  display->fillRect(xColonPos, y + (12 * this->scale), colonSize, colonSize, colonColour);
  display->fillRect(xColonPos, y + (8 * this->scale), colonSize, colonSize, colonColour);
}

void TetrisMatrixDraw::intialiseColors(){
    this->tetrisRED = 0xF800;
    this->tetrisGREEN = 0x07E0;
    this->tetrisBLUE = 0x325F;
    this->tetrisWHITE = 0xFFFF;
    this->tetrisYELLOW = 0xFFE0;
    this->tetrisCYAN = 0x07FF;
    this->tetrisMAGENTA = 0xF81F;
    this->tetrisORANGE = 0xFB00;
    this->tetrisBLACK = 0x0000;
    
    this->tetrisColors[0] = this->tetrisRED; 
    this->tetrisColors[1] = this->tetrisGREEN; 
    this->tetrisColors[2] = this->tetrisBLUE; 
    this->tetrisColors[3] = this->tetrisWHITE; 
    this->tetrisColors[4] = this->tetrisYELLOW; 
    this->tetrisColors[5] = this->tetrisCYAN; 
    this->tetrisColors[6] = this->tetrisMAGENTA;
    this->tetrisColors[7] = this->tetrisORANGE; 
    this->tetrisColors[8] = this->tetrisBLACK;
}

int TetrisMatrixDraw::calculateWidth(){
  return (this->sizeOfValue * TETRIS_DISTANCE_BETWEEN_DIGITS) - 1;
}

void TetrisMatrixDraw::resetNumStates(){
    for(int i = 0; i < TETRIS_MAX_NUMBERS; i++){
        this->numstates[i].num_to_draw = -1;
        this->numstates[i].fallindex = 0;
        this->numstates[i].blockindex = 0;
        this->numstates[i].x_shift = 0;
    }
}