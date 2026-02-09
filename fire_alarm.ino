#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

const int FlameS = 7;
const int crvena = 6;
const int zelena = 4;
const int buzzer = 3;
const int tempPin = A0; 
bool alarmAktivan = false;

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  pinMode(FlameS, INPUT);
  pinMode(crvena, OUTPUT);
  pinMode(zelena, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  Serial.println("Sistem spreman.");
  digitalWrite(zelena, HIGH);
}

void loop() {
  int flame = digitalRead(FlameS);

  int tempRaw = analogRead(tempPin);
  float voltage = tempRaw * (5.0 / 1023.0);
  float temperatura = voltage * 30.0; 

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (!alarmAktivan && flame == HIGH) {
    Serial.println("VATRA DETEKTOVANA!");
    alarmAktivan = true;
  }

  if (alarmAktivan) {
    digitalWrite(crvena, HIGH);
    tone(buzzer, 4000);
    digitalWrite(zelena, LOW);
    delay(250);
    digitalWrite(crvena, LOW);
    noTone(buzzer);
    delay(250);

    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      Serial.println("KARTICA OCITANA – alarm isključen");
      alarmAktivan = false;
      digitalWrite(crvena, LOW);
      noTone(buzzer);
      delay(500);
    }
  } else {
    digitalWrite(zelena, HIGH);
    digitalWrite(crvena, LOW);
    noTone(buzzer);
  }

  delay(500); 
}
