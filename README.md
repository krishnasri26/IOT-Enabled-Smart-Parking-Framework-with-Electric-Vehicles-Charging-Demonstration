# IOT-Enabled-Smart-Parking-Framework-with-Electric-Vehicles-Charging-Demonstration


## Overview

This project presents an IoT-based Smart Parking System integrated with Electric Vehicle (EV) Charging Slot Monitoring using an ESP32 microcontroller and the Blynk IoT platform.

The system automatically manages vehicle entry and exit using ultrasonic sensors and a servo-controlled gate. Parking slot occupancy is detected using IR sensors, while EV charging slots are monitored separately. Real-time parking status and charging slot availability are displayed on an LCD screen and remotely monitored through the Blynk IoT mobile application.

---

## Features

- Smart automatic parking gate using ESP32
- Vehicle detection using ultrasonic sensors
- Servo motor controlled entry/exit barrier
- Real-time parking slot monitoring
- Separate Fuel Vehicle and EV Parking Slots
- EV charging slot status monitoring
- LED indication for occupied slots
- LCD display for slot availability
- Blynk IoT cloud monitoring
- Real-time updates through mobile app

---

## Hardware Components

| Component | Quantity |
|------------|----------|
| ESP32 Development Board | 1 |
| Ultrasonic Sensor HC-SR04 | 2 |
| IR Sensors | 6 |
| Servo Motor SG90 | 1 |
| LEDs | 6 |
| 16x2 LCD with I2C Module | 1 |
| EV Charging Demo Cables | 3 |
| Breadboard | 1 |
| Jumper Wires | As Required |
| Power Supply | 5V |

---

## System Architecture

### Entry and Exit Control

- Ultrasonic Sensor 1 detects approaching vehicles.
- ESP32 activates the servo motor to open the gate.
- Ultrasonic Sensor 2 detects vehicle passage.
- Servo motor closes the gate automatically.

### Fuel Vehicle Slots

- Three parking slots monitored using IR sensors.
- LEDs indicate occupied slots.
- Slot status is displayed on LCD and Blynk App.

### EV Charging Slots

- Three EV parking slots monitored using IR sensors.
- LED glows when a vehicle occupies the slot.
- Charging cable demonstration indicates EV charging process.
- Slot occupancy updates are sent to Blynk Cloud.

---

## Working Flow

1. Vehicle approaches parking gate.
2. Ultrasonic Sensor 1 detects vehicle.
3. Servo motor opens gate.
4. Vehicle passes through gate.
5. Ultrasonic Sensor 2 detects vehicle.
6. Servo motor closes gate.
7. Vehicle parks in Fuel or EV slot.
8. IR sensor detects occupancy.
9. Corresponding LED turns ON.
10. LCD updates available slots.
11. ESP32 sends data to Blynk IoT Cloud.
12. User monitors parking status through Blynk Mobile App.
13. When vehicle exits, slot status updates automatically.

---

## Pin Configuration

| ESP32 Pin | Component |
|------------|-----------|
| GPIO 18 | Servo Motor |
| GPIO 5 | Ultrasonic Sensor 1 Trigger |
| GPIO 19 | Ultrasonic Sensor 1 Echo |
| GPIO 2 | Ultrasonic Sensor 2 Trigger |
| GPIO 15 | Ultrasonic Sensor 2 Echo |
| GPIO 21 | LCD SDA |
| GPIO 22 | LCD SCL |
| GPIO 34 | Fuel Slot IR Sensor 1 |
| GPIO 35 | Fuel Slot IR Sensor 2 |
| GPIO 36 | Fuel Slot IR Sensor 3 |
| GPIO 25 | EV Slot IR Sensor 1 |
| GPIO 26 | EV Slot IR Sensor 2 |
| GPIO 27 | EV Slot IR Sensor 3 |

---

## Software Requirements

- Arduino IDE
- ESP32 Board Package
- Blynk IoT Platform
- Blynk Mobile App
- LiquidCrystal_I2C Library
- ESP32Servo Library
- WiFi Library

---

## Blynk Dashboard

The Blynk application displays:

- Total Available Slots
- Fuel Vehicle Slot Status
- EV Slot Status
- Charging Slot Availability
- Entry and Exit Monitoring
- Real-Time Notifications

---

## Project Structure

```
Smart-Parking-EV-Charging/
│
├── Arduino_Code/
│   ├── SmartParking.ino
│
├── Circuit_Diagram/
│   ├── circuit.png
│
├── Flowchart/
│   ├── flowchart.png
│
├── Images/
│   ├── prototype.jpg
│   ├── blynk_dashboard.jpg
│
└── README.md
```

---

## Results

- Automated vehicle entry and exit.
- Accurate parking slot detection.
- Real-time slot monitoring.
- Dedicated EV charging slot management.
- Mobile monitoring through Blynk IoT.
- Reduced parking congestion.

---

## Future Enhancements

- QR Code Based Parking Access
- RFID Vehicle Authentication
- Online Slot Reservation
- AI-Based Parking Prediction
- License Plate Recognition
- Payment Gateway Integration
- Smart City Deployment

---

## Applications

- Smart Cities
- Shopping Malls
- Airports
- Universities
- Office Campuses
- EV Charging Stations
- Commercial Parking Facilities

---

## Authors

**Krishna Srivastava,
  Divyansh Dwivedi**

Department of Electronics and Communication Engineering

---

## License

This project is developed for educational and research purposes.
