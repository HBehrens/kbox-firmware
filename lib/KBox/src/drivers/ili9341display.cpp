/*
  The MIT License

  Copyright (c) 2016 Thomas Sarlandie thomas@sarlandie.net

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
#include "ili9341display.h"
#include "drivers/board.h"
#include "font_DroidSans.h"

ILI9341Display::ILI9341Display() : size(Size(display_width, display_height)), backlightPin(display_backlight)
{
  display = new ILI9341_t3(display_cs, display_dc, 255 /* rst unused */, display_mosi, display_sck, display_miso);

  display->begin();
  display->fillScreen(ILI9341_BLUE);
  display->setRotation(display_rotation);

  setBacklight(BacklightIntensityMax);
}

void ILI9341Display::setBacklight(BacklightIntensity intensity) {
  if (backlightPin) {
    if (intensity > 0) {
      analogWrite(backlightPin, intensity);
    }
    else {
      analogWrite(backlightPin, 0);
    }
  }
}

// TODO: delete me when everything has been updated to provide bgColor
void ILI9341Display::drawText(Point a, Font font, Color color, const char *text) {
  this->drawText(a, font, color, ColorBlue, text);
}

void ILI9341Display::drawText(Point a, Font font, Color color, Color bgColor, const char *text) {
  drawText(a, font, color, bgColor, String(text));
}

void ILI9341Display::drawText(const Point &a, const Font &font, const Color &color, const Color &bgColor, const String &text) {
  display->setCursor(a.x(), a.y());
  display->setTextColor(color, bgColor);

  switch (font) {
    case FontDefault:
      display->setFont(DroidSans_12);
      break;
    case FontLarge:
      display->setFont(DroidSans_32);
      break;
  };
  display->println(text);
}

void ILI9341Display::drawLine(Point a, Point b, Color color) {
  display->drawLine(a.x(), a.y(), b.x(), b.y(), color);
}

void ILI9341Display::drawRectangle(Point orig, Size size, Color color) {
  display->drawRect(orig.x(), orig.y(), size.width(), size.height(), color);
}

void ILI9341Display::fillRectangle(Point orig, Size size, Color color) {
  display->fillRect(orig.x(), orig.y(), size.width(), size.height(), color);
}

