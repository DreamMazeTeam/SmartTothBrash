// Раскоментировать строку для компиляции в Arduino IDE
//#define ARDUINO_IDE


#ifndef ARDUINO_IDE
#include <Arduino.h>
#endif

#include <EEPROM.h>

// Для отладки
//#define DB_SERIAL
#ifdef DB_SERIAL
uint16_t DELAY = 1000;
uint16_t TIMER = 0;
#endif

// Пины
#define GL_PIN_UP 0
#define GL_PIN_DOWN 0
#define GR_PIN_UP 0
#define GR_PIN_DOWN 0
#define ENGINE_LEFT 0
#define ENGINE_RIGHT 0


// Чуть чуть редефов
#define G_PIN_180 GR_PIN_UP
#define G_PIN_90_UP GL_PIN_UP
#define G_PIN_90_DOWN GL_PIN_DOWN


const int GYRO_PINS_COUNT = 3;
const int GYRO_PINS[GYRO_PINS_COUNT] = {
    G_PIN_90_UP,
    G_PIN_90_DOWN,
    G_PIN_180,
//    GR_PIN_DOWN
};


enum class Direction{ No, Left, Right, _count };
Direction EngineDirection = Direction::No;


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

    default:
        break;
    }
}


Direction getDirectionFromGyroState()
{
    // Логику поворота щетки относительно данных из GYRO_PINS
    return Direction::No;
}


#ifdef DB_SERIAL
void db_print()
{
    Serial.print("Состояние гироскопа: \t");
    for (int i = 0; i < GYRO_PINS_COUNT; i++){
        Serial.print(GYRO_PINS[i]);
        Serial.print("\t");
    }

    Serial.print("\nМоторы в состоянии: Direction::");
    Serial.println(static_cast<int>(EngineDirection));
}
#endif


void setup()
{
#ifdef DB_SERIAL
    Serial.begin(9600);
    Serial.println("Debug mod -> on");
    TIMER = millis();
#endif

    // Настройка нашего всевдо гироскопа
    for (int i = 0; i < GYRO_PINS_COUNT; i++){
        pinMode(GYRO_PINS[i], INPUT);
    }

    pinMode(ENGINE_LEFT, OUTPUT);
    pinMode(ENGINE_RIGHT, OUTPUT);

    EngineDirection = getDirectionFromGyroState();
    setEngineDirection(EngineDirection);
}


void loop() 
{
#ifdef DB_SERIAL
    if ((millis() - TIMER) >= DELAY) {
        TIMER = millis();
        db_print();
    }
#endif
}