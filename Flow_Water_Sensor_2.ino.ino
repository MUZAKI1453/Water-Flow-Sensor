#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

volatile int flow_frequency = 0;
float vol = 0.0, l_minute = 0.0;
const int flowsensorPin = 2; // Sesuaikan pin sensor jika perlu
unsigned long currentTime;
unsigned long cloopTime;

// Fungsi interrupt untuk menghitung frekuensi pulsa dari sensor
void flow() {
  flow_frequency++;
}

void setup() {
  Serial.begin(9600);
  pinMode(flowsensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowsensorPin), flow, RISING);

  lcd.begin(16, 2); // Inisialisasi LCD dengan 16 kolom dan 2 baris
  lcd.clear();
  lcd.print(F("Subscribe my YT"));
  lcd.setCursor(0, 1);
  lcd.print(F("Mr Controllers Noobs"));

  delay(2000); // Biarkan pesan awal tampil selama 2 detik
  lcd.clear();

  currentTime = millis();
  cloopTime = currentTime;
}

void loop() {
  currentTime = millis();
  
  // Setiap detik, hitung laju aliran dan volume total
  if (currentTime >= (cloopTime + 1000)) {
    cloopTime = currentTime;

    if (flow_frequency != 0) {
      l_minute = (flow_frequency / 7.5); // Konversi ke L/min
      vol += l_minute / 60; // Update volume total dalam liter
    } else {
      l_minute = 0; // Jika tidak ada aliran, set l_minute ke 0
    }

    flow_frequency = 0; // Reset frekuensi untuk siklus berikutnya

    // Tampilkan informasi di LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rate: ");
    lcd.print(l_minute);
    lcd.print(" L/M");
    lcd.setCursor(0, 1);
    lcd.print("Vol: ");
    lcd.print(vol);
    lcd.print(" L");

    // Tampilkan juga di Serial Monitor
    Serial.print("Laju Aliran: ");
    Serial.print(l_minute);
    Serial.println(" L/M");
    Serial.print("Volume: ");
    Serial.print(vol);
    Serial.println(" L");
  }
}
