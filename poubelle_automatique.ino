#include <Servo.h>

#define algilanirken_bekle 5000
#define kapanmadan_bekle 3000
#define sinir 10
#define en_son_bekle 1000

#define echo 6
#define trig 7

Servo motor;
Servo servoMotor; 

#define OPEN true
#define CLOSE false

bool kapakDurumu = CLOSE;
unsigned long baslangicZamani;
unsigned long baslangicZamani2;

void setup() {
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  motor.attach(9);
  servoMotor.attach(10); 
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trig, LOW);

  float zaman = pulseIn(echo, HIGH);
  float uzaklik = zaman / 58.2;
  Serial.print("Mesafe: ");
  Serial.println(uzaklik);

 
  motor.write(0);
  kapakDurumu = CLOSE;
  Serial.println("Kapı kapatılıyor...");

 
  if(uzaklik < sinir && kapakDurumu == CLOSE){
    motor.write(90);
    kapakDurumu = OPEN;
    baslangicZamani = millis();
    Serial.println("Kapı açılıyor...");
  }

 
  if (uzaklik < sinir && kapakDurumu == OPEN && (millis() - baslangicZamani) > algilanirken_bekle) {
    servoMotor.write(0);
    kapakDurumu = CLOSE;
    Serial.println("Kapı servo ile kapatılıyor...");
  }

 
  if (uzaklik > sinir && kapakDurumu == OPEN) {
    delay(kapanmadan_bekle);
    servoMotor.write(0);
    kapakDurumu = CLOSE;
    Serial.println("Kapı uzaklaşan biri nedeniyle servo ile kapatılıyor...");
  }
  
  delay(en_son_bekle); 
}
