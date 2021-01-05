#ifndef ALS_NEOMATRIX_H
	#define ALS_NEOMATRIX_H 
	#include <Arduino.h>
	#include <FastLED.h>
	#include <FastLED_NeoMatrix.h>
	
	uint8_t mapsin8(uint8_t theta, uint8_t lowest = 0, uint8_t highest = 255);
	uint8_t mapcos8(uint8_t theta, uint8_t lowest = 0, uint8_t highest = 255);
	
	class MyNeoMatrix : public FastLED_NeoMatrix
	{

	public:

			int 	_numLeds;
			int 	_matrixW;
			int 	_matrixH;
			CRGB * 	_leds;
					
	    MyNeoMatrix(CRGB *leds, uint8_t w, uint8_t h, uint8_t matrixType);

	    void 		Initialize(MyNeoMatrix *object );

		uint8_t 	getRotation();

		uint16_t 	getNumLeds();

		uint8_t 	getCenterX();

		uint8_t 	getCenterY();

		uint8_t 	getDimension();

		CRGB *		getLeds();

		void 		setCurrentLimit(uint32_t maxCurrent);

		void 		fill(CRGB color, bool shouldShow);

		void 		fillProgress(double progress);

		void 		setLed(uint16_t index, CRGB color);

		void 		fadeToBlackBy(uint16_t index, uint8_t step);

		void 		fadeToBlackBy(uint8_t step);

		void 		dimAll(uint8_t value);

		uint8_t 	wrapX(int8_t x);

		uint8_t 	wrapY(int8_t y);

		void 		fader(uint8_t step);

		void 		fadePixel(uint8_t x, uint8_t y, uint8_t step);

		uint32_t 	colorcode(const CRGB &color);

		void 		applyBlur2d(uint8_t amount);

		void 		applyBlur2d(uint8_t w, uint8_t h, uint8_t amount);

		void 		matrixTest();

    	void 		clear(bool shouldShow = false);

uint16_t XYS( uint8_t x, uint8_t y);
int _XY(int x, int y);
int _XY_(int x, int y);

		uint16_t 	getPixelNumberXY(uint8_t x, uint8_t y);

		uint16_t 	getPixelNumber_XY(uint8_t x, uint8_t y);

		void 		drawPixelXY(uint8_t x, uint8_t y, CRGB color);

		void 		drawPixel_XY(uint8_t x, uint8_t y, CRGB color);

		void 		drawLineXY(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, CRGB color);

		CRGB 		getPixColor(uint16_t number);

		CRGB 		getPixColorXY(uint8_t x, uint8_t y);

		void 		tintPixelXY(uint8_t x, uint8_t y, CRGB color);

		void 		shadePixelXY(uint8_t x, uint8_t y, CRGB color);

		void 		blendPixelXY(uint8_t x, uint8_t y, const CRGB &color, uint8_t amount);

		void 		dimPixelXY(uint8_t x, uint8_t y, uint8_t value);

		void 		fillRectXY(uint8_t x, uint8_t y, uint8_t w, uint8_t h, CRGB color);

		void 		fadePixelXY(uint8_t x, uint8_t y, uint8_t step);

		void 		SpiralStream(int x, int y, int r, byte dimm);
    	CRGB 		ColorFromCurrentPalette(CRGBPalette16 currentPalette, uint8_t index = 0, uint8_t brightness = 255, TBlendType blendType = LINEARBLEND);
		void 		BresenhamLine(int x0, int y0, int x1, int y1, CRGB color);
		void 		BresenhamLine(CRGBPalette16 currentPalette, int x0, int y0, int x1, int y1, byte colorIndex);

	
		void Caleidoscope1();
		void Caleidoscope2();
		void Caleidoscope3();
		void Caleidoscope4();
		void Caleidoscope5();
		void Caleidoscope6(); 
	};
	MyNeoMatrix * MyNeoMatrix_instance();

	
#endif