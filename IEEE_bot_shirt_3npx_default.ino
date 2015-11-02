#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 0
#define BULB_FREQ_DIV 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


// Sample colors:
uint32_t white         = strip.Color(24, 24, 24);
uint32_t hot_pink      = strip.Color(48, 0, 24);
uint32_t light_blue    = strip.Color(0, 24, 24);
uint32_t bright_blue   = strip.Color(10, 24, 50);
uint32_t leaf_green    = strip.Color(30, 44, 0);
uint32_t purple        = strip.Color(17, 0, 44);
uint32_t yellowOrange  = strip.Color(44, 30, 0);
uint32_t sapphire      = strip.Color(0, 50, 24);
uint32_t green         = strip.Color(0, 24, 0);
uint32_t red           = strip.Color(24, 0, 0);
uint32_t blue          = strip.Color(0, 0, 24);
uint32_t salmon_pink   = strip.Color(236, 79, 100); 
uint32_t cream         = strip.Color(246, 216, 180);
uint32_t lavender      = strip.Color(174, 113, 208);
uint32_t deep_purple   = strip.Color(91, 44, 86); 
uint32_t medium_purple = strip.Color(232, 100, 255);
uint32_t yellow        = strip.Color(200, 200, 20);
uint32_t mediumSeaGreen       = strip.Color(12, 36, 23);
uint32_t mediumSpringGreen    = strip.Color(0, 50, 20);
uint32_t lightGreen       = strip.Color(10, 50, 10);
uint32_t honeyDew         = strip.Color(30, 51, 30);
uint32_t rosyBrown        = strip.Color(38, 35, 35);
uint32_t thistle          = strip.Color(43, 24, 43);
uint32_t plum             = strip.Color(44, 20, 44);
uint32_t mediumOrchid     = strip.Color(44, 10, 44);
uint32_t mediumPurple     = strip.Color(44, 5, 44);
uint32_t mediumSlateBlue  = strip.Color(10, 10, 50);
uint32_t cornFlowerBlue   = strip.Color(5, 10, 50);
uint32_t skyBlue          = strip.Color(20, 30, 50);
uint32_t lightSkyBlue     = strip.Color(27, 30, 50);
uint32_t paleTurquoise    = strip.Color(20, 30, 48);
uint32_t powderBlue       = strip.Color(25, 35, 50);
uint32_t aquamarine       = strip.Color(25, 51, 42);
uint32_t turquoise        = strip.Color(13, 45, 42);
uint32_t mediumTurquoise  = strip.Color(14, 42, 41);
uint32_t lime             = strip.Color(0, 100, 0);

int brightness = 90;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {
  directional_color_fade(44, 20, 44, 1);    //plum
  directional_color_fade(0, 50, 24, 0);     //sapphire
  directional_color_fade(0, 50, 20, 1);     //medium_spring_green
  directional_color_fade(13, 45, 42, 0);    //turquoise
  directional_color_fade(30, 51, 30, 1);    //honeyDew
  directional_color_fade(38, 35, 35, 0);    //rosyBrown
  directional_color_fade(43, 24, 43, 1);    //thistle
  directional_color_fade(44, 10, 44, 0);    //medium_orchid
}

void directional_color_fade(int rStart, int gStart, int bStart, int dir) {
  //fade into or out of a color; dir controls the direction
  
  int Rstart = rStart;
  int Gstart = gStart;
  int Bstart = bStart;
  int Rend, Gend, Bend = 0;

  int n = 100; // larger values of 'n' will give a smoother/slower transition

  //Set color intensity based on cycle and fade direction
  for(int i = 0; i < n; i++) {
    for(int j = 0; j<strip.numPixels() - 1; j++) {
      float Rnew = Rstart + (Rend - Rstart) * (99*dir + i*(1-2*dir)) / n;
      float Gnew = Gstart + (Gend - Gstart) * (99*dir + i*(1-2*dir)) / n;
      float Bnew = Bstart + (Bend - Bstart) * (99*dir + i*(1-2*dir)) / n;
      strip.setPixelColor(j, strip.Color(Rnew, Gnew, Bnew));
    }

    //flash the last Neopixel (bulb) based on cycle and BULB_FREQ_DIV
    if (i%BULB_FREQ_DIV == 0) {
      strip.setPixelColor(strip.numPixels()-1, Wheel(random(0, 255)));
    }
    else {
      strip.setPixelColor(strip.numPixels()-1, strip.Color(0,0,0));
    }
    strip.setBrightness(brightness); strip.show();
    delay(30);
  }  
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}




///***  UNUSED NEOPIXEL FUNCTIONS BELOW ***///

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      //strip.setBrightness(30); 
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    //strip.setBrightness(30); 
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    //strip.setBrightness(30); 
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      //strip.setBrightness(30); 
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        //strip.setBrightness(30); 
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
