#include <Arduino.h>

#define FLASK_X       5
#define FLASK_Y       6
#define ENGINE_LEFT  11
#define ENGINE_RIGHT 10
#define LEFT          0
#define RIGHT         1
#define DOWN          0
#define UP            1
#define TICK        250

enum class Direction{ No, Left, Right, _count };
Direction EngineDirection = Direction::No;

uint8_t xFlask = LEFT;
uint8_t yFlask = DOWN;

void setEngineDirection(Direction dir) {
    switch (dir)
    {
    case Direction::Left:
        digitalWrite(ENGINE_LEFT, HIGH);
        digitalWrite(ENGINE_RIGHT, LOW);
        break;

    case Direction::Right:
        digitalWrite(ENGINE_LEFT, LOW);
        digitalWrite(ENGINE_RIGHT, HIGH);
        break;

    case Direction::No:
        digitalWrite(ENGINE_LEFT, LOW);
        digitalWrite(ENGINE_RIGHT, LOW);
        break;
    }
}


Direction getDirectionFromFlasks()
{
    if (xFlask == LEFT && yFlask == DOWN) {
        return Direction::Left;
    }
    else if (xFlask == LEFT && yFlask == UP) {
        return Direction::Right;
    }
    else if (xFlask == RIGHT && yFlask == DOWN) {
        return Direction::Left;
    }
    else if (xFlask == RIGHT && yFlask == UP) {
        return Direction::Right;
    }
    return Direction::No;
}

void setup()
{
    pinMode(ENGINE_LEFT, OUTPUT);
    pinMode(ENGINE_RIGHT, OUTPUT);
    pinMode(FLASK_X, INPUT);
    pinMode(FLASK_Y, INPUT);
}

void tick()
{
    static uint32_t timer = 0;
    static uint8_t xPrev = xFlask;
    static uint8_t yPrev = yPrev;

    uint8_t x = digitalRead(FLASK_X);
    uint8_t y = digitalRead(FLASK_Y);

    if (millis() - timer >= TICK){

        if (xPrev == x) xFlask = x;
        if (yPrev == y) yFlask = y;

        timer = millis();
    }

    xPrev = x;
    yPrev = y;
}

void loop() 
{
    tick();

    EngineDirection = getDirectionFromFlasks();
    setEngineDirection(EngineDirection);
}