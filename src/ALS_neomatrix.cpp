#include "ALS_neomatrix.h"

MyNeoMatrix * MyNeoMatrixPtr = nullptr;

FASTLED_NAMESPACE_BEGIN
uint16_t XY(uint8_t x, uint8_t y) {
    return MyNeoMatrixPtr->XY(x, y);
}
FASTLED_NAMESPACE_END

uint8_t mapsin8(uint8_t theta, uint8_t lowest, uint8_t highest )
{
    uint8_t beatsin = sin8(theta);
    uint8_t rangewidth = highest - lowest;
    uint8_t scaledbeat = scale8(beatsin, rangewidth);
    uint8_t result = lowest + scaledbeat;
    return result;
}

uint8_t mapcos8(uint8_t theta, uint8_t lowest, uint8_t highest )
{
    uint8_t beatcos = cos8(theta);
    uint8_t rangewidth = highest - lowest;
    uint8_t scaledbeat = scale8(beatcos, rangewidth);
    uint8_t result = lowest + scaledbeat;
    return result;
}

MyNeoMatrix * MyNeoMatrix_instance()
{
    return MyNeoMatrixPtr;
}

MyNeoMatrix::MyNeoMatrix(CRGB *_leds, uint8_t w, uint8_t h, uint8_t matrixType)
    : FastLED_NeoMatrix(_leds, w, h, 1, 1, matrixType)
{
	MyNeoMatrixPtr = this;

}

void MyNeoMatrix::Initialize(MyNeoMatrix *object)
{

}

uint8_t MyNeoMatrix::getRotation()
{
    return rotation;
}

uint16_t MyNeoMatrix::getNumLeds()
{
    return _numLeds;
}

uint8_t MyNeoMatrix::getCenterX()
{
    return (_matrixW / 2) - 1;
}

uint8_t MyNeoMatrix::getCenterY()
{
    return (_matrixH / 2) - 1;
}

uint8_t MyNeoMatrix::getDimension()
{
    if (type & NEO_MATRIX_ROWS) {
        return width();
    } else {
        return height();
    }
}

CRGB *MyNeoMatrix::getLeds()
{
    return _leds;
}

void MyNeoMatrix::setCurrentLimit(uint32_t maxCurrent)
{
    FastLED.setMaxPowerInVoltsAndMilliamps(5, maxCurrent);
}

void MyNeoMatrix::fill(CRGB color, bool shouldShow)
{
    fill_solid(_leds, _numLeds, color);
    if (shouldShow) {
        show();
    }
}

void MyNeoMatrix::fillProgress(double progress)
{
    FastLED.clear();

    const uint16_t number = static_cast<uint16_t>(_numLeds * progress);
    const uint8_t fullRows = static_cast<uint8_t>(number / width());
    for (uint8_t y = 0; y < fullRows; ++y) {
        for (uint8_t x = 0; x < width(); ++x) {
            drawPixelXY(x, y, CRGB(5, 5, 5));
        }
    }

    const uint8_t remainingProgress = static_cast<uint8_t>(number % width());
    for (uint8_t x = 0; x < remainingProgress; ++x) {
        drawPixelXY(x, fullRows, CRGB(5, 5, 5));
    }

    const String percent = String(static_cast<int>(progress * 100));
    setCursor(0, 5);
    setPassThruColor(CRGB(40, 0, 0));
    print(percent);
    setPassThruColor();
    delay(1);

    FastLED.show();
}

void MyNeoMatrix::setLed(uint16_t index, CRGB color)
{
    _leds[index] = color;
}

void MyNeoMatrix::fadeToBlackBy(uint16_t index, uint8_t step)
{
    _leds[index].fadeToBlackBy(step);
}

void MyNeoMatrix::fadeToBlackBy(uint8_t step)
{
    for (uint16_t i = 0; i < _numLeds; i++) {
        _leds[i].fadeToBlackBy(step);
    }
}

void MyNeoMatrix::dimAll(uint8_t value)
{
    for (uint16_t i = 0; i < _numLeds; i++) {
        _leds[i].nscale8(value);
    }
}

uint8_t MyNeoMatrix::wrapX(int8_t x)
{
    return (x + width()) % width();
}

uint8_t MyNeoMatrix::wrapY(int8_t y)
{
    return (y + height()) % height();
}

void MyNeoMatrix::fader(uint8_t step)
{
    for (uint8_t x = 0; x < width(); x++) {
        for (uint8_t y = 0; y < height(); y++) {
            fadePixel(x, y, step);
        }
    }
}

void MyNeoMatrix::fadePixel(uint8_t x, uint8_t y, uint8_t step)
{
    uint16_t pixelNum = XY(x, y);
    if (!getPixColor(pixelNum)) {
        return;
    }

    if (_leds[pixelNum].r >= 30 ||
            _leds[pixelNum].g >= 30 ||
            _leds[pixelNum].b >= 30) {
        _leds[pixelNum].fadeToBlackBy(step);
    } else {
        _leds[pixelNum] = 0;
    }
}

uint32_t MyNeoMatrix::colorcode(const CRGB &color)
{
    return 	uint32_t{color.r} << 16 |
           	uint32_t{color.g} << 8 |
			uint32_t{color.b};
}

void MyNeoMatrix::applyBlur2d(uint8_t amount)
{
    blur2d(_leds, width(), height(), amount);
}
void MyNeoMatrix::applyBlur2d(uint8_t w, uint8_t h, uint8_t amount)
{
    blur2d(_leds, w, h, amount);
}

void MyNeoMatrix::matrixTest()
{
    for (int16_t i = 0; i < 16; i++) {
        clear();
        drawPixelXY(i, 0, CRGB(CRGB::Red));
        drawPixelXY(0, i, CRGB(CRGB::Green));
        drawPixelXY(i, i, CRGB(CRGB::White));
        show();
        delay(100);
    }

    clear();
    show();
}

void MyNeoMatrix::clear(bool shouldShow)
{
    FastLED.clear();
    if (shouldShow) {
        delay(1);
        show();
    }
}


uint16_t MyNeoMatrix::XYS( uint8_t x, uint8_t y) // maps the matrix to the strip
{
  uint16_t i;
  i = (y * _matrixW) + (_matrixW - x);

  // i = (_numLeds - 1) - i;

  if (i > _numLeds)
    i = _numLeds;

  return i;
}

// ###############################################################################
// FROM : https://github.com/Intrinsically-Sublime/esp8266-fastled-webserver
int MyNeoMatrix::_XY(int x, int y) {


    // matrix_wh_get(_matrixW, _matrixH);   
    if(y > _matrixH) { y = _matrixH; }
    if(y < 0) { y = 0; }
    if(x > _matrixW) { x = _matrixW;}
    if(x < 0) { x = 0; }
    if(x % 2 == 1) {  
    return (x * (_matrixW) + (_matrixH - y -1));
    } else {
        // use that line only, if you have all rows beginning at the same side
        return (x * (_matrixW) + y);  
    }
}

boolean neomatrix_horizontal = true;

// #define SERPENTINE
int MyNeoMatrix::_XY_(int x, int y) { // x = Width, y = Height


    int XorY; 

    // map anything outside of the matrix to the extra hidden pixel
    if (y >= _matrixH || x >= _matrixW || x < 0 || y < 0) { return _numLeds; }

    #ifdef MIRROR_WIDTH
        x = (_matrixW - 1) - x;
    #endif

    #ifndef MIRROR_HEIGHT   // Default is to mirror the height to be compatible with irregular matrix array that is read from the top left corner
        y = (_matrixH - 1) - y;
    #endif

    if (neomatrix_horizontal) {
        uint8_t xx = x;
        x = y;
        y = xx;
        XorY = _matrixW;
    }
    else {
        XorY = _matrixH;
    }

    uint16_t pixNum;

    // #ifdef SERPENTINE
        if(x%2 == 0) {
            pixNum = (x * XorY) + y;
        } else {
            pixNum = (x * XorY) + ((XorY - 1) - y);
        }
        pixNum = (_numLeds - 1) - pixNum;
    // #else
    //     pixNum = (x * XorY) + y;
    //     pixNum = (_numLeds - 1) - pixNum;
    // #endif

    return pixNum;
}

uint16_t MyNeoMatrix::getPixelNumberXY(uint8_t x, uint8_t y)
{
    return static_cast<uint16_t>(XY(y, x));
}
uint16_t MyNeoMatrix::getPixelNumber_XY(uint8_t x, uint8_t y)
{
    return _XY_( x,  y);
}
void MyNeoMatrix::drawPixelXY(uint8_t x, uint8_t y, CRGB color)
{
    _leds[getPixelNumberXY(x, y)] = color;
}
void MyNeoMatrix::drawPixel_XY(uint8_t x, uint8_t y, CRGB color)
{
    _leds[getPixelNumber_XY(x, y)] = color;
}


void MyNeoMatrix::drawLineXY(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, CRGB color)
{
    setPassThruColor(color);
    drawLine(y0, x0, y1, x1, 0);
    setPassThruColor();
}

CRGB MyNeoMatrix::getPixColor(uint16_t number)
{
    if (number > _numLeds - 1) {
        return 0;
    }
    return _leds[number];
}

CRGB MyNeoMatrix::getPixColorXY(uint8_t x, uint8_t y)
{
    return getPixColor(getPixelNumberXY(x, y));
}

void MyNeoMatrix::tintPixelXY(uint8_t x, uint8_t y, CRGB color)
{
    _leds[getPixelNumberXY(x, y)] += color;
}

void MyNeoMatrix::shadePixelXY(uint8_t x, uint8_t y, CRGB color)
{
    _leds[getPixelNumberXY(x, y)] -= color;
}

void MyNeoMatrix::blendPixelXY(uint8_t x, uint8_t y, const CRGB &color, uint8_t amount)
{
    nblend(_leds[getPixelNumberXY(x, y)], color, amount);
}

void MyNeoMatrix::dimPixelXY(uint8_t x, uint8_t y, uint8_t value)
{
    _leds[getPixelNumberXY(x, y)].nscale8(value);
}

void MyNeoMatrix::fillRectXY(uint8_t x, uint8_t y, uint8_t w, uint8_t h, CRGB color)
{
    setPassThruColor(color);
    fillRect(y, x, h, w, 0);
    setPassThruColor();
}

void MyNeoMatrix::fadePixelXY(uint8_t x, uint8_t y, uint8_t step)
{
    const uint16_t pixelNum = getPixelNumberXY(x, y);
    const CRGB color = getPixColor(pixelNum);

    if (!color) {
        return;
    }

    if (color.r >= 30 || color.g >= 30 || color.b >= 30) {
        fadeToBlackBy(pixelNum, step);
    } else {
        setLed(pixelNum, CRGB::Black);
    }
}


  void MyNeoMatrix::SpiralStream(int x, int y, int r, byte dimm) {
    for (int d = r; d >= 0; d--) { // from the outside to the inside
      for (int i = x - d; i <= x + d; i++) {
        _leds[XY(i, y - d)] += _leds[XY(i + 1, y - d)]; // lowest row to the right
        _leds[XY(i, y - d)].nscale8(dimm);
      }
      for (int i = y - d; i <= y + d; i++) {
        _leds[XY(x + d, i)] += _leds[XY(x + d, i + 1)]; // right colum up
        _leds[XY(x + d, i)].nscale8(dimm);
      }
      for (int i = x + d; i >= x - d; i--) {
        _leds[XY(i, y + d)] += _leds[XY(i - 1, y + d)]; // upper row to the left
        _leds[XY(i, y + d)].nscale8(dimm);
      }
      for (int i = y + d; i >= y - d; i--) {
        _leds[XY(x - d, i)] += _leds[XY(x - d, i - 1)]; // left colum down
        _leds[XY(x - d, i)].nscale8(dimm);
      }
    }
  }

    CRGB  MyNeoMatrix::ColorFromCurrentPalette(CRGBPalette16 currentPalette, uint8_t index, uint8_t brightness, TBlendType blendType) {
        return ColorFromPalette(currentPalette, index, brightness, blendType);
    }
  void MyNeoMatrix::BresenhamLine(CRGBPalette16 currentPalette, int x0, int y0, int x1, int y1, byte colorIndex)
  {
    BresenhamLine(x0, y0, x1, y1, ColorFromCurrentPalette(currentPalette, colorIndex));
  }

  void MyNeoMatrix::BresenhamLine(int x0, int y0, int x1, int y1, CRGB color)
  {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    for (;;) {
      _leds[XY(x0, y0)] += color;
      if (x0 == x1 && y0 == y1) break;
      e2 = 2 * err;
      if (e2 > dy) {
        err += dy;
        x0 += sx;
      }
      if (e2 < dx) {
        err += dx;
        y0 += sy;
      }
    }
  }


  // All the caleidoscope functions work directly within the screenbuffer (leds array).
  // Draw whatever you like in the area x(0-15) and y (0-15) and then copy it arround.

  // rotates the first 16x16 quadrant 3 times onto a 32x32 (+90 degrees rotation for each one)
  void MyNeoMatrix::Caleidoscope1() {
    uint8_t sCenterX = (_matrixW/2);
    uint8_t sCenterY = (_matrixH/2);

    for (int x = 0; x < sCenterX; x++) {
      for (int y = 0; y < sCenterY; y++) {
        _leds[XY(_matrixW - 1 - x, y)] = _leds[XY(x, y)];
        _leds[XY(_matrixW - 1 - x, _matrixH - 1 - y)] = _leds[XY(x, y)];
        _leds[XY(x, _matrixH - 1 - y)] = _leds[XY(x, y)];
      }
    }
  }
// const byte MATRIX_CENTRE_X = MATRIX_CENTER_X - 1;
// const byte MATRIX_CENTRE_Y = MATRIX_CENTER_Y - 1;

  // mirror the first 16x16 quadrant 3 times onto a 32x32
  void MyNeoMatrix::Caleidoscope2() {
    uint8_t sCenterX = (_matrixW/2);
    uint8_t sCenterY = (_matrixH/2);

    for (int x = 0; x < sCenterX; x++) {
      for (int y = 0; y < sCenterY; y++) {
        _leds[XY(_matrixW - 1 - x, y)] = _leds[XY(y, x)];
        _leds[XY(x, _matrixH - 1 - y)] = _leds[XY(y, x)];
        _leds[XY(_matrixW - 1 - x, _matrixH - 1 - y)] = _leds[XY(x, y)];
      }
    }
  }

  // copy one diagonal triangle into the other one within a 16x16
  void MyNeoMatrix::Caleidoscope3() {
    uint8_t sCenterX = (_matrixW/2);
    uint8_t sCentreX = sCenterX-1;

    for (int x = 0; x <= sCentreX; x++) {
      for (int y = 0; y <= x; y++) {
        _leds[XY(x, y)] = _leds[XY(y, x)];
      }
    }
  }

  // copy one diagonal triangle into the other one within a 16x16 (90 degrees rotated compared to Caleidoscope3)
  void MyNeoMatrix::Caleidoscope4() {
    uint8_t sCenterX = (_matrixW/2);
    uint8_t sCentreX = sCenterX-1;
    uint8_t sCenterY = (_matrixH/2);
    uint8_t sCentreY = sCenterY-1;

    for (int x = 0; x <= sCentreX; x++) {
      for (int y = 0; y <= sCentreY - x; y++) {
        _leds[XY(sCentreY - y, sCentreX - x)] = _leds[XY(x, y)];
      }
    }
  }

  // copy one diagonal triangle into the other one within a 8x8
  void MyNeoMatrix::Caleidoscope5() 
  {
    for (int x = 0; x < _matrixW / 4; x++) {
      for (int y = 0; y <= x; y++) {
        _leds[XY(x, y)] = _leds[XY(y, x)];
      }
    }

    for (int x = _matrixW / 4; x < _matrixW / 2; x++) {
      for (int y = _matrixH / 4; y >= 0; y--) {
        _leds[XY(x, y)] = _leds[XY(y, x)];
      }
    }
  }

  void MyNeoMatrix::Caleidoscope6() {
    uint8_t sCenterX = (_matrixH/2);

    for (int x = 1; x < sCenterX; x++) {
      _leds[XY(7 - x, 7)] = _leds[XY(x, 0)];
    } //a
    for (int x = 2; x < sCenterX; x++) {
      _leds[XY(7 - x, 6)] = _leds[XY(x, 1)];
    } //b
    for (int x = 3; x < sCenterX; x++) {
      _leds[XY(7 - x, 5)] = _leds[XY(x, 2)];
    } //c
    for (int x = 4; x < sCenterX; x++) {
      _leds[XY(7 - x, 4)] = _leds[XY(x, 3)];
    } //d
    for (int x = 5; x < sCenterX; x++) {
      _leds[XY(7 - x, 3)] = _leds[XY(x, 4)];
    } //e
    for (int x = 6; x < sCenterX; x++) {
      _leds[XY(7 - x, 2)] = _leds[XY(x, 5)];
    } //f
    for (int x = 7; x < sCenterX; x++) {
      _leds[XY(7 - x, 1)] = _leds[XY(x, 6)];
    } //g
  }
  //   


