#include <Arduino.h>


#define DB_SERIAL


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
}


void loop() 
{
#ifdef DB_SERIAL
    db_print();
#endif
}