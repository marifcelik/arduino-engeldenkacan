#include <Arduino.h>

byte MotorSol1 = 7;
byte MotorSol2 = 6;
byte MotorSolguc = 3;
byte MotorSag1 = 5;
byte MotorSag2 = 4;
byte MotorSagguc = 9;

byte echo = 12;
byte trig = 13;

long sure, mesafe;

void setup()
{
    pinMode(trig, OUTPUT); // ses dalgaları yollayacağımız pin
    pinMode(echo, INPUT);  // bize ses dalgaları geri geleceğinden input pini
    pinMode(MotorSol1, OUTPUT);
    pinMode(MotorSol2, OUTPUT);
    pinMode(MotorSag1, OUTPUT);
    pinMode(MotorSag2, OUTPUT);
    pinMode(MotorSagguc, OUTPUT);
    pinMode(MotorSolguc, OUTPUT);

    Serial.begin(9600);
}

void ileri()
{
    digitalWrite(MotorSag1, LOW); // İleri yönde gitmesi için low ve high
    digitalWrite(MotorSag2, HIGH);
    digitalWrite(MotorSol1, HIGH); // İleri yönde gitmesi için high ve low
    digitalWrite(MotorSol2, LOW);

    analogWrite(MotorSagguc, 150);
    analogWrite(MotorSolguc, 150);
}

void sag()
{
    digitalWrite(MotorSag1, LOW); // İleri yönde gitmesi için low ve high
    digitalWrite(MotorSag2, HIGH);
    digitalWrite(MotorSol1, HIGH); // İleri yönde gitmesi için high ve low
    digitalWrite(MotorSol2, LOW);

    analogWrite(MotorSagguc, 0); // saga dönebilmesi için sadece sol motoru çalıştırıyorum.
    analogWrite(MotorSolguc, 150);
}

void geri()
{
    digitalWrite(MotorSag1, HIGH); // tersi yönde hareket etmesi için değerleri değiştiriyorum
    digitalWrite(MotorSag2, LOW);
    digitalWrite(MotorSol1, LOW);
    digitalWrite(MotorSol2, HIGH);

    analogWrite(MotorSagguc, 150); // 150 hız veriyoruz
    analogWrite(MotorSolguc, 150);
}

void loop()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    sure = pulseIn(echo, HIGH);
    mesafe = (sure / 2) * 0.0343;
    Serial.println(mesafe);

    if (mesafe < 30)
    {
        geri();
        delay(500);
        sag();
        delay(700);
    }
    else
    {
        ileri();
    }
}
