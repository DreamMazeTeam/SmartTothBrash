#include <Arduino.h>

#define DB_SERIAL

void setup()
{
#ifdef DB_SERIAL
    Serial.begin(9600);
#endif
}

void loop() 
{

}