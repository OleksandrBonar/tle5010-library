#include <tle5010.h>

#define PIN_CS 10

TLE5010_SPI sensor(PIN_CS);

void setup() {
  // 4 MHZ square wave on pin 9
  TCCR1A = (0 << COM1A1) | (1 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);
  TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
  OCR1A = 0x01;
  ICR1 = 0;
  pinMode(9, OUTPUT);

  // Init
  sensor.begin();

  Serial.begin(9600);
}

void loop() {
  int angleInt;

  // Read integer value
  angleInt = sensor.readInteger();
  
  Serial.println(" Integer value: " + String(angleInt));
}
