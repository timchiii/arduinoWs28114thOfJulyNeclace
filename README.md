# Arduino ws2811 4th Of July Neclace
A small string of ws2811 leds run by an Arduino pro mini using the FastLED library to display 4th of July themed light patterns. Code is written to allow any length of LED string. Test video: https://www.youtube.com/watch?v=k_DKa39Nn0M

There are 4 functions for different lighting patterns. Each function accepts an integer value for the quantity of times to show that pattern. I finally decided on randomizing the pattern and how many times to run it on each loop.

Functions:
  RWBflash - flashes all red, all white, all blue
  RWBChase - incrementally (circle effect), light up all red, chase with black, chase with white, chase with black, chase with blue, chase with Black
  RWB3Chase - 1 red, 1 white, and 1 blue light move around the strand 
  RWBsparkles - lighting alternates between the different colors to give a sparkling effect

Sleep Mode trick:
Thank you: Edgar Bonet! https://arduino.stackexchange.com/questions/32378/how-do-i-repurpose-arduinos-reset-button

I used Edgar's trick and allocated but did not initialize a variable for mode. The idea here is the device will have random values in its memory wherever the mode integer is allocated. Because that space isn't initialized, the value isn't reset to zero each time so it can be used a a toggle. Upon power on the value of mode is probably unreadable junk so incrementing it will "probably" do junk + 1, resulting in 1. I used a > instead of = on the off chance the uninitilized space used by mode might have an integer greater than 1 present.

const unsigned int NUMBER_OF_MODES = 1;
__attribute__((section(".noinit"))) unsigned int mode;

mode++;
if (mode > NUMBER_OF_MODES)
  mode = 0;
