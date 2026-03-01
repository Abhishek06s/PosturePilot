# 📏 Smart Posture Monitoring System (ESP32 + IoT)

A real-time IoT-based posture monitoring system using ESP32 and HC-SR04 ultrasonic sensor. The system detects bad sitting posture and sends alerts to an Android app via Bluetooth while displaying live status on a 16x2 LCD.

## 🚀 Features
- Real-time posture detection
- 10-second bad posture alert
- 45-minute sitting reminder
- Bluetooth communication with Android app
- LCD live distance display
- Automatic alert reset when posture improves

## 🛠 Hardware Used
- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- 16x2 LCD
- Jumper Wires

## 📱 Mobile App
Built using MIT App Inventor.
- Connects via Bluetooth (`ESP32_Posture`)
- Displays distance & posture status
- Shows alerts only when required

## ⚙️ How It Works
1. Ultrasonic sensor measures user distance.
2. If distance exceeds threshold → Bad Posture.
3. If bad posture persists >10s → Alert sent.
4. If sitting >45 min → Break reminder.
5. Alert clears automatically when posture becomes good.

## 🔮 Future Improvements
- Cloud data logging
- Buzzer/vibration alert
- Posture analytics dashboard

---
Developed as an IoT health monitoring prototype.
