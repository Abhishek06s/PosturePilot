# Smart Posture Monitor

An IoT-based posture correction system built using ESP32 and an ultrasonic sensor.  
The system monitors sitting distance in real time and triggers alerts when poor posture is detected for a prolonged duration.

---

## Overview

This project aims to reduce long-term spinal strain caused by improper sitting posture.  
Distance is measured using an HC-SR04 sensor and processed by an ESP32.  
Status and alerts are displayed locally on a 16x2 LCD and remotely via a Bluetooth-connected Android application.

---

## Hardware

- ESP32 Dev Board  
- HC-SR04 Ultrasonic Sensor  
- 16x2 LCD  
- Jumper wires  
- USB Power Supply  

---

## System Logic

- Measure user distance continuously  
- Compare with predefined posture threshold  
- If bad posture persists for 10 seconds → Trigger alert  
- If sitting exceeds 45 minutes → Break reminder  
- Automatically reset alert when posture improves  

---

## Mobile Application

Built using MIT App Inventor.

Features:
- Bluetooth connection to ESP32  
- Live distance display  
- Posture status updates  
- Alert notifications  

---

## Future Scope

- Cloud data logging  
- Posture analytics dashboard  
- Vibration/buzzer alerts  
- Battery-powered portable version  

---

Developed as an IoT health-tech prototype.
