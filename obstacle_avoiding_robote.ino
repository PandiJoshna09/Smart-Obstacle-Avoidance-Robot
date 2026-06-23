#include <Servo.h>

Servo servoMotor;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

// Motor pins (change according to your wiring)
const int ENA = 5;
const int IN1 = 2;
const int IN2 = 3;
const int ENB = 6;
const int IN3 = 4;
const int IN4 = 7;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servoMotor.attach(servoPin);
  servoMotor.write(90);

  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  if (distance > 20) {
    moveForward();
  } else {
    stopMotors();
    delay(300);

    moveBackward();
    delay(500);

    stopMotors();

    servoMotor.write(0);
    delay(500);
    int leftDistance = getDistance();

    servoMotor.write(180);
    delay(500);
    int rightDistance = getDistance();

    servoMotor.write(90);
    delay(500);

    if (leftDistance > rightDistance) {
      turnLeft();
      delay(500);
    } else {
      turnRight();
      delay(500);
    }
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
