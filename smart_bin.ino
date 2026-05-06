#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define IR_SENSOR 7
#define SERVO_PIN 6

Servo myServo;

long duration;
int distance;
int wasteLevel;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0); // lid closed

  Serial.begin(9600);
}

void loop() {
  // Ultrasonic distance measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Convert to waste level %
  wasteLevel = map(distance, 2, 30, 100, 0);

  Serial.print("Waste Level: ");
  Serial.print(wasteLevel);
  Serial.println("%");

  // IR sensor for lid open
  if (digitalRead(IR_SENSOR) == LOW) {
    myServo.write(90); // open lid
    delay(3000);
    myServo.write(0);  // close lid
  }

  delay(1000);
}
