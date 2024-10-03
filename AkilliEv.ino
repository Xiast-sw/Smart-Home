#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0X27, 16, 2);
dht11 DHT11;

int DHT11PIN = 5;
int fan = 6;
int buton = 7;
int buzzer1 = 8;
int yanginPin = 9;
int buzzer2 = 10;
int buzzer3 = 11;
int pirPin = 12;
int ledPin = 13;
int gazPin = A0;

int yangin;
int hareket;
int sensor_durum;
int esik_deger = 500;
int durum = 0;
int butondeger = 0;

byte customChar[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.createChar(0, customChar);
  pinMode(buton, INPUT);
  pinMode(yanginPin, INPUT);
  
  pinMode(pirPin, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(ledPin, OUTPUT);
  lcd.setCursor(7, 1);
  lcd.print("Xiast");
  lcd.setCursor(5, 2);
  lcd.print("Technology");
  delay(3000);
  lcd.clear();
  lcd.noBacklight();
  delay(100);
  lcd.backlight();
}

void loop() {
  yangin = !digitalRead(yanginPin);
  hareket = !digitalRead(pirPin);
  sensor_durum = analogRead(gazPin);
  int chk = DHT11.read(DHT11PIN);

  //yangın var
  if (yangin == HIGH && hareket == HIGH && sensor_durum > esik_deger) {
    EEPROM.update(0, 1);
  }
  else {
    EEPROM.update(0, 0);
  }
  //hiçbir durum yok
  if (yangin == LOW && hareket == HIGH && sensor_durum > esik_deger) {
    EEPROM.update(1, 1);
  }
  else {
    EEPROM.update(1, 0);
  }
  //hareket ve yangın var
  if (yangin == HIGH && hareket == LOW && sensor_durum > esik_deger) {
    EEPROM.update(2, 1);
  }
  else {
    EEPROM.update(2, 0);
  }
  //yangın ve gaz var
  if (yangin == HIGH && hareket == HIGH && sensor_durum < esik_deger) {
    EEPROM.update(3, 1);
  }
  else {
    EEPROM.update(3, 0);
  }
  //hareket var
  if (yangin == LOW && hareket == LOW && sensor_durum  > esik_deger) {
    EEPROM.update(4, 1);
  }
  else {
    EEPROM.update(4, 0);
  }
  //gaz var
  if (yangin == LOW && hareket == HIGH && sensor_durum < esik_deger) {
    EEPROM.update(5, 1);
  }
  else {
    EEPROM.update(5, 0);
  }
  //hareket,gaz ve yangın var
  if (yangin == HIGH && hareket == LOW && sensor_durum < esik_deger) {
    EEPROM.update(6, 1);
  }
  else {
    EEPROM.update(6, 0);
  }
  //hareket ve gaz var
  if (yangin == LOW && hareket == LOW && sensor_durum < esik_deger) {
    EEPROM.update(7, 1);
  }
  else {
    EEPROM.update(7, 0);
  }  
  if (EEPROM.read(0) == 1) {
   YANGIN();
  }
  else if (EEPROM.read(5) == 1) {
    GAZ();
  }
  else if (EEPROM.read(4) == 1) {
    HAREKET();
  }
  else if (EEPROM.read(2) == 1) {
   YANGIN_HAREKET();
  }
  else if (EEPROM.read(3) == 1) {
   YANGIN_GAZ();
  }
  else if (EEPROM.read(7) == 1) {
   GAZ_HAREKET();
  }
  else if (EEPROM.read(6) == 1) {
   YANGIN_GAZ_HAREKET();
  }
  else {
    digitalWrite(buzzer1, LOW);
  }
  
  Serial.print("0: ");
  Serial.println(EEPROM.read(0));
  Serial.print("1: ");
  Serial.println(EEPROM.read(1));
  Serial.print("2: ");
  Serial.println(EEPROM.read(2));
  Serial.print("3: ");
  Serial.println(EEPROM.read(3));
  Serial.print("4: ");
  Serial.println(EEPROM.read(4));
  Serial.print("5: ");
  Serial.println(EEPROM.read(5));
  Serial.print("6: ");
  Serial.println(EEPROM.read(6));
  Serial.print("7: ");
  Serial.println(EEPROM.read(7));

  lcd.setCursor(6, 0);
  lcd.print("Nem: %");
  lcd.print((float)DHT11.humidity, 0);
  lcd.setCursor(3, 1);
  lcd.print("Sicaklik:" );
  lcd.setCursor(13, 1);
  lcd.print((float)DHT11.temperature, 0);
  lcd.setCursor(15, 1);
  lcd.write((uint8_t)0);
  lcd.setCursor(16, 1);
  lcd.print("C");
  delay(500);
}
void YANGIN() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(5, 2);
    lcd.print("YANGIN VAR");
    delay(500);
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
void GAZ() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(4, 2);
    lcd.print("GAZ KACAGI VAR!");
    delay(500);
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
void HAREKET() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(6, 2);
    lcd.print("HAREKET VAR!");
    delay(500);
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
void YANGIN_GAZ() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(1, 2);
    lcd.print("YANGIN VE GAZ VAR!");
    delay(500);
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
void YANGIN_HAREKET() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("YANGIN & HAREKET VAR");
    delay(500);
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
void GAZ_HAREKET() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(1, 2);
    lcd.print("GAZ & HAREKET VAR!");
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
void YANGIN_GAZ_HAREKET() {
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(buzzer1, HIGH);
    lcd.setCursor(5, 2);
    lcd.print("YANGIN & GAZ KACAGI");
    delay(500);
    digitalWrite(buzzer1, LOW);
    lcd.clear();
    delay(500);
  }
}
