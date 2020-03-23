#include <Arduino.h>

// Pins definations
#define FLASK_X       6
#define FLASK_Y       4
#define ENGINE_LEFT  10
#define ENGINE_RIGHT 12


#define LEFT          0
#define RIGHT         1
#define DOWN          0
#define UP            1

// Update flasks rate
#define TICK         10
#define DEBUG         1

#if DEBUG == 1
    #define println(x) Serial.println(x)
    #define print(x) Serial.print(x)
#else 
    #define println(x)
    #define print(x)
#endif

enum class Direction{ No, Left, Right, _count };
Direction EngineDirection = Direction::No;

int xFlask = LEFT;
int yFlask = DOWN;

void setEngineDirection(Direction dir)
{
    print("Engines in pos ->");

    switch (dir)
    {
    case Direction::Left:
        digitalWrite(ENGINE_LEFT, HIGH);
        digitalWrite(ENGINE_RIGHT, LOW);
        println("Left");
        break;

    case Direction::Right:
        digitalWrite(ENGINE_LEFT, LOW);
        digitalWrite(ENGINE_RIGHT, HIGH);
        println("Right");
        break;

    case Direction::No:
        digitalWrite(ENGINE_LEFT, LOW);
        digitalWrite(ENGINE_RIGHT, LOW);
        println("No");
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
        return Direction::Right;
    }
    else if (xFlask == RIGHT && yFlask == UP) {
        return Direction::Left;
    }
    return Direction::No;
}

void setup()
{
    pinMode(ENGINE_LEFT, OUTPUT);
    pinMode(ENGINE_RIGHT, OUTPUT);
    pinMode(FLASK_X, INPUT);
    pinMode(FLASK_Y, INPUT);
    pinMode(FLASK_Y-1, OUTPUT);
    digitalWrite(FLASK_Y-1, HIGH);
    pinMode(FLASK_X-1, OUTPUT);
    digitalWrite(FLASK_X-1, HIGH);

#if DEBUG == 1
    Serial.begin(9600);
#endif
}


uint32_t timer = 0;
int xPrev = xFlask;
int yPrev = yPrev;
void tick()
{
    int x = digitalRead(FLASK_X);
    int y = digitalRead(FLASK_Y);

    print("Flask x -> ");
    println(x);
    print("Flask y -> ");
    println(y);

    if (millis() - timer >= TICK){

        if (xPrev == x) xFlask = x;
        if (yPrev == y) yFlask = y;
        
        timer = millis();

        println("Tick");
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