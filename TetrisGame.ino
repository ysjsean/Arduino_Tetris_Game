#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN 5
#define NUMPIXELS 20
#define SPEED 2
#define PIN2 6
#define PIN3 7
#define PIN4 8
#define PINL1 9
#define PINL2 10
#define PINL3 11
#define PINR1 4
#define PINR2 3
#define PINR3 2
#define BUTTON_LEFT A3
#define BUTTON_RIGHT A4

Adafruit_NeoPixel col1(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel col2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel col3(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel col4(NUMPIXELS, PIN4, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel colL1(NUMPIXELS, PINL1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel colL2(NUMPIXELS, PINL2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel colL3(NUMPIXELS, PINL3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel colR1(NUMPIXELS, PINR1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel colR2(NUMPIXELS, PINR2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel colR3(NUMPIXELS, PINR3, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int centerx = 0;
int centery1 = PIN;
int centery2 = PIN2;
int centery3 = PIN3;
int centery4 = PIN4;

// centery1b=centery1before
int centery1b = PIN;
int centery2b = PIN2;
int centery3b = PIN3;
int centery4b = PIN4;

int currentStateL;
int currentStateR;       // the current reading from the input pin
bool lightArray[20][10]; // record the light pixel
bool currentLanded = true;
long currentShape = -1;
long randNumber = -1;
int score = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_LEFT, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);
    randomSeed(analogRead(0));
    randNumber = random(0, 5);

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            lightArray[i][j] = false;
        }
    }

    randomShape(randNumber);
    col1.begin();
    col2.begin();
    col3.begin();
    col4.begin();
    colL1.begin();
    colL2.begin();
    colL3.begin();
    colR1.begin();
    colR2.begin();
    colR3.begin();
}

void loop()
{

    col1.setBrightness(10);
    col2.setBrightness(10);
    col3.setBrightness(10);
    col4.setBrightness(10);
    colL1.setBrightness(10);
    colL2.setBrightness(10);
    colL3.setBrightness(10);
    colR1.setBrightness(10);
    colR2.setBrightness(10);
    colR3.setBrightness(10);

    // shapeI();
    randomShape(randNumber);
}
// show all col
void showCol()
{
    col1.show();
    col2.show();
    col3.show();
    col4.show();
    colL1.show();
    colL2.show();
    colL3.show();
    colR1.show();
    colR2.show();
    colR3.show();
}

void randomShape(int currentShape)
{
    switch (currentShape)
    {
    case 0:
        if (lightArray[centerx][11 - centery2] + lightArray[centerx][11 - centery3] + lightArray[centerx + 2][11 - centery2] + lightArray[centerx + 2][11 - centery3] == 0)
        {
            shapeO();
        }
        else
        {
            // Game Over;
            endGame();
        }
        break;
    case 1:
        if (lightArray[centerx][11 - centery3] + lightArray[centerx + 2][11 - centery3] + lightArray[centerx + 2][11 - centery2] + lightArray[centerx + 4][11 - centery2] == 0)
        {
            shapeZ();
        }
        else
        {
            // Game Over;
            endGame();
        }

        break;
    case 2:
        if (lightArray[centerx][11 - centery3] + lightArray[centerx + 2][11 - centery3] + lightArray[centerx + 4][11 - centery3] + lightArray[centerx + 4][11 - centery2] == 0)
        {
            shapeL();
        }
        else
        {
            // Game Over;
            endGame();
        }
        break;
    case 3:
        if (lightArray[centerx + 2][11 - centery3] + lightArray[centerx][11 - centery2] + lightArray[centerx + 2][11 - centery2] + lightArray[centerx + 4][11 - centery2] == 0)
        {
            shapeT();
        }
        else
        {
            // Game Over;
            endGame();
        }
        break;
    case 4:
        if (lightArray[centerx][11 - centery3] + lightArray[centerx + 2][11 - centery3] + lightArray[centerx + 4][11 - centery3] + lightArray[centerx + 6][11 - centery3] == 0)
        {
            shapeI();
        }
        else
        {
            // Game Over;
            endGame();
        }
        break;
    default:
        break;
    }
    currentLanded = false;
}

// Game Over function
void endGame()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (11 - j)
            {
            case PIN:
                col1.setPixelColor(i, col1.Color(255, 0, 255));
                break;
            case PIN2:
                col2.setPixelColor(i, col2.Color(255, 0, 255));
                break;
            case PIN3:
                col3.setPixelColor(i, col3.Color(255, 0, 255));
                break;
            case PIN4:
                col4.setPixelColor(i, col4.Color(255, 0, 255));
                break;
            case PINL1:
                colL1.setPixelColor(i, colL1.Color(255, 0, 255));
                break;
            case PINL2:
                colL2.setPixelColor(i, colL2.Color(255, 0, 255));
                break;
            case PINL3:
                colL3.setPixelColor(i, colL3.Color(255, 0, 255));
                break;
            case PINR1:
                colR1.setPixelColor(i, colR1.Color(255, 0, 255));
                break;
            case PINR2:
                colR2.setPixelColor(i, colR2.Color(255, 0, 255));
                break;
            case PINR3:
                colR3.setPixelColor(i, colR3.Color(255, 0, 255));
                break;
            }
        }
    }
    showCol();
    while (1)
    {
    }
}

void shapeO()
{
    centery1b = centery1;
    centery2b = centery2;
    centery3b = centery3;
    centery4b = centery4;
    lightO(centerx);

    showCol();

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);

    if (currentStateL == HIGH && (lightArray[centerx + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][11 - centery3 - 1] == 0))
    {

        if (centery3 < PINL3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 += 1;
            centery2 += 1;
            centery3 += 1;
            centery4 += 1;
        }
    }
    if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][11 - centery2 + 1] == 0) && (lightArray[centerx + SPEED + 2][11 - centery2 + 1] == 0))
    {

        if (centery2 > PINR3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(500);

    if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][11 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][11 - centery3] == 0))
    {

        turnoffO(centerx);

        centerx = centerx + SPEED;
        showCol();
    }
    else
    {

        lightArray[centerx][11 - centery2] = true;
        lightArray[centerx + 2][11 - centery2] = true;
        lightArray[centerx][11 - centery3] = true;
        lightArray[centerx + 2][11 - centery3] = true;

        centerx = 0;
        centery1 = PIN;
        centery2 = PIN2;
        centery3 = PIN3;
        centery4 = PIN4;
        checkLine();
        showCol();
        randNumber = random(0, 5);
    }
}

// shapeL
void shapeL()
{
    centery1b = centery1;
    centery2b = centery2;
    centery3b = centery3;
    centery4b = centery4;
    lightL(centerx);

    showCol();

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);

    if (currentStateL == HIGH && (lightArray[centerx + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][11 - centery3 - 1] == 0))
    {

        if (centery3 < PINL3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 += 1;
            centery2 += 1;
            centery3 += 1;
            centery4 += 1;
        }
    }
    if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][11 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 4][11 - centery2 + 1] == 0))
    {

        if (centery2 > PINR3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(500);

    if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][11 - centery2] == 0) && (lightArray[centerx + 4 + SPEED][11 - centery3] == 0))
    {

        turnoffL(centerx);

        centerx = centerx + SPEED;
        showCol();
    }
    else
    {

        lightArray[centerx][11 - centery3] = true;
        lightArray[centerx + 2][11 - centery3] = true;
        lightArray[centerx + 4][11 - centery3] = true;
        lightArray[centerx + 4][11 - centery2] = true;

        centerx = 0;
        centery1 = PIN;
        centery2 = PIN2;
        centery3 = PIN3;
        centery4 = PIN4;
        checkLine();
        showCol();
        randNumber = random(0, 5);
    }
}

// shape Z
void shapeZ()
{
    centery1b = centery1;
    centery2b = centery2;
    centery3b = centery3;
    centery4b = centery4;
    lightZ(centerx);

    showCol();

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);

    if (currentStateL == HIGH && (lightArray[centerx + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][11 - centery2 - 1] == 0))
    {

        if (centery3 < PINL3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 += 1;
            centery2 += 1;
            centery3 += 1;
            centery4 += 1;
        }
    }
    if ((currentStateR == HIGH) && (lightArray[centerx + SPEED + 2][11 - centery2 + 1] == 0) && (lightArray[centerx + SPEED + 4][11 - centery2 + 1] == 0))
    {
        // clear(centerx-SPEED);
        if (centery2 > PINR3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(500);

    if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][11 - centery2] != 1) && (lightArray[centerx + 2 + SPEED][11 - centery3] != 1))
    {

        turnoffZ(centerx);

        centerx = centerx + SPEED;
        showCol();
    }
    else
    {

        lightArray[centerx + 2][11 - centery2] = true;
        lightArray[centerx + 4][11 - centery2] = true;
        lightArray[centerx][11 - centery3] = true;
        lightArray[centerx + 2][11 - centery3] = true;

        centerx = 0;
        centery1 = PIN;
        centery2 = PIN2;
        centery3 = PIN3;
        centery4 = PIN4;
        checkLine();
        showCol();
        randNumber = random(0, 5);
    }
}
// shapeT
void shapeT()
{
    centery1b = centery1;
    centery2b = centery2;
    centery3b = centery3;
    centery4b = centery4;
    lightT(centerx);

    showCol();

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);

    if ((currentStateL == HIGH) && (lightArray[centerx + 2 + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][11 - centery2 - 1] == 0))
    {

        if (centery3 < 11)
        {
            centery1 += 1;
            centery2 += 1;
            centery3 += 1;
            centery4 += 1;
        }
    }
    if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][11 - centery2 + 1] == 0) && (lightArray[centerx + 2 + SPEED][11 - centery2 + 1] == 0) && (lightArray[centerx + 4 + SPEED][11 - centery2 + 1] == 0))
    {
        if (centery2 > 2)
        {
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(500);

    if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][11 - centery2] != 1) && (lightArray[centerx + 2 + SPEED][11 - centery3] != 1))
    {
        turnoffT(centerx);
        centerx = centerx + SPEED;
        showCol();
    }
    else
    {
        lightArray[centerx][11 - centery2] = 1;
        lightArray[centerx + 2][11 - centery2] = 1;
        lightArray[centerx + 4][11 - centery2] = 1;
        lightArray[centerx + 2][11 - centery3] = 1;
        centerx = 0;
        centery1 = PIN;
        centery2 = PIN2;
        centery3 = PIN3;
        centery4 = PIN4;
        checkLine();
        showCol();
        randNumber = random(0, 5);
    }
}

// shape I
void shapeI()
{
    centery1b = centery1;
    centery2b = centery2;
    centery3b = centery3;
    centery4b = centery4;
    lightI(centerx);

    showCol();

    currentStateL = digitalRead(BUTTON_LEFT);
    currentStateR = digitalRead(BUTTON_RIGHT);

    if (currentStateL == HIGH && (lightArray[centerx + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][11 - centery3 - 1] == 0) && (lightArray[centerx + 6 + SPEED][11 - centery3 - 1] == 0))
    {
        if (centery3 < PINL3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 += 1;
            centery2 += 1;
            centery3 += 1;
            centery4 += 1;
        }
    }
    if ((currentStateR == HIGH) && (lightArray[centerx + SPEED + 2][11 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 4][11 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 6][11 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 6][11 - centery3 + 1] == 0))
    {
        if (centery2 > PINR3)
        {
            centery1b = centery1;
            centery2b = centery2;
            centery3b = centery3;
            centery4b = centery4;
            centery1 -= 1;
            centery2 -= 1;
            centery3 -= 1;
            centery4 -= 1;
        }
    }

    delay(500);

    if ((centerx < NUMPIXELS - 8) && (lightArray[centerx + 6 + SPEED][11 - centery3] != 1))
    {

        turnoffI(centerx);

        centerx = centerx + SPEED;
        showCol();
    }
    else
    {

        lightArray[centerx][11 - centery3] = true;
        lightArray[centerx + 2][11 - centery3] = true;
        lightArray[centerx + 4][11 - centery3] = true;
        lightArray[centerx + 6][11 - centery3] = true;

        centerx = 0;
        centery1 = PIN;
        centery2 = PIN2;
        centery3 = PIN3;
        centery4 = PIN4;
        checkLine();
        showCol();
        randNumber = random(0, 5);
    }
}

// check whether to clear the line
void checkLine()
{
    int product = 1;
    for (int i = 18; i > 0; i = i - 2)
    {
        product = 1;
        for (int j = 0; j < 10; j = j + 1)
        {
            product = product * lightArray[i][j];
        }

        if (product != 0)
        {
            score += 1;
            arrayUpdate(i);
            i = i + 2;
        }
    }
    arrayLight();
}
void arrayUpdate(int line)
{

    for (int i = line; i > 0; i = i - 2)
    {
        for (int j = 0; j < 10; j = j + 1)
        {
            lightArray[i][j] = lightArray[i - 2][j];
        }
    }
    for (int j = 0; j < 10; j = j + 1)
    {
        lightArray[0][j] = 0;
    }
}
// according to the lightArray to set pixel color
void arrayLight()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (11 - j)
            {
            case PIN:
                col1.setPixelColor(i, col1.Color(0, 0, 0));
                break;
            case PIN2:
                col2.setPixelColor(i, col2.Color(0, 0, 0));
                break;
            case PIN3:
                col3.setPixelColor(i, col3.Color(0, 0, 0));
                break;
            case PIN4:
                col4.setPixelColor(i, col4.Color(0, 0, 0));
                break;
            case PINL1:
                colL1.setPixelColor(i, colL1.Color(0, 0, 0));
                break;
            case PINL2:
                colL2.setPixelColor(i, colL2.Color(0, 0, 0));
                break;
            case PINL3:
                colL3.setPixelColor(i, colL3.Color(0, 0, 0));
                break;
            case PINR1:
                colR1.setPixelColor(i, colR1.Color(0, 0, 0));
                break;
            case PINR2:
                colR2.setPixelColor(i, colR2.Color(0, 0, 0));
                break;
            case PINR3:
                colR3.setPixelColor(i, colR3.Color(0, 0, 0));
                break;
            }
            if (lightArray[i][j] != 0)
            {
                switch (11 - j)
                {
                case PIN:
                    col1.setPixelColor(i, col1.Color(255, 0, 255));
                    break;
                case PIN2:
                    col2.setPixelColor(i, col2.Color(255, 0, 255));
                    break;
                case PIN3:
                    col3.setPixelColor(i, col3.Color(255, 0, 255));
                    break;
                case PIN4:
                    col4.setPixelColor(i, col4.Color(255, 0, 255));
                    break;
                case PINL1:
                    colL1.setPixelColor(i, colL1.Color(255, 0, 255));
                    break;
                case PINL2:
                    colL2.setPixelColor(i, colL2.Color(255, 0, 255));
                    break;
                case PINL3:
                    colL3.setPixelColor(i, colL3.Color(255, 0, 255));
                    break;
                case PINR1:
                    colR1.setPixelColor(i, colR1.Color(255, 0, 255));
                    break;
                case PINR2:
                    colR2.setPixelColor(i, colR2.Color(255, 0, 255));
                    break;
                case PINR3:
                    colR3.setPixelColor(i, colR3.Color(255, 0, 255));
                    break;
                }
            }
        }
    }
}

// turnoff
void turnoffO(int centerx)
{
    switch (centery1b)
    {
    case PIN:

        col2.setPixelColor(centerx, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
        col3.setPixelColor(centerx, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));

        break;
    case PIN2:

        col3.setPixelColor(centerx, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
        col4.setPixelColor(centerx, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

        break;
    case PIN3:

        col4.setPixelColor(centerx, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
        colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));

        break;
    case PIN4:

        colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
        colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));

        break;
    case PINL1:

        colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
        colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
        break;
    case PINR1:

        col1.setPixelColor(centerx, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
        col2.setPixelColor(centerx, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));

        break;
    case PINR2:

        colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
        col1.setPixelColor(centerx, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));

        break;
    case PINR3:

        colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
        colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));

        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
        colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
        colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));

        break;
    }
}

void turnoffL(int centerx)
{
    switch (centery1b)
    {
    case PIN:

        col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
        col3.setPixelColor(centerx, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));

        break;
    case PIN2:

        col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));
        col4.setPixelColor(centerx, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));

        break;
    case PIN3:

        col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));
        colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));

        break;
    case PIN4:

        colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));
        colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));

        break;
    case PINL1:

        colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));
        colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 4, colL3.Color(0, 0, 0));
        break;
    case PINR1:

        col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
        col2.setPixelColor(centerx, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));

        break;
    case PINR2:

        colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));
        col1.setPixelColor(centerx, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));

        break;
    case PINR3:

        colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));
        colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));

        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx + 4, colR3.Color(0, 0, 0));
        colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));

        break;
    }
}

void turnoffZ(int centerx)
{
    switch (centery1b)
    {
    case PIN:

        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
        col3.setPixelColor(centerx, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));

        break;
    case PIN2:

        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));
        col4.setPixelColor(centerx, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

        break;
    case PIN3:

        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));
        colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));

        break;
    case PIN4:

        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));
        colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));

        break;
    case PINL1:

        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));
        colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
        break;
    case PINR1:

        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
        col2.setPixelColor(centerx, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));

        break;
    case PINR2:

        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));
        col1.setPixelColor(centerx, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));

        break;
    case PINR3:

        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));
        colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));

        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
        colR3.setPixelColor(centerx + 4, colR3.Color(0, 0, 0));
        colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));

        break;
    }
}
void turnoffT(int centerx)
{
    switch (centery1b)
    {
    case PIN:

        col2.setPixelColor(centerx, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));

        break;
    case PIN2:

        col3.setPixelColor(centerx, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

        break;
    case PIN3:

        col4.setPixelColor(centerx, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));

        break;
    case PIN4:

        colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));

        break;
    case PINL1:

        colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
        break;
    case PINR1:

        col1.setPixelColor(centerx, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));

        break;
    case PINR2:

        colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));

        break;
    case PINR3:

        colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));

        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
        colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
        colR3.setPixelColor(centerx + 4, colR3.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));

        break;
    }
}

void turnoffI(int centerx)
{
    switch (centery1b)
    {
    case PIN:

        col3.setPixelColor(centerx, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));
        col3.setPixelColor(centerx + 6, col3.Color(0, 0, 0));

        break;
    case PIN2:

        col4.setPixelColor(centerx, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));
        col4.setPixelColor(centerx + 6, col4.Color(0, 0, 0));

        break;
    case PIN3:

        colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));
        colL1.setPixelColor(centerx + 6, colL1.Color(0, 0, 0));

        break;
    case PIN4:

        colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));
        colL2.setPixelColor(centerx + 6, colL2.Color(0, 0, 0));

        break;
    case PINL1:

        colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 4, colL3.Color(0, 0, 0));
        colL3.setPixelColor(centerx + 6, colL3.Color(0, 0, 0));
        break;
    case PINR1:

        col2.setPixelColor(centerx, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
        col2.setPixelColor(centerx + 6, col2.Color(0, 0, 0));

        break;
    case PINR2:

        col1.setPixelColor(centerx, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
        col1.setPixelColor(centerx + 6, col1.Color(0, 0, 0));

        break;
    case PINR3:

        colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));
        colR1.setPixelColor(centerx + 6, colR1.Color(0, 0, 0));

        break;
    case PINR3 - 1:
        colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));

        break;
    }
}
// light
void lightO(int centerx)
{
    switch (centery1)
    {
    case PIN:
        col2.setPixelColor(centerx, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        col3.setPixelColor(centerx, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
        break;
    case PIN2:
        col3.setPixelColor(centerx, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
        col4.setPixelColor(centerx, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        break;
    case PIN3:
        col4.setPixelColor(centerx, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        break;
    case PIN4:
        colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
        break;
    case PINL1:
        colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
        colL3.setPixelColor(centerx, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));
        break;
    case PINR1:
        col1.setPixelColor(centerx, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        col2.setPixelColor(centerx, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        break;
    case PINR2:
        colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        col1.setPixelColor(centerx, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        break;
    case PINR3:
        colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx, colR3.Color(255, 0, 255));
        colR3.setPixelColor(centerx + 2, colR3.Color(255, 0, 255));
        colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        break;
    }
}

void lightL(int centerx)
{
    switch (centery1)
    {
    case PIN:

        col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
        col3.setPixelColor(centerx, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 4, col3.Color(255, 0, 255));

        break;
    case PIN2:

        col3.setPixelColor(centerx + 4, col3.Color(255, 0, 255));
        col4.setPixelColor(centerx, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 4, col4.Color(255, 0, 255));

        break;
    case PIN3:

        col4.setPixelColor(centerx + 4, col4.Color(255, 0, 255));
        colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 4, colL1.Color(255, 0, 255));

        break;
    case PIN4:

        colL1.setPixelColor(centerx + 4, colL1.Color(255, 0, 255));
        colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 4, colL2.Color(255, 0, 255));

        break;
    case PINL1:

        colL2.setPixelColor(centerx + 4, colL2.Color(255, 0, 255));
        colL3.setPixelColor(centerx, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 4, colL3.Color(255, 0, 255));
        break;
    case PINR1:

        col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
        col2.setPixelColor(centerx, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));

        break;
    case PINR2:

        colR1.setPixelColor(centerx + 4, colR1.Color(255, 0, 255));
        col1.setPixelColor(centerx, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));

        break;
    case PINR3:

        colR2.setPixelColor(centerx + 4, colR2.Color(255, 0, 255));
        colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 4, colR1.Color(255, 0, 255));

        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx + 4, colR3.Color(255, 0, 255));
        colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 4, colR2.Color(255, 0, 255));

        break;
    }
}

void lightZ(int centerx)
{
    switch (centery1)
    {
    case PIN:

        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
        col3.setPixelColor(centerx, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));

        break;
    case PIN2:

        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 4, col3.Color(255, 0, 255));
        col4.setPixelColor(centerx, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));

        break;
    case PIN3:

        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 4, col4.Color(255, 0, 255));
        colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));

        break;
    case PIN4:

        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 4, colL1.Color(255, 0, 255));
        colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));

        break;
    case PINL1:

        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 4, colL2.Color(255, 0, 255));
        colL3.setPixelColor(centerx, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));
        break;
    case PINR1:

        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
        col2.setPixelColor(centerx, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));

        break;
    case PINR2:

        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 4, colR1.Color(255, 0, 255));
        col1.setPixelColor(centerx, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));

        break;
    case PINR3:

        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 4, colR2.Color(255, 0, 255));
        colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));

        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx + 2, colR3.Color(255, 0, 255));
        colR3.setPixelColor(centerx + 4, colR3.Color(255, 0, 255));
        colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));

        break;
    }
}
void lightT(int centerx)
{
    switch (centery1)
    {
    case PIN:

        col2.setPixelColor(centerx, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));

        break;
    case PIN2:
        col3.setPixelColor(centerx, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 4, col3.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        break;
    case PIN3:
        col4.setPixelColor(centerx, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 4, col4.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        break;
    case PIN4:
        colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 4, colL1.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));

        break;
    case PINL1:

        colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 4, colL2.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));
        break;
    case PINR1:
        col1.setPixelColor(centerx, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        break;
    case PINR2:
        colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 4, colR1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        break;
    case PINR3:
        colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 4, colR2.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx, colR3.Color(255, 0, 255));
        colR3.setPixelColor(centerx + 2, colR3.Color(255, 0, 255));
        colR3.setPixelColor(centerx + 4, colR3.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        break;
    }
}
void lightI(int centerx)
{
    switch (centery1)
    {
    case PIN:
        col3.setPixelColor(centerx, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 4, col3.Color(255, 0, 255));
        col3.setPixelColor(centerx + 6, col3.Color(255, 0, 255));
        break;
    case PIN2:

        col4.setPixelColor(centerx, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 4, col4.Color(255, 0, 255));
        col4.setPixelColor(centerx + 6, col4.Color(255, 0, 255));
        break;
    case PIN3:
        colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 4, colL1.Color(255, 0, 255));
        colL1.setPixelColor(centerx + 6, colL1.Color(255, 0, 255));
        break;
    case PIN4:
        colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 4, colL2.Color(255, 0, 255));
        colL2.setPixelColor(centerx + 6, colL2.Color(255, 0, 255));
        break;
    case PINL1:
        colL3.setPixelColor(centerx, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 4, colL3.Color(255, 0, 255));
        colL3.setPixelColor(centerx + 6, colL3.Color(255, 0, 255));
        break;
    case PINR1:
        col2.setPixelColor(centerx, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
        col2.setPixelColor(centerx + 6, col2.Color(255, 0, 255));
        break;
    case PINR2:
        col1.setPixelColor(centerx, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
        col1.setPixelColor(centerx + 6, col1.Color(255, 0, 255));
        break;
    case PINR3:

        colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 4, colR1.Color(255, 0, 255));
        colR1.setPixelColor(centerx + 6, colR1.Color(255, 0, 255));
        break;
    case PINR3 - 1:
        colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 4, colR2.Color(255, 0, 255));
        colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
        break;
    }
}