#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN 11
#define NUMPIXELS 38
#define SPEED 2
#define PIN2 12
#define PIN3 13
#define PIN4 14
#define PINL1 15
#define PINL2 16
#define PINL3 17
#define PINR1 10
#define PINR2 9
#define PINR3 8
#define BUTTON_LEFT A3
#define BUTTON_RIGHT A4
#define BUTTON_ROTATE A5
#define BUTTON_SPEEDUP A2
#define BUTTON_START A1
#define BUTTON_DROP A8

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
// L rgb(220,0,0) 1
// I rgb(0,0,255) 2
// O rgb(0,128,0) 3
// Z rgb(255,255,0) 4
// T rgb(255,0,255) 5

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int centerx = 0;
int centery1 = PIN;
int centery2 = PIN2;
int centery3 = PIN3;
int centery4 = PIN4;
int highestScore = 0;

// centery1b=centery1before
int centery1b = PIN;
int centery2b = PIN2;
int centery3b = PIN3;
int centery4b = PIN4;

int currentStateL;
int currentStateR; // the current reading from the input pin
int currentRotateState;
int SpeedUp;
int currentStateStart;
int currentStateDrop;
// bool lightArray[38][10];//record the light pixel
int lightArray[38][10]; // record the light pixel
bool currentLanded = true;
long currentShape = -1;
long randNumber = -1;
int score = 0;
int currentL = 0;
int currentT = 0;
int currentZ = 0;
int currentI = 0;

const int ones_score_pin[] = {22, 23, 24, 25, 26, 27, 28};
const int tens_score_pin[] = {29, 30, 31, 32, 33, 34, 35};

const int ones_highscore_pin[] = {36, 37, 38, 39, 40, 41, 42};
const int tens_highscore_pin[] = {43, 44, 45, 46, 47, 48, 49};
//#define button 10

uint8_t current_button_state;
uint8_t previous_button_state;

const int numbers[10][7] =
    {
        {0, 0, 0, 0, 0, 0, 1}, // 0
        {1, 1, 0, 0, 1, 1, 1}, // 1
        {0, 0, 1, 0, 0, 1, 0}, // 2
        {1, 0, 0, 0, 0, 1, 0}, // 3
        {1, 1, 0, 0, 1, 0, 0}, // 4
        {1, 0, 0, 1, 0, 0, 0}, // 5
        {0, 0, 0, 1, 0, 0, 0}, // 6
        {1, 1, 0, 0, 0, 0, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0}, // 8
        {1, 0, 0, 0, 0, 0, 0}, // 9
};
int incomingByte = 0;
int counter = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_LEFT, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);
    pinMode(BUTTON_ROTATE, INPUT);
    pinMode(BUTTON_SPEEDUP, INPUT);
    randomSeed(analogRead(0));
    randNumber = random(0, 5);

    for (int i = 0; i < 38; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            lightArray[i][j] = 0;
        }
    }

    // put your setup code here, to run once:
    for (int x = 0; x < 7; x++)
    {
        pinMode(ones_score_pin[x], OUTPUT);
        pinMode(tens_score_pin[x], OUTPUT);
        pinMode(ones_highscore_pin[x], OUTPUT);
        pinMode(tens_highscore_pin[x], OUTPUT);
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

    displayScore(score);
    displayHighscore(highestScore);
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
    if (lightArray[0][4] == 0 && lightArray[0][5] == 0)
    {
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
        }
    }
    else
    {
        endGame();
    }

    currentLanded = false;
}

// Game Over function
// all pixels set to white
void endGame()
{
    for (int i = 0; i < 38; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (17 - j)
            {
            case PIN:
                col1.setPixelColor(i, col1.Color(255, 255, 255));
                break;
            case PIN2:
                col2.setPixelColor(i, col2.Color(255, 255, 255));
                break;
            case PIN3:
                col3.setPixelColor(i, col3.Color(255, 255, 255));
                break;
            case PIN4:
                col4.setPixelColor(i, col4.Color(255, 255, 255));
                break;
            case PINL1:
                colL1.setPixelColor(i, colL1.Color(255, 255, 255));
                break;
            case PINL2:
                colL2.setPixelColor(i, colL2.Color(255, 255, 255));
                break;
            case PINL3:
                colL3.setPixelColor(i, colL3.Color(255, 255, 255));
                break;
            case PINR1:
                colR1.setPixelColor(i, colR1.Color(255, 255, 255));
                break;
            case PINR2:
                colR2.setPixelColor(i, colR2.Color(255, 255, 255));
                break;
            case PINR3:
                colR3.setPixelColor(i, colR3.Color(255, 255, 255));
                break;
            }
        }
    }
    showCol();
    for (int i = 0; i < 38; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            lightArray[i][j] = 0;
        }
    }
    // 10.20新加
    centerx = 0;
    if (highestScore <= score)
    {
        highestScore = score;
    }
    while (1)
    {
        currentStateStart = digitalRead(BUTTON_START);
        if (currentStateStart == HIGH)
        {
            for (int i = 0; i < 38; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    switch (17 - j)
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
                }
            }
            showCol();

            Serial.begin(9600);
            pinMode(BUTTON_LEFT, INPUT);
            pinMode(BUTTON_RIGHT, INPUT);
            pinMode(BUTTON_ROTATE, INPUT);
            pinMode(BUTTON_SPEEDUP, INPUT);
            pinMode(BUTTON_START, INPUT);
            randomSeed(analogRead(0));
            randNumber = random(0, 5);

            for (int i = 0; i < 38; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    lightArray[i][j] = 0;
                }
            }
            score = 0;
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
            break;
        }
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
    SpeedUp = digitalRead(BUTTON_SPEEDUP);
    currentStateDrop = digitalRead(BUTTON_DROP);

    if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0))
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
    if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + SPEED + 2][17 - centery2 + 1] == 0))
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
    // Change Speed
    if (SpeedUp == HIGH)
    {
        delay(100);
    }
    else
    {
        delay(500);
    }
    if (currentStateDrop == HIGH)
    {
        turnoffO(centerx);
        while ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
        {
            centerx = centerx + SPEED;
            // showCol();
        }

        lightArray[centerx][17 - centery2] = 3;
        lightArray[centerx + 2][17 - centery2] = 3;
        lightArray[centerx][17 - centery3] = 3;
        lightArray[centerx + 2][17 - centery3] = 3;
        lightO(centerx);
        centerx = 0;
        centery1 = PIN;
        centery2 = PIN2;
        centery3 = PIN3;
        centery4 = PIN4;
        checkLine();
        showCol();
        randNumber = random(0, 5);
    }

    else if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
    {

        turnoffO(centerx);

        centerx = centerx + SPEED;
        showCol();
    }
    else
    {

        lightArray[centerx][17 - centery2] = 3;
        lightArray[centerx + 2][17 - centery2] = 3;
        lightArray[centerx][17 - centery3] = 3;
        lightArray[centerx + 2][17 - centery3] = 3;

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
    currentRotateState = digitalRead(BUTTON_ROTATE); //记录是否按下rotate button
    SpeedUp = digitalRead(BUTTON_SPEEDUP);
    currentStateDrop = digitalRead(BUTTON_DROP);
    // need to add more conditions 不同形态的
    if (currentL == 0)
    {
        // move left
        if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery3 - 1] == 0))
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
        // move right
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 4][17 - centery2 + 1] == 0))
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
        // rotate
        if ((currentRotateState == HIGH) && (centery2 > PINR3) && (lightArray[centerx + 2][17 - centery2] == 0) && (lightArray[centerx + 2][17 - centery1] == 0))
        {
            // turnoff current state
            turnoffL(centerx);
            // light next state
            currentL = (currentL + 1) % 4;
            lightL(centerx);
        }
    }
    else if (currentL == 1)
    {
        if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0))
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery1 + 1] == 0) && (lightArray[centerx + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + SPEED][17 - centery3 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 + 1] == 0))
        {

            if (centery1 > PINR3)
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
        // rotate
        if ((currentRotateState == HIGH) && (lightArray[centerx + 2][17 - centery2] == 0) && (lightArray[centerx + 4][17 - centery2] == 0) && (lightArray[centerx + 6][17 - centery2] == 0))
        {
            // turnoff current state
            turnoffL(centerx);
            // light next state
            currentL = (currentL + 1) % 4;
            lightL(centerx);
        }
    }
    else if (currentL == 2)
    {
        if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2 - 1] == 0))
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2 + 1] == 0))
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
        // rotate
        if ((currentRotateState == HIGH) && (centery2 > PINR3) && (lightArray[centerx + 2][17 - centery1] == 0) && (lightArray[centerx + 4][17 - centery1] == 0) && (lightArray[centerx + 4][17 - centery3] == 0))
        {
            // turnoff current state
            turnoffL(centerx);
            // light next state
            currentL = (currentL + 1) % 4;
            lightL(centerx);
        }
    }
    else if (currentL == 3)
    {
        if (currentStateL == HIGH && (lightArray[centerx + 2 + SPEED][17 - centery1 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0))
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery1 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery1 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 + 1] == 0))
        {

            if (centery1 > PINR3)
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
        // rotate
        if ((currentRotateState == HIGH) && (lightArray[centerx + 4][17 - centery3] == 0) && (lightArray[centerx + 6][17 - centery3] == 0) && (lightArray[centerx + 6][17 - centery2] == 0))
        {
            // turnoff current state
            turnoffL(centerx);
            // light next state
            currentL = (currentL + 1) % 4;
            lightL(centerx);
        }
    }
    // Change Speed
    if (SpeedUp == HIGH)
    {
        delay(100);
    }
    else
    {
        delay(500);
    }
    // Drop
    // need to add more conditions 不同形态
    // 0
    if (currentL == 0)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffL(centerx);
            while ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
                // showCol();
            }
            lightArray[centerx][17 - centery3] = 1;
            lightArray[centerx + 2][17 - centery3] = 1;
            lightArray[centerx + 4][17 - centery3] = 1;
            lightArray[centerx + 4][17 - centery2] = 1;
            lightL(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
        else if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery3] == 0))
        {
            turnoffL(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery3] = 1;
            lightArray[centerx + 2][17 - centery3] = 1;
            lightArray[centerx + 4][17 - centery3] = 1;
            lightArray[centerx + 4][17 - centery2] = 1;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
    }
    // 1
    if (currentL == 1)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffL(centerx);
            while ((centerx < NUMPIXELS - 4) && (lightArray[centerx + SPEED][17 - centery1] == 0) && (lightArray[centerx + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery1] = 1;
            lightArray[centerx][17 - centery2] = 1;
            lightArray[centerx][17 - centery3] = 1;
            lightArray[centerx + 2][17 - centery3] = 1;
            lightL(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
        else if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + SPEED][17 - centery1] == 0) && (lightArray[centerx + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
        {
            turnoffL(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery1] = 1;
            lightArray[centerx][17 - centery2] = 1;
            lightArray[centerx][17 - centery3] = 1;
            lightArray[centerx + 2][17 - centery3] = 1;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
    }
    if (currentL == 2)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffL(centerx);
            while ((centerx < NUMPIXELS - 6) && (lightArray[centerx + SPEED][17 - centery3] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery3] = 1;
            lightArray[centerx][17 - centery2] = 1;
            lightArray[centerx + 2][17 - centery2] = 1;
            lightArray[centerx + 4][17 - centery2] = 1;
            lightL(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
        else if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + SPEED][17 - centery3] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0))
        {
            turnoffL(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery3] = 1;
            lightArray[centerx][17 - centery2] = 1;
            lightArray[centerx + 2][17 - centery2] = 1;
            lightArray[centerx + 4][17 - centery2] = 1;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
    }
    if (currentL == 3)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffL(centerx);
            while ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][17 - centery1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery1] = 1;
            lightArray[centerx + 2][17 - centery1] = 1;
            lightArray[centerx + 2][17 - centery2] = 1;
            lightArray[centerx + 2][17 - centery3] = 1;
            lightL(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
        else if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][17 - centery1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
        {
            turnoffL(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery1] = 1;
            lightArray[centerx + 2][17 - centery1] = 1;
            lightArray[centerx + 2][17 - centery2] = 1;
            lightArray[centerx + 2][17 - centery3] = 1;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentL = 0;
        }
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
    currentRotateState = digitalRead(BUTTON_ROTATE);
    SpeedUp = digitalRead(BUTTON_SPEEDUP);
    currentStateDrop = digitalRead(BUTTON_DROP);

    if (currentZ == 0)
    {
        if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 - 1] == 0))
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED + 2][17 - centery2 + 1] == 0) && (lightArray[centerx + SPEED + 4][17 - centery2 + 1] == 0))
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

        if ((currentRotateState == HIGH) && (centery2 > PINR3) && (lightArray[centerx + 4][17 - centery3] == 0) && (lightArray[centerx + 2][17 - centery1] == 0))
        {
            // turnoff current state
            turnoffZ(centerx);
            // light next state
            currentZ = (currentZ + 1) % 2;
            lightZ(centerx);
        }
    }
    else if (currentZ == 1)
    {
        if (currentStateL == HIGH && (lightArray[centerx + 2 + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0))
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED + 2][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 2][17 - centery2 + 1] == 0) && (lightArray[centerx + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + SPEED][17 - centery1 + 1] == 0))
        {
            // clear(centerx-SPEED);
            if (centery1 > PINR3)
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

        if ((currentRotateState == HIGH) && (lightArray[centerx + 4][17 - centery3] == 0) && (lightArray[centerx + 4][17 - centery2] == 0) && (lightArray[centerx + 6][17 - centery2] == 0))
        {
            // turnoff current state
            turnoffZ(centerx);
            // light next state
            currentZ = (currentZ + 1) % 2;
            lightZ(centerx);
        }
    }

    if (SpeedUp == HIGH)
    {
        delay(100);
    }
    else
    {
        delay(500);
    }
    if (currentZ == 0)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffZ(centerx);
            while ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx + 2][17 - centery2] = 4;
            lightArray[centerx + 4][17 - centery2] = 4;
            lightArray[centerx][17 - centery3] = 4;
            lightArray[centerx + 2][17 - centery3] = 4;
            lightZ(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentZ = 0;
        }
        else if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
        {

            turnoffZ(centerx);

            centerx = centerx + SPEED;
            showCol();
        }
        else
        {

            lightArray[centerx + 2][17 - centery2] = 4;
            lightArray[centerx + 4][17 - centery2] = 4;
            lightArray[centerx][17 - centery3] = 4;
            lightArray[centerx + 2][17 - centery3] = 4;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentZ = 0;
        }
    }
    if (currentZ == 1)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffZ(centerx);
            while ((centerx < NUMPIXELS - 4) && (lightArray[centerx + SPEED][17 - centery1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx + 2][17 - centery3] = 4;
            lightArray[centerx][17 - centery2] = 4;
            lightArray[centerx + 2][17 - centery2] = 4;
            lightArray[centerx][17 - centery1] = 4;
            lightZ(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentZ = 0;
        }
        else if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + SPEED][17 - centery1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
        {

            turnoffZ(centerx);

            centerx = centerx + SPEED;
            showCol();
        }
        else
        {

            lightArray[centerx + 2][17 - centery3] = 4;
            lightArray[centerx][17 - centery2] = 4;
            lightArray[centerx + 2][17 - centery2] = 4;
            lightArray[centerx][17 - centery1] = 4;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentZ = 0;
        }
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
    currentRotateState = digitalRead(BUTTON_ROTATE);
    SpeedUp = digitalRead(BUTTON_SPEEDUP);
    currentStateDrop = digitalRead(BUTTON_DROP);

    if (currentT == 0)
    {
        // move left
        if ((currentStateL == HIGH) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2 - 1] == 0))
        {
            if (centery3 < PINL3)
            {
                centery1 += 1;
                centery2 += 1;
                centery3 += 1;
                centery4 += 1;
            }
        }
        // move right
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery2 + 1] == 0))
        {
            if (centery2 > PINR3)
            {
                centery1 -= 1;
                centery2 -= 1;
                centery3 -= 1;
                centery4 -= 1;
            }
        }
        // rotate
        if ((currentRotateState == HIGH) && (centery3 < PINL3) && (lightArray[centerx + 4][17 - centery3] == 0) && (lightArray[centerx + 4][17 - centery4] == 0))
        {
            // turnoff current state
            turnoffT(centerx);
            // light next state
            currentT = (currentT + 1) % 4;
            lightT(centerx);
        }
    }
    else if (currentT == 1)
    {
        // move left
        if ((currentStateL == HIGH) && (lightArray[centerx + 2 + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery4 - 1] == 0))
        {
            if (centery4 < PINL3)
            {
                centery1 += 1;
                centery2 += 1;
                centery3 += 1;
                centery4 += 1;
            }
        }
        // move right
        if ((currentStateR == HIGH) && (lightArray[centerx + 2 + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery4 + 1] == 0))
        {
            if (centery2 > PINR3)
            {
                centery1 -= 1;
                centery2 -= 1;
                centery3 -= 1;
                centery4 -= 1;
            }
        }
        // rotate
        if ((currentRotateState == HIGH) && (lightArray[centerx + 4][17 - centery3] == 0) && (lightArray[centerx + 4][17 - centery2] == 0) && (lightArray[centerx + 6][17 - centery3] == 0))
        {
            // turnoff current state
            turnoffT(centerx);
            // light next state
            currentT = (currentT + 1) % 4;
            lightT(centerx);
        }
    }
    else if (currentT == 2)
    {
        // move left
        if ((currentStateL == HIGH) && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery3 - 1] == 0))
        {
            if (centery3 < PINL3)
            {
                centery1 += 1;
                centery2 += 1;
                centery3 += 1;
                centery4 += 1;
            }
        }
        // move right
        if ((currentStateR == HIGH) && (lightArray[centerx + 2 + SPEED][17 - centery3 + 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery3 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2 + 1] == 0))
        {
            if (centery2 > PINR3)
            {
                centery1 -= 1;
                centery2 -= 1;
                centery3 -= 1;
                centery4 -= 1;
            }
        }
        // rotate
        if ((currentRotateState == HIGH) && (centery3 < PINL3) && (lightArray[centerx + 2][17 - centery4] == 0))
        {
            // turnoff current state
            turnoffT(centerx);
            // light next state
            currentT = (currentT + 1) % 4;
            lightT(centerx);
        }
    }
    else if (currentT == 3)
    {
        // move left
        if ((currentStateL == HIGH) && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + SPEED][17 - centery4 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0))
        {
            if (centery4 < PINL3)
            {
                centery1 += 1;
                centery2 += 1;
                centery3 += 1;
                centery4 += 1;
            }
        }
        // move right
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED][17 - centery2 + 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 + 1] == 0))
        {
            if (centery2 > PINR3)
            {
                centery1 -= 1;
                centery2 -= 1;
                centery3 -= 1;
                centery4 -= 1;
            }
        }
        // rotate
        if ((currentRotateState == HIGH) && (lightArray[centerx + 2][17 - centery2] == 0) && (lightArray[centerx + 4][17 - centery2] == 0) && (lightArray[centerx + 6][17 - centery2] == 0) && (lightArray[centerx + 4][17 - centery3] == 0))
        {
            // turnoff current state
            turnoffT(centerx);
            // light next state
            currentT = (currentT + 1) % 4;
            lightT(centerx);
        }
    }

    // Change Speed
    if (SpeedUp == HIGH)
    {
        delay(100);
    }
    else
    {
        delay(500);
    }
    if (currentT == 0)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffT(centerx);
            while ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery2] = 5;
            lightArray[centerx + 2][17 - centery2] = 5;
            lightArray[centerx + 4][17 - centery2] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            lightT(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
        else if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0))
        {
            turnoffT(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery2] = 5;
            lightArray[centerx + 2][17 - centery2] = 5;
            lightArray[centerx + 4][17 - centery2] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
    }
    if (currentT == 1)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffT(centerx);
            while ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery4] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery2] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery4] = 5;
            lightT(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
        else if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery4] == 0))
        {
            turnoffT(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery2] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery4] = 5;
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
    }
    if (currentT == 2)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffT(centerx);
            while ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery3] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            lightArray[centerx + 4][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery2] = 5;
            lightT(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
        else if ((centerx < NUMPIXELS - 6) && (lightArray[centerx + 4 + SPEED][17 - centery3] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery2] == 0))
        {
            turnoffT(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            lightArray[centerx + 4][17 - centery3] = 5;
            lightArray[centerx + 2][17 - centery2] = 5;
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
    }
    if (currentT == 3)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffT(centerx);
            while ((centerx < NUMPIXELS - 4) && (lightArray[centerx + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0) && (lightArray[centerx + SPEED][17 - centery4] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery2] = 5;
            lightArray[centerx][17 - centery3] = 5;
            lightArray[centerx][17 - centery4] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            lightT(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
        else if ((centerx < NUMPIXELS - 4) && (lightArray[centerx + SPEED][17 - centery2] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3] == 0) && (lightArray[centerx + SPEED][17 - centery4] == 0))
        {
            turnoffT(centerx);
            centerx = centerx + SPEED;
            showCol();
        }
        else
        {
            lightArray[centerx][17 - centery2] = 5;
            lightArray[centerx][17 - centery3] = 5;
            lightArray[centerx][17 - centery4] = 5;
            lightArray[centerx + 2][17 - centery3] = 5;
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentT = 0;
        }
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
    currentRotateState = digitalRead(BUTTON_ROTATE);
    SpeedUp = digitalRead(BUTTON_SPEEDUP);
    currentStateDrop = digitalRead(BUTTON_DROP);

    if (currentI == 0)
    {
        if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 2 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 4 + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + 6 + SPEED][17 - centery3 - 1] == 0))
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED + 2][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 4][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 6][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 6][17 - centery3 + 1] == 0))
        {
            if (centery3 > PINR3)
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
        // rotate
        if ((currentRotateState == HIGH) && (centery3 > PINR2) && (centery3 < PINL3) && (lightArray[centerx + 2][17 - centery4] == 0) && (lightArray[centerx + 2][17 - centery2] == 0) && (lightArray[centerx + 2][17 - centery1] == 0))
        {
            // turnoff current state
            turnoffI(centerx);
            // light next state
            currentI = (currentI + 1) % 2;
            lightI(centerx);
        }
    }
    else if (currentI == 1)
    {
        if (currentStateL == HIGH && (lightArray[centerx + SPEED][17 - centery1 - 1] == 0) && (lightArray[centerx + SPEED][17 - centery2 - 1] == 0) && (lightArray[centerx + SPEED][17 - centery3 - 1] == 0) && (lightArray[centerx + SPEED][17 - centery4 - 1] == 0))
        {
            if (centery4 < PINL3)
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
        if ((currentStateR == HIGH) && (lightArray[centerx + SPEED + 2][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 4][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 6][17 - centery3 + 1] == 0) && (lightArray[centerx + SPEED + 6][17 - centery3 + 1] == 0))
        {
            if (centery1 > PINR3)
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
        // rotate
        if ((currentRotateState == HIGH) && (lightArray[centerx + 2][17 - centery3] == 0) && (lightArray[centerx + 4][17 - centery3] == 0) && (lightArray[centerx + 6][17 - centery3] == 0))
        {
            // turnoff current state
            turnoffI(centerx);
            // light next state
            currentI = (currentI + 1) % 2;
            lightI(centerx);
        }
    }

    // Change Speed
    if (SpeedUp == HIGH)
    {
        delay(100);
    }
    else
    {
        delay(500);
    }

    if (currentI == 0)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffI(centerx);
            while ((centerx < NUMPIXELS - 8) && (lightArray[centerx + 6 + SPEED][17 - centery3] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery3] = 2;
            lightArray[centerx + 2][17 - centery3] = 2;
            lightArray[centerx + 4][17 - centery3] = 2;
            lightArray[centerx + 6][17 - centery3] = 2;
            lightI(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentI = 0;
        }
        else if ((centerx < NUMPIXELS - 8) && (lightArray[centerx + 6 + SPEED][17 - centery3] == 0))
        {

            turnoffI(centerx);

            centerx = centerx + SPEED;
            showCol();
        }
        else
        {

            lightArray[centerx][17 - centery3] = 2;
            lightArray[centerx + 2][17 - centery3] = 2;
            lightArray[centerx + 4][17 - centery3] = 2;
            lightArray[centerx + 6][17 - centery3] = 2;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentI = 0;
        }
    }
    if (currentI == 1)
    {
        if (currentStateDrop == HIGH)
        {
            turnoffI(centerx);
            while ((centerx < NUMPIXELS) && (lightArray[centerx + SPEED][17 - centery1] == 0) && (lightArray[centerx + SPEED][17 - centery2] == 0) && (lightArray[centerx + SPEED][17 - centery3] == 0) && (lightArray[centerx + SPEED][17 - centery4] == 0))
            {
                centerx = centerx + SPEED;
            }
            lightArray[centerx][17 - centery1] = 2;
            lightArray[centerx][17 - centery2] = 2;
            lightArray[centerx][17 - centery3] = 2;
            lightArray[centerx][17 - centery4] = 2;
            lightI(centerx);
            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentI = 0;
        }
        else if ((centerx < NUMPIXELS) && (lightArray[centerx + SPEED][17 - centery1] == 0) && (lightArray[centerx + SPEED][17 - centery2] == 0) && (lightArray[centerx + SPEED][17 - centery3] == 0) && (lightArray[centerx + SPEED][17 - centery4] == 0))
        {

            turnoffI(centerx);

            centerx = centerx + SPEED;
            showCol();
        }
        else
        {

            lightArray[centerx][17 - centery1] = 2;
            lightArray[centerx][17 - centery2] = 2;
            lightArray[centerx][17 - centery3] = 2;
            lightArray[centerx][17 - centery4] = 2;

            centerx = 0;
            centery1 = PIN;
            centery2 = PIN2;
            centery3 = PIN3;
            centery4 = PIN4;
            checkLine();
            showCol();
            randNumber = random(0, 5);
            currentI = 0;
        }
    }
}

// check whether to clear the line
void checkLine()
{
    int product = 1;
    for (int i = 36; i > 0; i = i - 2)
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
            blink(i);
            i = i + 2;
        }
    }
    arrayLight();
}
void blink(int line)
{
    col1.setPixelColor(line, col1.Color(0, 0, 0));
    col2.setPixelColor(line, col1.Color(0, 0, 0));
    col3.setPixelColor(line, col1.Color(0, 0, 0));
    col4.setPixelColor(line, col1.Color(0, 0, 0));
    colL1.setPixelColor(line, col1.Color(0, 0, 0));
    colL2.setPixelColor(line, col1.Color(0, 0, 0));
    colL3.setPixelColor(line, col1.Color(0, 0, 0));
    colR1.setPixelColor(line, col1.Color(0, 0, 0));
    colR2.setPixelColor(line, col1.Color(0, 0, 0));
    colR3.setPixelColor(line, col1.Color(0, 0, 0));
    delay(50);
    col1.setPixelColor(line, col1.Color(255, 255, 255));
    col2.setPixelColor(line, col1.Color(255, 255, 255));
    col3.setPixelColor(line, col1.Color(255, 255, 255));
    col4.setPixelColor(line, col1.Color(255, 255, 255));
    colL1.setPixelColor(line, col1.Color(255, 255, 255));
    colL2.setPixelColor(line, col1.Color(255, 255, 255));
    colL3.setPixelColor(line, col1.Color(255, 255, 255));
    colR1.setPixelColor(line, col1.Color(255, 255, 255));
    colR2.setPixelColor(line, col1.Color(255, 255, 255));
    colR3.setPixelColor(line, col1.Color(255, 255, 255));
    delay(50);
    col1.setPixelColor(line, col1.Color(0, 0, 0));
    col2.setPixelColor(line, col1.Color(0, 0, 0));
    col3.setPixelColor(line, col1.Color(0, 0, 0));
    col4.setPixelColor(line, col1.Color(0, 0, 0));
    colL1.setPixelColor(line, col1.Color(0, 0, 0));
    colL2.setPixelColor(line, col1.Color(0, 0, 0));
    colL3.setPixelColor(line, col1.Color(0, 0, 0));
    colR1.setPixelColor(line, col1.Color(0, 0, 0));
    colR2.setPixelColor(line, col1.Color(0, 0, 0));
    colR3.setPixelColor(line, col1.Color(0, 0, 0));
    delay(50);
    col1.setPixelColor(line, col1.Color(255, 255, 255));
    col2.setPixelColor(line, col1.Color(255, 255, 255));
    col3.setPixelColor(line, col1.Color(255, 255, 255));
    col4.setPixelColor(line, col1.Color(255, 255, 255));
    colL1.setPixelColor(line, col1.Color(255, 255, 255));
    colL2.setPixelColor(line, col1.Color(255, 255, 255));
    colL3.setPixelColor(line, col1.Color(255, 255, 255));
    colR1.setPixelColor(line, col1.Color(255, 255, 255));
    colR2.setPixelColor(line, col1.Color(255, 255, 255));
    colR3.setPixelColor(line, col1.Color(255, 255, 255));
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
    for (int i = 0; i < 38; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (17 - j)
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
            if (lightArray[i][j] == 1)
            {
                switch (17 - j)
                {
                case PIN:
                    col1.setPixelColor(i, col1.Color(220, 0, 0));
                    break;
                case PIN2:
                    col2.setPixelColor(i, col2.Color(220, 0, 0));
                    break;
                case PIN3:
                    col3.setPixelColor(i, col3.Color(220, 0, 0));
                    break;
                case PIN4:
                    col4.setPixelColor(i, col4.Color(220, 0, 0));
                    break;
                case PINL1:
                    colL1.setPixelColor(i, colL1.Color(220, 0, 0));
                    break;
                case PINL2:
                    colL2.setPixelColor(i, colL2.Color(220, 0, 0));
                    break;
                case PINL3:
                    colL3.setPixelColor(i, colL3.Color(220, 0, 0));
                    break;
                case PINR1:
                    colR1.setPixelColor(i, colR1.Color(220, 0, 0));
                    break;
                case PINR2:
                    colR2.setPixelColor(i, colR2.Color(220, 0, 0));
                    break;
                case PINR3:
                    colR3.setPixelColor(i, colR3.Color(220, 0, 0));
                    break;
                }
            }
            if (lightArray[i][j] == 2)
            {
                switch (17 - j)
                {
                case PIN:
                    col1.setPixelColor(i, col1.Color(0, 0, 255));
                    break;
                case PIN2:
                    col2.setPixelColor(i, col2.Color(0, 0, 255));
                    break;
                case PIN3:
                    col3.setPixelColor(i, col3.Color(0, 0, 255));
                    break;
                case PIN4:
                    col4.setPixelColor(i, col4.Color(0, 0, 255));
                    break;
                case PINL1:
                    colL1.setPixelColor(i, colL1.Color(0, 0, 255));
                    break;
                case PINL2:
                    colL2.setPixelColor(i, colL2.Color(0, 0, 255));
                    break;
                case PINL3:
                    colL3.setPixelColor(i, colL3.Color(0, 0, 255));
                    break;
                case PINR1:
                    colR1.setPixelColor(i, colR1.Color(0, 0, 255));
                    break;
                case PINR2:
                    colR2.setPixelColor(i, colR2.Color(0, 0, 255));
                    break;
                case PINR3:
                    colR3.setPixelColor(i, colR3.Color(0, 0, 255));
                    break;
                }
            }
            if (lightArray[i][j] == 3)
            {
                switch (17 - j)
                {
                case PIN:
                    col1.setPixelColor(i, col1.Color(0, 128, 0));
                    break;
                case PIN2:
                    col2.setPixelColor(i, col2.Color(0, 128, 0));
                    break;
                case PIN3:
                    col3.setPixelColor(i, col3.Color(0, 128, 0));
                    break;
                case PIN4:
                    col4.setPixelColor(i, col4.Color(0, 128, 0));
                    break;
                case PINL1:
                    colL1.setPixelColor(i, colL1.Color(0, 128, 0));
                    break;
                case PINL2:
                    colL2.setPixelColor(i, colL2.Color(0, 128, 0));
                    break;
                case PINL3:
                    colL3.setPixelColor(i, colL3.Color(0, 128, 0));
                    break;
                case PINR1:
                    colR1.setPixelColor(i, colR1.Color(0, 128, 0));
                    break;
                case PINR2:
                    colR2.setPixelColor(i, colR2.Color(0, 128, 0));
                    break;
                case PINR3:
                    colR3.setPixelColor(i, colR3.Color(0, 128, 0));
                    break;
                }
            }
            if (lightArray[i][j] == 4)
            {
                switch (17 - j)
                {
                case PIN:
                    col1.setPixelColor(i, col1.Color(255, 255, 0));
                    break;
                case PIN2:
                    col2.setPixelColor(i, col2.Color(255, 255, 0));
                    break;
                case PIN3:
                    col3.setPixelColor(i, col3.Color(255, 255, 0));
                    break;
                case PIN4:
                    col4.setPixelColor(i, col4.Color(255, 255, 0));
                    break;
                case PINL1:
                    colL1.setPixelColor(i, colL1.Color(255, 255, 0));
                    break;
                case PINL2:
                    colL2.setPixelColor(i, colL2.Color(255, 255, 0));
                    break;
                case PINL3:
                    colL3.setPixelColor(i, colL3.Color(255, 255, 0));
                    break;
                case PINR1:
                    colR1.setPixelColor(i, colR1.Color(255, 255, 0));
                    break;
                case PINR2:
                    colR2.setPixelColor(i, colR2.Color(255, 255, 0));
                    break;
                case PINR3:
                    colR3.setPixelColor(i, colR3.Color(255, 255, 0));
                    break;
                }
            }
            if (lightArray[i][j] == 5)
            {
                switch (17 - j)
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
    if (currentL == 0)
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
    if (currentL == 1)
    {
        switch (centery1b)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));

            break;
        case PINL1:

            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));

            break;
        }
    }
    if (currentL == 2)
    {
        switch (centery1b)
        {
        case PIN:

            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));

            break;
        case PIN2:

            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));

            break;
        case PIN3:

            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));

            break;
        case PIN4:

            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));

            break;
        case PINL1:

            colL2.setPixelColor(centerx, colL2.Color(0, 0, 05));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
            break;
        case PINR1:

            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));

            break;
        case PINR2:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));

            break;
        case PINR3:

            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));

            break;
        case PINR3 - 1:

            colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
            colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
            colR3.setPixelColor(centerx + 4, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));

            break;
        }
    }
    if (currentL == 3)
    {
        switch (centery1b)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));

            break;
        case PINL1:

            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
            colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));

            break;
        }
    }
}

void turnoffZ(int centerx)
{
    if (currentZ == 0)
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
    if (currentZ == 1)
    {
        switch (centery1b)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));

            break;
        case PINL1:

            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));

            break;
        }
    }
}
void turnoffT(int centerx)
{
    if (currentT == 0)
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
    if (currentT == 1)
    {
        switch (centery1b)
        {
        case PIN:

            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));

            break;
        case PIN2:
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            break;
        case PIN3:
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            break;
        case PIN4:
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));

            break;
        case PINR1:
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            break;
        case PINR2:
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            break;
        case PINR3:
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            break;
        }
    }
    if (currentT == 2)
    {
        switch (centery1b)
        {
        case PIN:

            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx + 4, col3.Color(0, 0, 0));

            break;
        case PIN2:
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx + 4, col4.Color(0, 0, 0));
            break;
        case PIN3:
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 0));
            break;
        case PIN4:
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 0));

            break;
        case PINL1:
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 0));
            colL3.setPixelColor(centerx + 4, colL3.Color(0, 0, 0));

            break;
        case PINR1:
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx + 4, col2.Color(0, 0, 0));
            break;
        case PINR2:
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 4, col1.Color(0, 0, 0));
            break;
        case PINR3:
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 0));
            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx + 2, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 0));
            break;
        }
    }
    if (currentT == 3)
    {
        switch (centery1b)
        {
        case PIN:

            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));

            break;
        case PIN2:
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            break;
        case PIN3:
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, col2.Color(0, 0, 0));
            break;
        case PIN4:
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));

            break;
        case PINR1:
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            break;
        case PINR2:
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            break;
        case PINR3:
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            break;
        }
    }
}

void turnoffI(int centerx)
{
    if (currentI == 0)
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
    if (currentI == 1)
    {
        switch (centery1b)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(0, 0, 0));
            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(0, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(0, 0, 0));

            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));
            col3.setPixelColor(centerx, col3.Color(0, 0, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));
            col2.setPixelColor(centerx, col2.Color(0, 0, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(0, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 0));
            col1.setPixelColor(centerx, col1.Color(0, 0, 0));

            break;
        }
    }
}
// light
void lightO(int centerx)
{
    switch (centery1)
    {
    case PIN:
        col2.setPixelColor(centerx, col2.Color(0, 128, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 128, 0));
        col3.setPixelColor(centerx, col3.Color(0, 128, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 128, 0));
        break;
    case PIN2:
        col3.setPixelColor(centerx, col3.Color(0, 128, 0));
        col3.setPixelColor(centerx + 2, col3.Color(0, 128, 0));
        col4.setPixelColor(centerx, col4.Color(0, 128, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 128, 0));
        break;
    case PIN3:
        col4.setPixelColor(centerx, col4.Color(0, 128, 0));
        col4.setPixelColor(centerx + 2, col4.Color(0, 128, 0));
        colL1.setPixelColor(centerx, colL1.Color(0, 128, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 128, 0));
        break;
    case PIN4:
        colL1.setPixelColor(centerx, colL1.Color(0, 128, 0));
        colL1.setPixelColor(centerx + 2, colL1.Color(0, 128, 0));
        colL2.setPixelColor(centerx, colL2.Color(0, 128, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 128, 0));
        break;
    case PINL1:
        colL2.setPixelColor(centerx, colL2.Color(0, 128, 0));
        colL2.setPixelColor(centerx + 2, colL2.Color(0, 128, 0));
        colL3.setPixelColor(centerx, colL3.Color(0, 128, 0));
        colL3.setPixelColor(centerx + 2, colL3.Color(0, 128, 0));
        break;
    case PINR1:
        col1.setPixelColor(centerx, col1.Color(0, 128, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 128, 0));
        col2.setPixelColor(centerx, col2.Color(0, 128, 0));
        col2.setPixelColor(centerx + 2, col2.Color(0, 128, 0));
        break;
    case PINR2:
        colR1.setPixelColor(centerx, colR1.Color(0, 128, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 128, 0));
        col1.setPixelColor(centerx, col1.Color(0, 128, 0));
        col1.setPixelColor(centerx + 2, col1.Color(0, 128, 0));
        break;
    case PINR3:
        colR2.setPixelColor(centerx, colR2.Color(0, 128, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 128, 0));
        colR1.setPixelColor(centerx, colR1.Color(0, 128, 0));
        colR1.setPixelColor(centerx + 2, colR1.Color(0, 128, 0));
        break;
    case PINR3 - 1:
        colR3.setPixelColor(centerx, colR3.Color(0, 128, 0));
        colR3.setPixelColor(centerx + 2, colR3.Color(0, 128, 0));
        colR2.setPixelColor(centerx, colR2.Color(0, 128, 0));
        colR2.setPixelColor(centerx + 2, colR2.Color(0, 128, 0));
        break;
    }
}

void lightL(int centerx)
{
    if (currentL == 0)
    {
        switch (centery1)
        {
        case PIN:

            col2.setPixelColor(centerx + 4, col2.Color(220, 0, 0));
            col3.setPixelColor(centerx, col3.Color(220, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(220, 0, 0));
            col3.setPixelColor(centerx + 4, col3.Color(220, 0, 0));

            break;
        case PIN2:

            col3.setPixelColor(centerx + 4, col3.Color(220, 0, 0));
            col4.setPixelColor(centerx, col4.Color(220, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(220, 0, 0));
            col4.setPixelColor(centerx + 4, col4.Color(220, 0, 0));

            break;
        case PIN3:

            col4.setPixelColor(centerx + 4, col4.Color(220, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 4, colL1.Color(220, 0, 0));

            break;
        case PIN4:

            colL1.setPixelColor(centerx + 4, colL1.Color(220, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 4, colL2.Color(220, 0, 0));

            break;
        case PINL1:

            colL2.setPixelColor(centerx + 4, colL2.Color(220, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(220, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(220, 0, 0));
            colL3.setPixelColor(centerx + 4, colL3.Color(220, 0, 0));
            break;
        case PINR1:

            col1.setPixelColor(centerx + 4, col1.Color(220, 0, 0));
            col2.setPixelColor(centerx, col2.Color(220, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(220, 0, 0));
            col2.setPixelColor(centerx + 4, col2.Color(220, 0, 0));

            break;
        case PINR2:

            colR1.setPixelColor(centerx + 4, colR1.Color(220, 0, 0));
            col1.setPixelColor(centerx, col1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 4, col1.Color(220, 0, 0));

            break;
        case PINR3:

            colR2.setPixelColor(centerx + 4, colR2.Color(220, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 4, colR1.Color(220, 0, 0));

            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx + 4, colR3.Color(220, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(220, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(220, 0, 0));
            colR2.setPixelColor(centerx + 4, colR2.Color(220, 0, 0));

            break;
        }
    }
    if (currentL == 1)
    {
        switch (centery1)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(220, 0, 0));
            col2.setPixelColor(centerx, col2.Color(220, 0, 0));
            col3.setPixelColor(centerx, col3.Color(220, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(220, 0, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(220, 0, 0));
            col3.setPixelColor(centerx, col3.Color(220, 0, 0));
            col4.setPixelColor(centerx, col4.Color(220, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(220, 0, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(220, 0, 0));
            col4.setPixelColor(centerx, col4.Color(220, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(220, 0, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(220, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(220, 0, 0));

            break;
        case PINL1:

            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(220, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(220, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(220, 0, 0));
            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));
            col1.setPixelColor(centerx, col1.Color(220, 0, 0));
            col2.setPixelColor(centerx, col2.Color(220, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(220, 0, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(220, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));
            col1.setPixelColor(centerx, col1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(220, 0, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(220, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(220, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(220, 0, 0));

            break;
        }
    }
    if (currentL == 2)
    {
        switch (centery1)
        {
        case PIN:

            col2.setPixelColor(centerx, col2.Color(220, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(220, 0, 0));
            col2.setPixelColor(centerx + 4, col2.Color(220, 0, 0));
            col3.setPixelColor(centerx, col3.Color(220, 0, 0));

            break;
        case PIN2:

            col3.setPixelColor(centerx, col3.Color(220, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(220, 0, 0));
            col3.setPixelColor(centerx + 4, col3.Color(220, 0, 0));
            col4.setPixelColor(centerx, col4.Color(220, 0, 0));

            break;
        case PIN3:

            col4.setPixelColor(centerx, col4.Color(220, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(220, 0, 0));
            col4.setPixelColor(centerx + 4, col4.Color(220, 0, 0));
            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));

            break;
        case PIN4:

            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 4, colL1.Color(220, 0, 0));
            colL2.setPixelColor(centerx, colL2.Color(220, 0, 0));

            break;
        case PINL1:

            colL2.setPixelColor(centerx, colL2.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 4, colL2.Color(220, 0, 0));
            colL3.setPixelColor(centerx, colL3.Color(220, 0, 0));
            break;
        case PINR1:

            col1.setPixelColor(centerx, col1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 4, col1.Color(220, 0, 0));
            col2.setPixelColor(centerx, col2.Color(220, 0, 0));

            break;
        case PINR2:

            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 4, colR1.Color(220, 0, 0));
            col1.setPixelColor(centerx, col1.Color(220, 0, 0));

            break;
        case PINR3:

            colR2.setPixelColor(centerx, colR2.Color(220, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(220, 0, 0));
            colR2.setPixelColor(centerx + 4, colR2.Color(220, 0, 0));
            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));

            break;
        case PINR3 - 1:

            colR3.setPixelColor(centerx, colR3.Color(220, 0, 0));
            colR3.setPixelColor(centerx + 2, colR3.Color(220, 0, 0));
            colR3.setPixelColor(centerx + 4, colR3.Color(220, 0, 0));
            colR2.setPixelColor(centerx, colR2.Color(220, 0, 0));

            break;
        }
    }
    if (currentL == 3)
    {
        switch (centery1)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(220, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(220, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(220, 0, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(220, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(220, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(220, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(220, 0, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(220, 0, 0));
            col3.setPixelColor(centerx + 2, col3.Color(220, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(220, 0, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(220, 0, 0));
            col4.setPixelColor(centerx + 2, col4.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(220, 0, 0));

            break;
        case PINL1:

            colL1.setPixelColor(centerx, colL1.Color(220, 0, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(220, 0, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(220, 0, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(220, 0, 0));
            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(220, 0, 0));
            col2.setPixelColor(centerx + 2, col2.Color(220, 0, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(220, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(220, 0, 0));
            col1.setPixelColor(centerx + 2, col1.Color(220, 0, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(220, 0, 0));
            colR3.setPixelColor(centerx + 2, colR3.Color(220, 0, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(220, 0, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(220, 0, 0));

            break;
        }
    }
}

void lightZ(int centerx)
{
    if (currentZ == 0)
    {
        switch (centery1)
        {
        case PIN:

            col2.setPixelColor(centerx + 2, col2.Color(255, 255, 0));
            col2.setPixelColor(centerx + 4, col2.Color(255, 255, 0));
            col3.setPixelColor(centerx, col3.Color(255, 255, 0));
            col3.setPixelColor(centerx + 2, col3.Color(255, 255, 0));

            break;
        case PIN2:

            col3.setPixelColor(centerx + 2, col3.Color(255, 255, 0));
            col3.setPixelColor(centerx + 4, col3.Color(255, 255, 0));
            col4.setPixelColor(centerx, col4.Color(255, 255, 0));
            col4.setPixelColor(centerx + 2, col4.Color(255, 255, 0));

            break;
        case PIN3:

            col4.setPixelColor(centerx + 2, col4.Color(255, 255, 0));
            col4.setPixelColor(centerx + 4, col4.Color(255, 255, 0));
            colL1.setPixelColor(centerx, colL1.Color(255, 255, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 255, 0));

            break;
        case PIN4:

            colL1.setPixelColor(centerx + 2, colL1.Color(255, 255, 0));
            colL1.setPixelColor(centerx + 4, colL1.Color(255, 255, 0));
            colL2.setPixelColor(centerx, colL2.Color(255, 255, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 255, 0));

            break;
        case PINL1:

            colL2.setPixelColor(centerx + 2, colL2.Color(255, 255, 0));
            colL2.setPixelColor(centerx + 4, colL2.Color(255, 255, 0));
            colL3.setPixelColor(centerx, colL3.Color(255, 255, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(255, 255, 0));
            break;
        case PINR1:

            col1.setPixelColor(centerx + 2, col1.Color(255, 255, 0));
            col1.setPixelColor(centerx + 4, col1.Color(255, 255, 0));
            col2.setPixelColor(centerx, col2.Color(255, 255, 0));
            col2.setPixelColor(centerx + 2, col2.Color(255, 255, 0));

            break;
        case PINR2:

            colR1.setPixelColor(centerx + 2, colR1.Color(255, 255, 0));
            colR1.setPixelColor(centerx + 4, colR1.Color(255, 255, 0));
            col1.setPixelColor(centerx, col1.Color(255, 255, 0));
            col1.setPixelColor(centerx + 2, col1.Color(255, 255, 0));

            break;
        case PINR3:

            colR2.setPixelColor(centerx + 2, colR2.Color(255, 255, 0));
            colR2.setPixelColor(centerx + 4, colR2.Color(255, 255, 0));
            colR1.setPixelColor(centerx, colR1.Color(255, 255, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 255, 0));

            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx + 2, colR3.Color(255, 255, 0));
            colR3.setPixelColor(centerx + 4, colR3.Color(255, 255, 0));
            colR2.setPixelColor(centerx, colR2.Color(255, 255, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 255, 0));

            break;
        }
    }
    if (currentZ == 1)
    {
        switch (centery1)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(255, 255, 0));
            col2.setPixelColor(centerx, col2.Color(255, 255, 0));
            col2.setPixelColor(centerx + 2, col2.Color(255, 255, 0));
            col3.setPixelColor(centerx + 2, col3.Color(255, 255, 0));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(255, 255, 0));
            col3.setPixelColor(centerx, col3.Color(255, 255, 0));
            col3.setPixelColor(centerx + 2, col3.Color(255, 255, 0));
            col4.setPixelColor(centerx + 2, col4.Color(255, 255, 0));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(255, 255, 0));
            col4.setPixelColor(centerx, col4.Color(255, 255, 0));
            col4.setPixelColor(centerx + 2, col4.Color(255, 255, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 255, 0));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(255, 255, 0));
            colL1.setPixelColor(centerx, colL1.Color(255, 255, 0));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 255, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 255, 0));

            break;
        case PINL1:

            colL1.setPixelColor(centerx, colL1.Color(255, 255, 0));
            colL2.setPixelColor(centerx, colL2.Color(255, 255, 0));
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 255, 0));
            colL3.setPixelColor(centerx + 2, colL3.Color(255, 255, 0));
            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(255, 255, 0));
            col1.setPixelColor(centerx, col1.Color(255, 255, 0));
            col1.setPixelColor(centerx + 2, col1.Color(255, 255, 0));
            col2.setPixelColor(centerx + 2, col2.Color(255, 255, 0));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(255, 255, 0));
            colR1.setPixelColor(centerx, colR1.Color(255, 255, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 255, 0));
            col1.setPixelColor(centerx + 2, col1.Color(255, 255, 0));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(255, 255, 0));
            colR2.setPixelColor(centerx, colR2.Color(255, 255, 0));
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 255, 0));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 255, 0));

            break;
        }
    }
}
void lightT(int centerx)
{
    if (currentT == 0)
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
    if (currentT == 1)
    {
        switch (centery1)
        {
        case PIN:

            col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            col3.setPixelColor(centerx, col3.Color(255, 0, 255));
            col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
            col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));

            break;
        case PIN2:
            col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
            col4.setPixelColor(centerx, col4.Color(255, 0, 255));
            col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
            break;
        case PIN3:
            col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
            colL2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            break;
        case PIN4:
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
            colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
            colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));

            break;
        case PINR1:
            col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
            col2.setPixelColor(centerx, col2.Color(255, 0, 255));
            col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
            break;
        case PINR2:
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
            col1.setPixelColor(centerx, col1.Color(255, 0, 255));
            col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
            col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            break;
        case PINR3:
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
            colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
            col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx + 2, colR3.Color(255, 0, 255));
            colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
            break;
        }
    }
    if (currentT == 2)
    {
        switch (centery1)
        {
        case PIN:

            col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            col3.setPixelColor(centerx, col3.Color(255, 0, 255));
            col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
            col3.setPixelColor(centerx + 4, col3.Color(255, 0, 255));

            break;
        case PIN2:
            col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
            col4.setPixelColor(centerx, col4.Color(255, 0, 255));
            col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
            col4.setPixelColor(centerx + 4, col4.Color(255, 0, 255));
            break;
        case PIN3:
            col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
            colL1.setPixelColor(centerx + 4, colL1.Color(255, 0, 255));
            break;
        case PIN4:
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
            colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
            colL2.setPixelColor(centerx + 4, colL2.Color(255, 0, 255));

            break;
        case PINL1:
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
            colL3.setPixelColor(centerx, colL3.Color(255, 0, 255));
            colL3.setPixelColor(centerx + 2, colL3.Color(255, 0, 255));
            colL3.setPixelColor(centerx + 4, colL3.Color(255, 0, 255));

            break;
        case PINR1:
            col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
            col2.setPixelColor(centerx, col2.Color(255, 0, 255));
            col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            col2.setPixelColor(centerx + 4, col2.Color(255, 0, 255));
            break;
        case PINR2:
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
            col1.setPixelColor(centerx, col1.Color(255, 0, 255));
            col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
            col1.setPixelColor(centerx + 4, col1.Color(255, 0, 255));
            break;
        case PINR3:
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
            colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
            colR1.setPixelColor(centerx + 4, colR1.Color(255, 0, 255));
            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx + 2, colR3.Color(255, 0, 255));
            colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
            colR2.setPixelColor(centerx + 4, colR2.Color(255, 0, 255));
            break;
        }
    }
    if (currentT == 3)
    {
        switch (centery1)
        {
        case PIN:

            col2.setPixelColor(centerx, col2.Color(255, 0, 255));
            col3.setPixelColor(centerx + 2, col3.Color(255, 0, 255));
            col3.setPixelColor(centerx, col3.Color(255, 0, 255));
            col4.setPixelColor(centerx, col4.Color(255, 0, 255));

            break;
        case PIN2:
            col3.setPixelColor(centerx, col3.Color(255, 0, 255));
            col4.setPixelColor(centerx + 2, col4.Color(255, 0, 255));
            col4.setPixelColor(centerx, col4.Color(255, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
            break;
        case PIN3:
            col4.setPixelColor(centerx, col4.Color(255, 0, 255));
            colL1.setPixelColor(centerx + 2, colL1.Color(255, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
            colL2.setPixelColor(centerx, col2.Color(255, 0, 255));
            break;
        case PIN4:
            colL1.setPixelColor(centerx, colL1.Color(255, 0, 255));
            colL2.setPixelColor(centerx + 2, colL2.Color(255, 0, 255));
            colL2.setPixelColor(centerx, colL2.Color(255, 0, 255));
            colL3.setPixelColor(centerx, colL3.Color(255, 0, 255));

            break;
        case PINR1:
            col1.setPixelColor(centerx, col1.Color(255, 0, 255));
            col2.setPixelColor(centerx + 2, col2.Color(255, 0, 255));
            col2.setPixelColor(centerx, col2.Color(255, 0, 255));
            col3.setPixelColor(centerx, col3.Color(255, 0, 255));
            break;
        case PINR2:
            colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
            col1.setPixelColor(centerx + 2, col1.Color(255, 0, 255));
            col1.setPixelColor(centerx, col1.Color(255, 0, 255));
            col2.setPixelColor(centerx, col2.Color(255, 0, 255));
            break;
        case PINR3:
            colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
            colR1.setPixelColor(centerx + 2, colR1.Color(255, 0, 255));
            colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
            col1.setPixelColor(centerx, col1.Color(255, 0, 255));
            break;
        case PINR3 - 1:
            colR3.setPixelColor(centerx, colR3.Color(255, 0, 255));
            colR2.setPixelColor(centerx + 2, colR2.Color(255, 0, 255));
            colR2.setPixelColor(centerx, colR2.Color(255, 0, 255));
            colR1.setPixelColor(centerx, colR1.Color(255, 0, 255));
            break;
        }
    }
}

void lightI(int centerx)
{
    if (currentI == 0)
    {
        switch (centery1)
        {
        case PIN:

            col3.setPixelColor(centerx, col3.Color(0, 0, 255));
            col3.setPixelColor(centerx + 2, col3.Color(0, 0, 255));
            col3.setPixelColor(centerx + 4, col3.Color(0, 0, 255));
            col3.setPixelColor(centerx + 6, col3.Color(0, 0, 255));

            break;
        case PIN2:

            col4.setPixelColor(centerx, col4.Color(0, 0, 255));
            col4.setPixelColor(centerx + 2, col4.Color(0, 0, 255));
            col4.setPixelColor(centerx + 4, col4.Color(0, 0, 255));
            col4.setPixelColor(centerx + 6, col4.Color(0, 0, 255));

            break;
        case PIN3:

            colL1.setPixelColor(centerx, colL1.Color(0, 0, 255));
            colL1.setPixelColor(centerx + 2, colL1.Color(0, 0, 255));
            colL1.setPixelColor(centerx + 4, colL1.Color(0, 0, 255));
            colL1.setPixelColor(centerx + 6, colL1.Color(0, 0, 255));

            break;
        case PIN4:

            colL2.setPixelColor(centerx, colL2.Color(0, 0, 255));
            colL2.setPixelColor(centerx + 2, colL2.Color(0, 0, 255));
            colL2.setPixelColor(centerx + 4, colL2.Color(0, 0, 255));
            colL2.setPixelColor(centerx + 6, colL2.Color(0, 0, 255));

            break;
        case PINL1:

            colL3.setPixelColor(centerx, colL3.Color(0, 0, 255));
            colL3.setPixelColor(centerx + 2, colL3.Color(0, 0, 255));
            colL3.setPixelColor(centerx + 4, colL3.Color(0, 0, 255));
            colL3.setPixelColor(centerx + 6, colL3.Color(0, 0, 255));
            break;
        case PINR1:

            col2.setPixelColor(centerx, col2.Color(0, 0, 255));
            col2.setPixelColor(centerx + 2, col2.Color(0, 0, 255));
            col2.setPixelColor(centerx + 4, col2.Color(0, 0, 255));
            col2.setPixelColor(centerx + 6, col2.Color(0, 0, 255));

            break;
        case PINR2:

            col1.setPixelColor(centerx, col1.Color(0, 0, 255));
            col1.setPixelColor(centerx + 2, col1.Color(0, 0, 255));
            col1.setPixelColor(centerx + 4, col1.Color(0, 0, 255));
            col1.setPixelColor(centerx + 6, col1.Color(0, 0, 255));

            break;
        case PINR3:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 255));
            colR1.setPixelColor(centerx + 2, colR1.Color(0, 0, 255));
            colR1.setPixelColor(centerx + 4, colR1.Color(0, 0, 255));
            colR1.setPixelColor(centerx + 6, colR1.Color(0, 0, 255));

            break;
        case PINR3 - 1:
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 255));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 255));
            colR2.setPixelColor(centerx + 4, colR2.Color(0, 0, 255));
            colR2.setPixelColor(centerx + 2, colR2.Color(0, 0, 255));

            break;
        }
    }
    if (currentI == 1)
    {
        switch (centery1)
        {
        case PIN:

            col1.setPixelColor(centerx, col1.Color(0, 0, 255));
            col2.setPixelColor(centerx, col2.Color(0, 0, 255));
            col3.setPixelColor(centerx, col3.Color(0, 0, 255));
            col4.setPixelColor(centerx, col4.Color(0, 0, 255));

            break;
        case PIN2:

            col2.setPixelColor(centerx, col2.Color(0, 0, 255));
            col3.setPixelColor(centerx, col3.Color(0, 0, 255));
            col4.setPixelColor(centerx, col4.Color(0, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 255));

            break;
        case PIN3:

            col3.setPixelColor(centerx, col3.Color(0, 0, 255));
            col4.setPixelColor(centerx, col4.Color(0, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 255));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 255));

            break;
        case PIN4:

            col4.setPixelColor(centerx, col4.Color(0, 0, 255));
            colL1.setPixelColor(centerx, colL1.Color(0, 0, 255));
            colL2.setPixelColor(centerx, colL2.Color(0, 0, 255));
            colL3.setPixelColor(centerx, colL3.Color(0, 0, 255));

            break;
        case PINR1:

            colR1.setPixelColor(centerx, colR1.Color(0, 0, 255));
            col1.setPixelColor(centerx, col1.Color(0, 0, 255));
            col2.setPixelColor(centerx, col2.Color(0, 0, 255));
            col3.setPixelColor(centerx, col3.Color(0, 0, 255));

            break;
        case PINR2:

            colR2.setPixelColor(centerx, colR2.Color(0, 0, 255));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 255));
            col1.setPixelColor(centerx, col1.Color(0, 0, 255));
            col2.setPixelColor(centerx, col2.Color(0, 0, 255));

            break;
        case PINR3:

            colR3.setPixelColor(centerx, colR3.Color(0, 0, 255));
            colR2.setPixelColor(centerx, colR2.Color(0, 0, 255));
            colR1.setPixelColor(centerx, colR1.Color(0, 0, 255));
            col1.setPixelColor(centerx, col1.Color(0, 0, 255));

            break;
        }
    }
}

void displayScore(int score)
{
    int ones = 0;
    int tens = 0;
    if (score <= 9)
    {
        ones = score;
    }
    else if (score > 9)
    {
        ones = score % 10;
        tens = score / 10;
    }

    for (int j = 0; j < 7; j++)
    {
        digitalWrite(ones_score_pin[j], numbers[ones][j]);
        digitalWrite(tens_score_pin[j], numbers[tens][j]);
    }
}

void displayHighscore(int score)
{
    int ones = 0;
    int tens = 0;
    if (score <= 9)
    {
        ones = score;
    }
    else if (score > 9)
    {
        ones = score % 10;
        tens = score / 10;
    }

    for (int j = 0; j < 7; j++)
    {
        digitalWrite(ones_highscore_pin[j], numbers[ones][j]);
        digitalWrite(tens_highscore_pin[j], numbers[tens][j]);
    }
}