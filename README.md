# IOT-Enabled-Smart-Parking-Framework-with-Electric-Vehicles-Charging-Demonstration


## Overview

This project presents an IoT-based Smart Parking Framework integrated with Electric Vehicle (EV) Charging capabilities. The system enables real-time monitoring of parking slots, automated vehicle detection, parking space management, and EV charging station availability through connected IoT devices and cloud services.

The framework aims to reduce parking congestion, improve parking efficiency, and support sustainable transportation by integrating smart charging infrastructure for electric vehicles.

---

## Features

- Real-time parking slot monitoring
- Vehicle presence detection using IoT sensors
- Smart parking space allocation
- EV charging station management
- Live availability updates through web/mobile dashboard
- Automated entry and exit tracking
- Cloud-based data storage and analytics
- Parking occupancy visualization
- Charging status monitoring
- Notifications and alerts

---

## System Architecture

```
+---------------------+
|     IoT Sensors     |
| (IR/Ultrasonic)     |
+----------+----------+
           |
           v
+---------------------+
|  ESP32              |
| Microcontroller     |
+----------+----------+
           |
           v
+---------------------+
| Wi-Fi               |
| Communication Layer |
+----------+----------+
           |
           v
+---------------------+
| Cloud Server        |
| Database            |
+----------+----------+
           |
           v
+---------------------+
| Web/Mobile App      |
| Dashboard           |
+---------------------+
```

---

## Hardware Requirements

- ESP32 Development Board
- Ultrasonic Sensors (HC-SR04) or IR Sensors
- Servo Motor (Gate Control)
- EV Charging Module (Prototype)
- Jumper Wires
- Breadboard

---

## Software Requirements

- Arduino IDE
- Blynk IOT

---

## Technologies Used

| Technology | Purpose |
|------------|----------|
| IoT | Real-time monitoring |
| ESP32 | Sensor communication |
| Lightweight messaging |
| EV Charging Module | Charging demonstration |

---

## Working Principle

1. Sensors detect vehicle occupancy in parking slots.
2. ESP32 collects sensor data.
3. 
4. The server processes parking availability information.
5. Users view available slots via a dashboard.
6. EV owners can locate available charging stations.
7. Charging status and parking occupancy are updated in real time.

---

## Installation

### Clone Repository

```bash
git clone https://github.com/yourusername/IOT-Enabled-Smart-Parking-Framework-with-Electric-Vehicles-Charging-Demonstration.git
```

### Install Dependencies

```bash
npm install
```

or

```bash
pip install -r requirements.txt
```

### Configure MQTT Broker

Update the MQTT broker settings in the configuration file:

```json
{
  "broker": "mqtt://localhost",
  "port": 1883
}
```

### Run Application

```bash
npm start
```

or

```bash
python app.py
```

---

## Project Demonstration

### Parking Slot Status

| Slot | Status |
|--------|--------|
| P1 | Available |
| P2 | Occupied |
| P3 | Available |
| P4 | Charging |

### EV Charging Dashboard

- Charging Station Availability
- Battery Charging Status
- Charging Duration
- Energy Consumption

---

## Folder Structure

```
├── hardware/
│   ├── esp8266_code/
│   ├── sensors/
│
├── backend/
│   ├── api/
│   ├── database/
│
├── frontend/
│   ├── dashboard/
│   ├── mobile_app/
│
├── docs/
│
├── images/
│
└── README.md
```

---

## Future Enhancements

- AI-based parking prediction
- License plate recognition
- Online slot reservation
- Smart payment gateway
- Wireless EV charging integration
- Mobile application deployment
- Smart city integration

---

## Applications

- Shopping malls
- Airports
- Smart cities
- Universities
- Corporate campuses
- EV charging stations
- Multi-level parking facilities

---

## Results

- Reduced parking search time
- Improved parking utilization
- Enhanced EV charging accessibility
- Real-time monitoring and management
- Better user experience

---

## Contributors

- Your Name
- Team Members

---

## License

This project is licensed under the MIT License.

---

## Acknowledgements

Special thanks to the IoT, Smart Mobility, and Electric Vehicle communities for inspiring this project.
