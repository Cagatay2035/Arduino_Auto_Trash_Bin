#include <Servo.h>

int trigPin = 7;
int echoPin = 6;
int servoPin = 9;

Servo servoMotor;

#define OPEN true
#define CLOSE false

bool kapakDurumu = CLOSE;
unsigned long baslangicZamani;
unsigned long baslangicZamani2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin, OUTPUT);
  servoMotor.attach(servoPin);
}

void loop() {
  long mesafe = mesafeOlc();

  if (mesafe < 10 && kapakDurumu == CLOSE) {
    servoMotor.write(90);
    kapakDurumu = OPEN;
    baslangicZamani = millis();
  }

  if (mesafe < 10 && kapakDurumu == OPEN && (millis() - baslangicZamani) > 10000) {
    servoMotor.write(0);
    while(mesafe<10){
      kapakDurumu = CLOSE;
    }
    kapakDurumu = CLOSE;
  }

  if (mesafe > 10 && kapakDurumu == OPEN) {
    baslangicZamani2 = millis();
    if ((millis() - baslangicZamani2) > 3000) {
      servoMotor.write(0);
      kapakDurumu = CLOSE;
    }
  }
}

long mesafeOlc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long sure = pulseIn(echoPin, HIGH);
  return sure / 58.2;
}