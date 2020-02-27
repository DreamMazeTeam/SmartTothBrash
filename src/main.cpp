#include <Arduino.h>


// Для отладки
#define DB_SERIAL

// Пины
#define GL_PIN_UP 0
#define GL_PIN_DONW 0
#define GR_PIN_UP 0
#define GR_PIN_DOWN 0

const int GYRO_PINS_COUNT = 4;
const int GYRO_PINS[GYRO_PINS_COUNT] = {
    GL_PIN_UP,
    GL_PIN_DONW,
    GR_PIN_UP,
    GR_PIN_DOWN
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