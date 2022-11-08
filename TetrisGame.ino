#include <Adafruit_NeoPixel.h>
#ifdef AVR
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 5
#define NUMPIXELS 20
#define SPEED 2
#define PIN2 6
#define PIN3 7
#define PIN4 8
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
int currentStateR;      // the current reading from the input pin
int lightArray[10][20]; // record the light pixel

bool currentLanded = true;
long currentShape = -1;
long randNumber = -1;

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
    col1.setPin(centery1);
    col2.setPin(centery2);
    col3.setPin(centery3);
    col4.setPin(centery4);

    col1.setBrightness(10);
    col2.setBrightness(10);
    col3.setBrightness(10);
    col4.setBrightness(10);

    randomShape();
    // shapeI();
}

void randomShape()
{
    if (currentLanded)
    {
        randomSeed(analogRead(0));
        randNumber = random(0, 5);
    }

    currentShape = randNumber;
    Serial.println(currentShape);

    switch (currentShape)
    {
    case 0:
        shapeO();
        break;
    case 1:
        shapeZ();
        break;
    case 2:
        shapeL();
        break;
    case 3:
        shapeT();
        break;
    case 4:
        shapeI();
        break;
    default:
        break;
    }

    currentLanded = false;
}

void shapeO()
{
    lightO(centerx);

    col1.show();
    col2.show();
    col3.show();
    col4.show();

    if (centerx < NUMPIXELS - 3)
    {
        centerx = centerx + SPEED;
    }

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);
    // Serial.println(currentState);
    if (currentStateL == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery3 < 11)
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
        if (centery2 > 2)
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
    else
    {
        lightArray[col2.getPin()][centerx] = 1;
        lightArray[col2.getPin()][centerx + 2] = 1;
        lightArray[col3.getPin()][centerx] = 1;
        lightArray[col3.getPin()][centerx + 2] = 1;
        centerx = 0;
    }

    col1.show();
    col2.show();
    col3.show();
    col4.show();
}

// shapeZ
void shapeI()
{
    lightI(centerx);

    col1.show();
    col2.show();
    col3.show();
    col4.show();

    if (centerx < NUMPIXELS - 7)
    {
        centerx = centerx + SPEED;
    }

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);
    // Serial.println(currentState);
    if (currentStateL == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery3 < 11)
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
        if (centery3 > 2)
        {
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(1000);

    if (centerx < NUMPIXELS - 7)
    {
        turnoffI(centerx - SPEED);
    }
    else
    {
        lightArray[col3.getPin()][centerx] = 1;
        lightArray[col3.getPin()][centerx + 2] = 1;
        lightArray[col3.getPin()][centerx + 4] = 1;
        lightArray[col3.getPin()][centerx + 6] = 1;
        centerx = 0;
    }

    col1.show();
    col2.show();
    col3.show();
    col4.show();
}

void shapeZ()
{
    lightZ(centerx);

    col1.show();
    col2.show();
    col3.show();
    col4.show();

    if (centerx < NUMPIXELS - 5)
    {
        centerx = centerx + SPEED;
    }

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);
    // Serial.println(currentState);
    if (currentStateL == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery3 < 11)
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
        if (centery2 > 2)
        {
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(1000);

    if (centerx < NUMPIXELS - 5)
    {
        turnoffZ(centerx - SPEED);
    }
    else
    {
        lightArray[col2.getPin()][centerx] = 1;
        lightArray[col2.getPin()][centerx + 2] = 1;
        lightArray[col3.getPin()][centerx] = 1;
        lightArray[col3.getPin()][centerx + 2] = 1;
        centerx = 0;
    }

    col1.show();
    col2.show();
    col3.show();
    col4.show();
}

void shapeT()
{
    lightT(centerx);

    col1.show();
    col2.show();
    col3.show();
    col4.show();

    if (centerx < NUMPIXELS - 5)
    {
        centerx = centerx + SPEED;
    }

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);
    // Serial.println(currentState);
    if (currentStateL == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery3 < 11)
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
        if (centery2 > 2)
        {
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(1000);

    if (centerx < NUMPIXELS - 5)
    {
        turnoffT(centerx - SPEED);
    }
    else
    {
        lightArray[col2.getPin()][centerx] = 1;
        lightArray[col2.getPin()][centerx + 2] = 1;
        lightArray[col2.getPin()][centerx + 4] = 1;
        lightArray[col3.getPin()][centerx + 2] = 1;
        centerx = 0;
    }

    col1.show();
    col2.show();
    col3.show();
    col4.show();
}

void shapeL()
{
    lightL(centerx);

    col1.show();
    col2.show();
    col3.show();
    col4.show();

    if (centerx < NUMPIXELS - 5)
    {
        centerx = centerx + SPEED;
    }

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);
    // Serial.println(currentState);
    if (currentStateL == HIGH)
    {
        // clear(centerx-SPEED);
        if (centery3 < 11)
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
        if (centery2 > 2)
        {
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(1000);

    if (centerx < NUMPIXELS - 5)
    {
        turnoffL(centerx - SPEED);
    }
    else
    {
        lightArray[col2.getPin()][centerx] = 1;
        lightArray[col2.getPin()][centerx + 2] = 1;
        lightArray[col3.getPin()][centerx] = 1;
        lightArray[col3.getPin()][centerx + 2] = 1;
        centerx = 0;
    }

    col1.show();
    col2.show();
    col3.show();
    col4.show();
}

// turnoff
void turnoffO(int centerx)
{
    col2.setPixelColor(centerx, col1.Color(0, 0, 0));
    col2.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx, col2.Color(0, 0, 0));
    col3.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
}

void turnoffZ(int centerx)
{
    col2.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
    col2.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx, col2.Color(0, 0, 0));
    col3.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
}

void turnoffL(int centerx)
{
    col3.setPixelColor(centerx, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
    col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
}

void turnoffT(int centerx)
{
    col2.setPixelColor(centerx, col1.Color(0, 0, 0));
    col2.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
    col2.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
}

void turnoffI(int centerx)
{
    col3.setPixelColor(centerx, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
    col3.setPixelColor(centerx + 6, col1.Color(0, 0, 0));
}

// light
void lightO(int centerx)
{

    col2.setPixelColor(centerx, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx, col2.Color(255, 0, 255));
    col3.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
}

void lightZ(int centerx)
{
    col2.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx, col2.Color(255, 0, 255));
    col3.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
}

void lightL(int centerx)
{
    col3.setPixelColor(centerx, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
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
    col3.setPixelColor(centerx, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
    col3.setPixelColor(centerx + 6, col1.Color(255, 0, 255));
}
