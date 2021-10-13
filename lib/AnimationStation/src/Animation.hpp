#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "NeoPico.hpp"
#include "Pixel.hpp"

struct RGB
{
  RGB()
    : r(0), g(0), b(0) { }

  RGB(uint8_t r, uint8_t g, uint8_t b)
    : r(r), g(g), b(b) { }

  RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
    : r(r), g(g), b(b), w(w) { }

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t w;

  inline static RGB wheel(uint8_t pos) {
    pos = 255 - pos;
    if (pos < 85) {
      return RGB(255 - pos * 3, 0, pos * 3);
    } else if (pos < 170) {
      pos -= 85;
      return RGB(0, pos * 3, 255 - pos * 3);
    } else {
      pos -= 170;
      return RGB(pos * 3, 255 - pos * 3, 0);
    }
  }

  inline uint32_t value(LEDFormat format, float brightnessX = 1.0F) {
    switch (format) {
      case LED_FORMAT_GRB:
        return ((uint32_t)(g * brightnessX) << 16)
            | ((uint32_t)(r * brightnessX) << 8)
            | (uint32_t)(b * brightnessX);

      case LED_FORMAT_RGB:
        return ((uint32_t)(r * brightnessX) << 16)
            | ((uint32_t)(g * brightnessX) << 8)
            | (uint32_t)(b * brightnessX);

      case LED_FORMAT_GRBW:
      {
        if ((r == g) && (r == b))
          return (uint32_t)(r * brightnessX);

        return ((uint32_t)(g * brightnessX) << 24)
            | ((uint32_t)(r * brightnessX) << 16)
            | ((uint32_t)(b * brightnessX) << 8)
            | (uint32_t)(w * brightnessX);
      }

      case LED_FORMAT_RGBW:
      {
        if ((r == g) && (r == b))
          return (uint32_t)(r * brightnessX);

        return ((uint32_t)(r * brightnessX) << 24)
            | ((uint32_t)(g * brightnessX) << 16)
            | ((uint32_t)(b * brightnessX) << 8)
            | (uint32_t)(w * brightnessX);
      }
    }
  }

};

static const RGB ColorBlack(0, 0, 0);
static const RGB ColorWhite(255, 255, 255);
static const RGB ColorRed(255, 0, 0);
static const RGB ColorOrange(255, 128, 0);
static const RGB ColorYellow(255, 255, 0);
static const RGB ColorLimeGreen(128, 255, 0);
static const RGB ColorGreen(0, 255, 0);
static const RGB ColorSeafoam(0, 255, 128);
static const RGB ColorAqua(0, 255, 255);
static const RGB ColorSkyBlue(0, 128, 255);
static const RGB ColorBlue(0, 0, 255);
static const RGB ColorPurple(128, 0, 255);
static const RGB ColorPink(255, 0, 255);
static const RGB ColorMagenta(255, 0, 128);

class Animation {
public:
  Animation(std::vector<Pixel> pixels);

  static LEDFormat format;

  virtual void Animate(RGB (&frame)[100]) = 0;
  bool isComplete();
protected:
  std::vector<Pixel> pixels;
  int currentLoop = 0;
  int totalLoops;
  bool baseAnimation = true;
};

#endif
