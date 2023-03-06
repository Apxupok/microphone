#include <Arduino.h>
#include <NewPing.h>

#define RELAY_IN1 10
#define RELAY_IN2 11
#define RELAY_IN3 12

#define PIN_TRIG 6
#define PIN_ECHO 7

#define MAX_DISTANCE 200 // Константа для определения максимального расстояния, которое мы будем считать корректным.

const int sensorD0 = 0;  // пин для выхода D0 датчика
const int led = 13; // пин светодиода
boolean ledRalay = 0;
boolean disrel = 0;
boolean disrel1 = 0;

// Создаем объект, методами которого будем затем пользоваться для получения расстояния.
// В качестве параметров передаем номера пинов, к которым подключены выходы ECHO и TRIG датчика
NewPing sonar(PIN_TRIG, PIN_ECHO, MAX_DISTANCE);


void setup ()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT); // устанавливаем цифровой пин 2 в режим выхода
  pinMode(RELAY_IN1, OUTPUT);
  pinMode(RELAY_IN2, OUTPUT);
  pinMode(RELAY_IN3, OUTPUT);
  
}


void loop ()
{
   // делаем паузу, чтобы светодиод горел 1 секунду 
  int sensorValue = digitalRead(sensorD0); // получаем сигнал с датчика

  if (sensorValue == 0) //если получен сигнал от датчика в виде единицы
  {
    if (ledRalay==0){
      ledRalay = 1;
    }
    else {
      ledRalay =0;
    }
    digitalWrite(led, HIGH); // включаем светодиод
    
    digitalWrite(RELAY_IN1, ledRalay);
    Serial.println(ledRalay);
    
      // Стартовая задержка, необходимая для корректной работы.
  delay(150);
  }

  // Получаем значение от датчика расстояния и сохраняем его в переменную
  int distance = sonar.ping_cm();

  // Печатаем расстояние в мониторе порта
  Serial.print(distance);
  if (distance != 0){
    if (disrel==0){
      disrel = 1;
      disrel1 = 0;
    }
    else {
      disrel =0;
      disrel1 = 1;
    }
    digitalWrite(RELAY_IN2, disrel);
    digitalWrite(RELAY_IN3, disrel1);
    delay(2000);
  }
   

}





