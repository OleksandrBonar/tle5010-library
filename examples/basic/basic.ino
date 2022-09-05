#include <tle5010.h>

#define PIN_CS 10

tle5010_spi sensor(PIN_CS);

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
  double angle;
  int x, y;

  int times[2];

  // Read angle and measure time
  times[0] = micros();
  angle=sensor.readAngleRadians();
  times[1] = micros();
  x = sensor.x;
  y = sensor.y;
  
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Angle: ");
  Serial.print(angle);
  Serial.print(" Time: ");
  Serial.print(times[1] - times[0]);
  Serial.println();;
}
