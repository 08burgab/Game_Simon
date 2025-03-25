#include <Arduino.h>

const int ledPins[] = {2, 3, 4, 5};
const int buttonPins[] = {6, 7, 8, 9};
const int sequenceLength = 5;
int sequence[sequenceLength];
int playerInput[sequenceLength];
int level = 0;

void generateSequence();
void showSequence();
bool getPlayerInput();
void resetGame();

void setup()
{
    Serial.begin(115200);
    randomSeed(analogRead(0));
    for (int i = 0; i < 4; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    generateSequence();
}

void loop()
{
    showSequence();
    if (getPlayerInput())
    {
        Serial.println("Richtig!");
        level++;
        if (level == sequenceLength)
        {
            Serial.println("Du hast gewonnen!");
            resetGame();
        }
    }
    else
    {
        Serial.println("Falsch! Versuch es erneut.");
        resetGame();
    }
    delay(1000);
}

void generateSequence()
{
    for (int i = 0; i < sequenceLength; i++)
    {
        sequence[i] = random(0, 4);
    }
}

void showSequence()
{
    Serial.println("Merke dir die Sequenz:");
    for (int i = 0; i <= level; i++)
    {
        digitalWrite(ledPins[sequence[i]], HIGH);
        delay(500);
        digitalWrite(ledPins[sequence[i]], LOW);
        delay(250);
    }
}

bool getPlayerInput()
{
    for (int i = 0; i <= level; i++)
    {
        bool buttonPressed = false;
        while (!buttonPressed)
        {
            for (int j = 0; j < 4; j++)
            {
                if (digitalRead(buttonPins[j]) == LOW)
                {
                    buttonPressed = true;
                    playerInput[i] = j;
                    digitalWrite(ledPins[j], HIGH);
                    delay(200);
                    digitalWrite(ledPins[j], LOW);
                    if (playerInput[i] != sequence[i])
                    {
                        return false;
                    }
                    delay(500);
                }
            }
        }
    }
    return true;
}

void resetGame()
{
    level = 0;
    generateSequence();
    delay(1000);
}
