#include "LowPower.h"
#include <FastLED.h>
#define NUM_LEDS 12
#define DATA_PIN 3
#define BRIGHTNESS 75
#define RWB_WAIT 250
#define LOOP_WAIT 50
#define LOOP_PAUSE 650
#define FLASH_WAIT 500
#define SPARKLE_DELAY 175

CRGB leds[NUM_LEDS];

//allocate but do not initialize variable for mode
//thank you Edgar Bonet! https://arduino.stackexchange.com/questions/32378/how-do-i-repurpose-arduinos-reset-button

const unsigned int NUMBER_OF_MODES = 1;
__attribute__((section(".noinit"))) unsigned int mode;

void setup()
{
  //Serial.begin(115200);
  //Serial.print("Starting mode:");
  //Serial.println(mode);
  
  //initialize LEDs and turn them all off
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  
  //incremend mode by one, if greater than 1 reset to zero
  mode++;
  if (mode > NUMBER_OF_MODES)
    mode = 0;
}

void RWBflash(int loops)
{
  for (int i = 1; i <= loops; i++)
  {
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      leds[i] = CRGB::Red;
    }
    FastLED.delay(FLASH_WAIT);
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      leds[i] = CRGB::White;
    }
    FastLED.delay(FLASH_WAIT);
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      leds[i] = CRGB::Blue;
    }
    FastLED.delay(FLASH_WAIT);
  }
}

void RWBChase(int loops)
{
  for (int i = 1; i <= loops; i++)
  { //incrementally turn all red
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      leds[i] = CRGB::Red;
      FastLED.delay(LOOP_WAIT);
    }
    //incrementally turn all white
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      leds[i] = CRGB::White;
      FastLED.delay(LOOP_WAIT);
    }
    //incrementally turn all blue
    for (int i = 0; i <= NUM_LEDS; i++)
    {
      leds[i] = CRGB::Blue;
      FastLED.delay(LOOP_WAIT);
    }
  }
}

void RWB3chase(int loops)
{
  FastLED.clear();
  for (int i = 0; i <= loops; i++)
  {
    int white;
    int blue;
    int black;
    for (int red = 0; red <= NUM_LEDS; red++)
    {
      //find white led
      if (red >= 1)
      {
        white = red - 1;
      }
      else
      {
        white = NUM_LEDS;
      }

      if (white >= 1)
      {
        blue = white - 1;
      }
      else
      {
        blue = NUM_LEDS;
      }

      if (blue >= 1)
      {
        black = blue - 1;
      }
      else
      {
        black = NUM_LEDS;
      }
      leds[red] = CRGB(100, 0, 0);
      leds[white] = CRGB(100, 100, 100);
      leds[blue] = CRGB(0, 0, 255);
      leds[black] = CRGB::Black;
      FastLED.show();
      FastLED.delay(RWB_WAIT);
    }
  }
}

void RWBsparkles(int loops)
{
  for (int i = 1; i <= loops; i++)
  {

    for (int i = 0; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::Red;
    }
    for (int i = 1; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::White;
    }
    for (int i = 2; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::Blue;
    }
    FastLED.delay(SPARKLE_DELAY);

    for (int i = 0; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::White;
    }
    for (int i = 1; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::Blue;
    }
    for (int i = 2; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::Red;
    }
    FastLED.delay(SPARKLE_DELAY);
    for (int i = 0; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::Blue;
    }
    for (int i = 1; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::Red;
    }
    for (int i = 2; i <= NUM_LEDS; i += 3)
    {
      leds[i] = CRGB::White;
    }
    FastLED.delay(SPARKLE_DELAY);
  }
}

void loop()
{
  /*
Options:
  RWBflash - flashes all red, all white, all blue
  RWBChase - incrementally light up all red, chase with black, chase with white, chase with black, chase with blue, chase with Black
  RWB3Chase - 1 red, 1 white, and 1 blue light with chase around together
  RWBsparkles - lighting alternates between the different colors
*/
  
  //generate random numbers for pattern and quantities
  int randFunc = random(4);
  int randFlashChase = random(1, 4);
  int randSparkles = random(3, 10);
  
  //Serial.print("mode:");
  //Serial.println(mode);
  
  //switch case for mode 0 (lights) or mode 1 (sleep)
  switch (mode)
  {
  case 0:
    
    //switch case for light pattern
    switch (randFunc)
    {
    case 0:
      RWB3chase(randFlashChase);
      break;
    case 1:
      RWBflash(randFlashChase);
      break;
    case 2:
      RWBChase(randFlashChase);
      break;
    case 3:
      RWBsparkles(randSparkles);
      break;
    }
    break;
  case 1:
    //turn off all leds and enter sleep mode
    FastLED.clear();
    FastLED.show();
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    break;
  }
}
