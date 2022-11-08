#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 4
#define NUMPIXELS 20
#define SPEED 2
#define PIN2 5
#define PIN3 6
#define PIN4 7
#define BUTTON_LEFT A3
#define BUTTON_RIGHT A4

Adafruit_NeoPixel col1(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel col2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel col3(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel col4(NUMPIXELS, PIN4, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int centerx = 0;
int centery1 = PIN;
int centery2 = PIN2;
int centery3 = PIN3;
int centery4 = PIN4;

int currentStateL;
int currentStateR; // the current reading from the input pin

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_LEFT, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);
    col1.begin();
    col2.begin();
    col3.begin();
    col4.begin();
}

void loop()
{
    Serial.println("xxxxxxxxxxxxx");
    Serial.println(col1.getPin());
    Serial.println(col2.getPin());
    Serial.println(col3.getPin());
    Serial.println(col4.getPin());

    // clear();

    col1.setPin(centery1);
    col2.setPin(centery2);
    col3.setPin(centery3);
    col4.setPin(centery4);
    //原先clear在这里

    col1.setBrightness(10);
    col2.setBrightness(10);
    col3.setBrightness(10);
    col4.setBrightness(10);

    lightO(centerx);

    col1.show();
    col2.show();
    col3.show();
    col4.show();

    if (centerx < NUMPIXELS - 4)
    {
        centerx = centerx + SPEED;
    }

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);
    // Serial.println(currentState);
    if (currentStateL == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery2 < 11)
        {
            centery1 += 1;
            centery2 += 1;
            centery3 += 1;
            centery4 += 1;
        }
    }
    if (currentStateR == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery1 > 2)
        {
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(1000);

    if (centerx < NUMPIXELS - 3)
    {
        turnoffO(centerx - SPEED);
    }

    col1.show();
    col2.show();
    col3.show();
    col4.show();
}

void turnoffO(int centerx)
{

    col1.setPixelColor(centerx, col1.Color(0, 0, 0));
    col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
    col2.setPixelColor(centerx, col2.Color(0, 0, 0));
    col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
}

void lightO(int centerx)
{

    col1.setPixelColor(centerx, col1.Color(255, 0, 255));
    col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx, col2.Color(255, 0, 255));
    col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
}

void lightZ(int centerx)
{
    col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx, col2.Color(255, 0, 255));
    col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
}

void lightL(int centerx)
{
    col2.setPixelColor(centerx, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
}

void lightT(int centerx)
{
    col2.setPixelColor(centerx, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
}

void lightI(int centerx)
{
    col2.setPixelColor(centerx, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 6, col1.Color(255, 0, 255));
}