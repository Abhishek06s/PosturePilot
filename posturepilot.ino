#include <LiquidCrystal.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// LCD pins
const int RS = 5, EN = 18, D4 = 19, D5 = 21, D6 = 22, D7 = 23;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Ultrasonic pins
const int trigPin = 4;
const int echoPin = 2;

// Thresholds
const int postureThreshold = 25;      // cm for bad posture
const int userGoneThreshold = 70;     // cm = user not sitting
const unsigned long badPostureTime = 10000; // 10 s
const unsigned long sitTimeLimit  = 45UL * 60UL * 1000UL; // 45 min

// Variables
unsigned long badStart = 0;
unsigned long sitStart = 0;
bool badPosture = false;
bool sitting = false;
bool notifiedBad = false;
bool notifiedSitTime = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Posture Monitor");
  delay(2000);
  lcd.clear();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);
  SerialBT.begin("ESP32_Posture");
  Serial.println("Bluetooth started. Pair with 'ESP32_Posture'");
}

void loop() {
  float distance = getDistance();
  unsigned long now = millis();

  // Detect sitting
  if (distance < userGoneThreshold) {
    if (!sitting) {
      sitting = true;
      sitStart = now;
      notifiedSitTime = false;
    }
  } else {
    sitting = false;
    badPosture = false;
    notifiedBad = false;
  }

  // --- LCD display ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.print(distance, 1);
  lcd.print("cm");

  if (sitting) {
    if (distance > postureThreshold) {
      lcd.setCursor(0, 1);
      lcd.print("Sit Straight!  ");

      if (!badPosture) {
        badPosture = true;
        badStart = now;
      }

      // Alert to app after 10 seconds
      if ((now - badStart > badPostureTime) && !notifiedBad) {
        SerialBT.println("ALERT: Bad Posture for 10s more than, Sit straight!.");
        notifiedBad = true;
      }
    } else {
      badPosture = false;
      notifiedBad = false;
      lcd.setCursor(0, 1);
      lcd.print("Good Posture   ");
    }

    // Alert app if sitting > 45 mins
    if (!notifiedSitTime && (now - sitStart > sitTimeLimit)) {
      SerialBT.println("ALERT: Sitting for more than 45 min, Take a break!.");
      notifiedSitTime = true;
    }

  } else {
    lcd.setCursor(0, 1);
    lcd.print("No User        ");
  }

  // --- Send live data to App ---
  String postureStatus;
  if (!sitting) postureStatus = "No User.";
  else if (distance > postureThreshold) postureStatus = "Bad Posture.";
  else postureStatus = "Good Posture.";

  // Send combined data line
  SerialBT.print("DATA:");
  SerialBT.print(distance, 1);
  SerialBT.print(",");
  SerialBT.println(postureStatus);

  delay(800);
}

// Distance measurement
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return (duration * 0.0343) / 2.0;
}
