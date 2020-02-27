// Раскоментировать строку для компиляции в Arduino IDE
//#define ARDUINO_IDE


#ifndef ARDUINO_IDE
#include <Arduino.h>
#endif

// Для отладки
#define DB_SERIAL

// Пины
#define GL_PIN_UP 0
#define GL_PIN_DOWN 0
#define GR_PIN_UP 0
#define GR_PIN_DOWN 0

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


#ifdef DB_SERIAL
void db_print()
{

}
#endif


void setup()
{
#ifdef DB_SERIAL
    Serial.begin(9600);
    Serial.println("Debug mod -> on");
#endif

    // Настройка нашего всевдо гироскопа
    for (int i = 0; i < GYRO_PINS_COUNT; i++){
        pinMode(GYRO_PINS[i], INPUT);
    }
}


void loop() 
{
#ifdef DB_SERIAL
    db_print();
#endif
}