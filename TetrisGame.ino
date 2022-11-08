#include <Adafruit_NeoPixel.h>
//#include <FastLED.h>

#define PIN13 13 // input pin Neopixel is attached to
#define PIN12 12
#define PIN11 11
#define PIN10 10
#define PIN9 9
#define PIN8 8
#define PIN7 7
#define PIN6 6
#define PIN5 5
#define PIN4 4
#define PIN3 3
#define PIN2 2
#define PINA0 A0
#define PINA1 A1
#define PINA2 A2

#define NUMPIXELS 20 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_1 = Adafruit_NeoPixel(NUMPIXELS, PIN12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2 = Adafruit_NeoPixel(NUMPIXELS, PIN11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_3 = Adafruit_NeoPixel(NUMPIXELS, PIN10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_4 = Adafruit_NeoPixel(NUMPIXELS, PIN9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_5 = Adafruit_NeoPixel(NUMPIXELS, PIN8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_6 = Adafruit_NeoPixel(NUMPIXELS, PIN7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_7 = Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_8 = Adafruit_NeoPixel(NUMPIXELS, PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_9 = Adafruit_NeoPixel(NUMPIXELS, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_10 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_11 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_12 = Adafruit_NeoPixel(NUMPIXELS, PINA0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_13 = Adafruit_NeoPixel(NUMPIXELS, PINA1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_14 = Adafruit_NeoPixel(NUMPIXELS, PINA2, NEO_GRB + NEO_KHZ800);

/*Adafruit_NeoPixel px[] = {
  Adafruit_NeoPixel(NUMPIXELS, PIN13, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN12, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN11, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN10, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN9, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN8, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN7, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_GRB + NEO_KHZ800),

}*/
int delayval = 100; // timing delay in milliseconds

// uint16_t colors[3];

const long colors[7] =
    {
        0x009900, // green S
        0xFF0000, // red Z
        0xFF8000, // orange L
        0x000044, // blue J
        0xFFFF00, // yellow O
        0xFF00FF, // purple T
        0x00FFFF  // cyan I
};

int count = 0;

void setup()
{
    // Initialize the NeoPixel library.
    initialise();
}

void loop()
{

    for (int i = 0; i < NUMPIXELS; i++)
    {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

        pixels.setPixelColor(i, colors[count]);
        pixels_1.setPixelColor(i, colors[count]);
        pixels_2.setPixelColor(i, colors[count]);
        pixels_3.setPixelColor(i, colors[count]);
        pixels_4.setPixelColor(i, colors[count]);
        pixels_5.setPixelColor(i, colors[count]);
        pixels_6.setPixelColor(i, colors[count]);
        pixels_7.setPixelColor(i, colors[count]);
        pixels_8.setPixelColor(i, colors[count]);
        pixels_9.setPixelColor(i, colors[count]);
        pixels_10.setPixelColor(i, colors[count]);
        pixels_11.setPixelColor(i, colors[count]);
        pixels_12.setPixelColor(i, colors[count]);
        pixels_13.setPixelColor(i, colors[count]);
        pixels_14.setPixelColor(i, colors[count]);
        count++;
        if (count > 6)
        {
            count = 0;
        }

        // This sends the updated pixel color to the hardware.
        pixels.show();
        pixels_1.show();
        pixels_2.show();
        pixels_3.show();
        pixels_4.show();
        pixels_5.show();
        pixels_6.show();
        pixels_7.show();
        pixels_8.show();
        pixels_9.show();
        pixels_10.show();
        pixels_11.show();
        pixels_12.show();
        pixels_13.show();
        pixels_14.show();

        // Delay for a period of time (in milliseconds).
        delay(delayval);

        //}
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_1.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_2.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_3.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_4.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_5.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_6.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_7.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_8.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_9.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_10.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_11.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_12.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_13.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels_14.setPixelColor(i, pixels.Color(0, 0, 0));
    }
}

void initialise()
{
    pixels.begin();
    pixels_1.begin();
    pixels_2.begin();
    pixels_3.begin();
    pixels_4.begin();
    pixels_5.begin();
    pixels_6.begin();
    pixels_7.begin();
    pixels_8.begin();
    pixels_9.begin();
    pixels_10.begin();
    pixels_11.begin();
    pixels_12.begin();
    pixels_13.begin();
    pixels_14.begin();
}
