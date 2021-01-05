#include <ALS_neomatrix.h>

#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN    D4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    224

CRGB 			leds[NUM_LEDS];
MyNeoMatrix	    * _myMatrix = nullptr;

void setup()
{
	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

    _myMatrix = new MyNeoMatrix(leds, 16, 14,
            NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE
        );
    _myMatrix->_leds       = leds;
    _myMatrix->_numLeds    = NUM_LEDS;
    _myMatrix->_matrixW    = 16;
    _myMatrix->_matrixH    = 14; 
    _myMatrix->setRotation(3);     
    FastLED.clear();
    FastLED.show();	
}

void loop()
{
    _myMatrix->matrixTest();
}
